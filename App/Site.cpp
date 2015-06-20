#include "Includes.h"

#include "Site.h"

BEGIN_EVENT_TABLE(Site, wxFrame)
    EVT_BUTTON(ADVANCE, Site::OnAdvanceTime)
    EVT_CLOSE(Site::OnExit)
    EVT_MENU(MENU_FILE_NEW, Site::OnMenuFileNew)
    EVT_MENU(MENU_FILE_SAVE, Site::OnMenuFileSave)
    EVT_MENU(MENU_FILE_OPEN, Site::OnMenuFileOpen)
    EVT_MENU(MENU_FILE_QUIT, Site::OnMenuFileQuit)
    EVT_MENU(MENU_HELP, Site::OnMenuHelp)
    EVT_MENU(MENU_HELP_ABOUT, Site::OnMenuHelpAbout)
END_EVENT_TABLE()

void Site::OnAdvanceTime(wxCommandEvent& event)
{
    // Entrada do tanque 1
    this->t1->SetLevel(this->flow * this->vin1->value/100);
    // Saída do tanque 1
    float out1 = MIN(this->flow * this->vout1->value/100, this->t1->level);

    // Entrada do tanque 2
    this->t2->SetLevel(this->flow * this->vin2->value/100);
    // Saída do tanque 2
    float out2 = MIN(this->flow * this->vout2->value/100, this->t2->level);

    this->t1->SetLevel(-1 * out1);
    this->t2->SetLevel(-1 * out2);

    // Entrada no tanque 3 das duas tintas separadamente
    this->t3->SetLevel(out1, out2);

    // Saída do tanque 3
    if (this->t3->level > 0 && this->vout3->value > 0)
    {
        float tinta1 = this->t3->Cont1() * this->vout3->value/100 * this->flow;
        float tinta2 = this->t3->Cont2() * this->vout3->value/100 * this->flow;
        this->t3->SetLevel((-1)*MIN(this->t3->lvl_c1, tinta1), (-1)*MIN(this->t3->lvl_c2, tinta2));
    }
}


Site::Site(const wxString& title, wxApp* app, std::string uid, const wxPoint& pos, const wxSize& size, long style):
    wxFrame((wxFrame*) NULL, wxID_ANY, title, pos, size, style)
{
    taskbar = new TaskBar(this);
    this->flow = 10;

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(228, 228, 228));

	///Menu
    menu = new MyMenu();
    wxString file = _("File"),
             help = _("Help");

    this->menu->AddMenu(file);
    this->menu->AddMenu(help);

    this->menu->AddSubMenu(file, MENU_FILE_NEW, _("New\tCtrl+N"), _("New File."));
    this->menu->AddSubMenu(file, MENU_FILE_OPEN, _("Open\tCtrl+O"), _("Open File."));
    this->menu->AddSubMenu(file, MENU_FILE_SAVE, _("Save\tCtrl+S"), _("Save File."));
    this->menu->Separator(file);
    this->menu->AddSubMenu(file, MENU_FILE_QUIT, _("Quit\tCtrl+Q"), _("Quit App."));
    this->menu->AddSubMenu(help, MENU_HELP, _("Help\tF1"), _("Get Help."));
    this->menu->AddSubMenu(help, MENU_HELP_ABOUT, _("About\tF2"), _("Get to know us better!"));

    SetMenuBar(this->menu);
	//**********

	btnAdvance = new wxButton(this, ADVANCE, _("Avançar Tempo"), wxDefaultPosition, wxDefaultSize, 0);

	leftPipe_valvIn1  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_LEFT), wxDefaultPosition, wxDefaultSize, 0);
	rightPipe_valvIn1 = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_RIGHT), wxDefaultPosition, wxDefaultSize, 0);
    leftPipe_valvIn2  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_LEFT), wxDefaultPosition, wxDefaultSize, 0);
    rightPipe_valvIn2 = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_RIGHT), wxDefaultPosition, wxDefaultSize, 0);

    leftPipe_valvOut1  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_LEFT), wxDefaultPosition, wxDefaultSize, 0);
    rightPipe_valvOut1 = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(CURVE_90), wxDefaultPosition, wxDefaultSize, 0);
    leftPipe_valvOut2  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_LEFT), wxDefaultPosition, wxDefaultSize, 0);
    rightPipe_valvOut2 = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(TEE), wxDefaultPosition, wxDefaultSize, 0);
    leftPipe_valvOut3  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_LEFT), wxDefaultPosition, wxDefaultSize, 0);
    rightPipe_valvOut3 = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(PIPE_RIGHT), wxDefaultPosition, wxDefaultSize, 0);

    this->vin1  = new Valve(this, 0);
    this->vout1 = new Valve(this, 0);
    this->vin2  = new Valve(this, 0);
    this->vout2 = new Valve(this, 0);
    this->vout3 = new Valve(this, 0);

    this->t2 = new Tank(this, wxColour(60, 237, 247), 0, 100);
    this->t1 = new Tank(this, wxColour(244, 235, 62), 0, 100);
    this->t3 = new TankMix(this, this->t1, this->t2, 0, 200);


	wxFlexGridSizer *planta_grid = new wxFlexGridSizer(2, 11, 0, 0);
	planta_grid->SetFlexibleDirection(wxBOTH);
	planta_grid->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	planta_grid->Add(leftPipe_valvIn1, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->vin1, 1, wxALIGN_BOTTOM, 0);
	planta_grid->Add(rightPipe_valvIn1, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->t1, 1, wxEXPAND, 0);
	planta_grid->Add(leftPipe_valvOut1, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->vout1, 1, wxALIGN_BOTTOM, 0);
	planta_grid->Add(rightPipe_valvOut1, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(0, 0, 1, wxEXPAND, 0);
	planta_grid->Add(0, 0, 1, wxEXPAND, 0);
	planta_grid->Add(0, 0, 1, wxEXPAND, 0);

	planta_grid->Add(btnAdvance, 0, wxALL, 5);
	planta_grid->Add(leftPipe_valvIn2, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->vin2, 1, wxALIGN_BOTTOM, 5);
	planta_grid->Add(rightPipe_valvIn2, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->t2, 1, wxEXPAND, 5);
	planta_grid->Add(leftPipe_valvOut2, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->vout2, 1, wxALIGN_BOTTOM, 0);
	planta_grid->Add(rightPipe_valvOut2, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->t3, 1, wxEXPAND, 5);
	planta_grid->Add(leftPipe_valvOut3, 0, wxALIGN_BOTTOM|wxALL, 0);
	planta_grid->Add(this->vout3, 1, wxALIGN_BOTTOM, 0);
	planta_grid->Add(rightPipe_valvOut3, 0, wxALIGN_BOTTOM|wxALL, 0);

	this->SetSizer(planta_grid);
	this->Layout();

	this->Centre(wxBOTH);
}

Site::~Site()
{
}

void Site::OnExit(wxCloseEvent& event)
{
    this->taskbar->CloseParent();
}

void Site::OnMenuFileNew(wxCommandEvent& event)
{
    wxMessageDialog dlg(this, _("You have created a new file!"), _("File created"), wxICON_INFORMATION);
    dlg.ShowModal();
}

void Site::OnMenuFileSave(wxCommandEvent& event)
{
    wxMessageDialog dlg(this, _("Your file was saved with success!"), _("File saved"), wxICON_INFORMATION);
    dlg.ShowModal();
}

void Site::OnMenuFileOpen(wxCommandEvent& event)
{
    wxString path = this->menu->FilePath(_("Select a file"), _("All files (*.*)|*.*"));
    if (path != "")
    {
        wxLogMessage(path);
    }
}

void Site::OnMenuFileQuit(wxCommandEvent& event)
{
    this->taskbar->CloseParent();
}

void Site::OnMenuHelp(wxCommandEvent& event)
{
    //help->ShowHelp();
}

void Site::OnMenuHelpAbout(wxCommandEvent & event)
{
    wxMessageDialog dlg(this, _("Developed by Luana Michelly and Murilo Camargos\nComputer Aided Project\nUNIMONTES"), _("About"), wxICON_QUESTION);
    dlg.ShowModal();
}
