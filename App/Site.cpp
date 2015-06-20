#include "Includes.h"

#include "Site.h"

#include "../Modulos/Configs/SiteConfig.h"

BEGIN_EVENT_TABLE(Site, wxFrame)
    EVT_BUTTON(ADVANCE, Site::OnAdvanceTime)
    EVT_BUTTON(INITOPR, Site::OnInitOperation)
    EVT_CLOSE(Site::OnExit)
    EVT_MENU(MENU_FILE_NEW, Site::OnMenuFileNew)
    EVT_MENU(MENU_FILE_SAVE, Site::OnMenuFileSave)
    EVT_MENU(MENU_FILE_OPEN, Site::OnMenuFileOpen)
    EVT_MENU(MENU_FILE_QUIT, Site::OnMenuFileQuit)
    EVT_MENU(MENU_HELP, Site::OnMenuHelp)
    EVT_MENU(MENU_HELP_ABOUT, Site::OnMenuHelpAbout)
    EVT_MENU(MENU_SETTINGS_CONFIG, Site::OnMenuSettingsPlant)
END_EVENT_TABLE()

void Site::OnInitOperation(wxCommandEvent& event)
{
    this->operation = !this->operation;
    this->btnAdvance->Enable(!this->btnAdvance->IsEnabled());

    if (this->operation)
    {
        this->btnInitOpr->SetLabel(_("Stop Operation"));
    }
    else
    {
        this->btnInitOpr->SetLabel(_("Start Operation"));
    }
}

void Site::OnAdvanceTime(wxCommandEvent& event)
{
    // Entrada do tanque 1
    this->t1->SetLevel(this->cnf->valveMaxFlow * this->vin1->value/100);
    // Saída do tanque 1
    float out1 = MIN(this->cnf->valveMaxFlow * this->vout1->value/100, this->t1->level);

    // Entrada do tanque 2
    this->t2->SetLevel(this->cnf->valveMaxFlow * this->vin2->value/100);
    // Saída do tanque 2
    float out2 = MIN(this->cnf->valveMaxFlow * this->vout2->value/100, this->t2->level);

    this->t1->SetLevel(-1 * out1);
    this->t2->SetLevel(-1 * out2);

    // Entrada no tanque 3 das duas tintas separadamente
    this->t3->SetLevel(out1, out2);

    // Saída do tanque 3
    if (this->t3->level > 0 && this->vout3->value > 0)
    {
        float tinta1 = this->t3->Percent(1) * this->vout3->value/100 * this->cnf->valveMaxFlow;
        float tinta2 = this->t3->Percent(2) * this->vout3->value/100 * this->cnf->valveMaxFlow;
        this->t3->SetLevel((-1)*MIN(this->t3->lvl_c1, tinta1), (-1)*MIN(this->t3->lvl_c2, tinta2));
    }
}


Site::Site(const wxString& title, wxApp* app, std::string uid, const wxPoint& pos, const wxSize& size, long style):
    wxFrame((wxFrame*) NULL, wxID_ANY, title, pos, size, style)
{
    this->taskbar = new TaskBar(this);
    this->app = app;
    this->cnf = new Config(app);
    this->operation = false;

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(228, 228, 228));

	///Menu
    menu = new MyMenu();
    wxString file = _("File"),
             help = _("Help"),
             settings = _("Settings");

    this->menu->AddMenu(file);
    this->menu->AddMenu(help);
    this->menu->AddMenu(settings);

    this->menu->AddSubMenu(file, MENU_FILE_NEW, _("New\tCtrl+N"), _("New File."));
    this->menu->AddSubMenu(file, MENU_FILE_OPEN, _("Open\tCtrl+O"), _("Open File."));
    this->menu->AddSubMenu(file, MENU_FILE_SAVE, _("Save\tCtrl+S"), _("Save File."));
    this->menu->Separator(file);
    this->menu->AddSubMenu(file, MENU_FILE_QUIT, _("Quit\tCtrl+Q"), _("Quit App."));

    this->menu->AddSubMenu(help, MENU_HELP, _("Help\tF1"), _("Get Help."));
    this->menu->AddSubMenu(help, MENU_HELP_ABOUT, _("About\tF2"), _("Get to know us better!"));

    this->menu->AddSubMenu(settings, MENU_SETTINGS_CONFIG, _("Plant Config.\tf10"), _("Configure the plant variables."));

    SetMenuBar(this->menu);
	//**********

	btnInitOpr = new wxButton(this, INITOPR, _("Start Operation"), wxDefaultPosition, wxDefaultSize, 0);
	btnAdvance = new wxButton(this, ADVANCE, _("Advance Time"), wxDefaultPosition, wxDefaultSize, 0);

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

    this->t1 = new Tank(this, this->cnf->tank1Color, 0, this->cnf->tank1MaxVol);
    this->t2 = new Tank(this, this->cnf->tank2Color, 0, this->cnf->tank2MaxVol);
    this->t3 = new TankMix(this, this->t1, this->t2, 0, this->cnf->tank3MaxVol);

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


	wxBoxSizer* sizerCtrl = new wxBoxSizer(wxVERTICAL);
    sizerCtrl->Add(btnAdvance, 0, wxALL|wxEXPAND, 5);
    sizerCtrl->Add(btnInitOpr, 0, wxALL|wxEXPAND, 5);

	planta_grid->Add(sizerCtrl, 0, wxALL, 5);
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

	this->btnAdvance->Enable(false);
}

Site::~Site()
{
}

void Site::Reload()
{
    this->t1->Reset(this->cnf->tank1MaxVol, this->cnf->tank1Color);
    this->t2->Reset(this->cnf->tank2MaxVol, this->cnf->tank2Color);
    this->t3->Reset(this->cnf->tank3MaxVol);
}

void Site::OnMenuSettingsPlant(wxCommandEvent& event)
{
    wxString title = _("ColorMixer") + ": " + _("Configurations");
    SiteConfig *frame = new SiteConfig(title, this, "1", this->cnf);
    frame->SetIcon(wxICON(CONFIG));
    frame->Show(TRUE);
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
