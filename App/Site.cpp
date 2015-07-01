#include "Includes.h"

#include "Site.h"

#include "../Modulos/Configs/SiteConfig.h"
#include "../Modulos/User/SearchUserScreen.h"
#include "../Modulos/Log/LogScreen.h"
#include "../Modulos/Login/LoginScreen.h"

#include <wx/sound.h>

BEGIN_EVENT_TABLE(SiteLayout, wxScrolledWindow)
    EVT_BUTTON(ADVANCE, SiteLayout::OnAdvanceTime)
    EVT_BUTTON(INITOPR, SiteLayout::OnInitOperation)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Site, wxFrame)
    EVT_CLOSE(Site::OnExit)
    EVT_MENU(MENU_FILE_NEW, Site::OnMenuFileNew)
    EVT_MENU(MENU_FILE_SAVE, Site::OnMenuFileSave)
    EVT_MENU(MENU_FILE_OPEN, Site::OnMenuFileOpen)
    EVT_MENU(MENU_FILE_QUIT, Site::OnMenuFileQuit)
    EVT_MENU(MENU_USER_NEW, Site::OnMenuUserNew)
    EVT_MENU(MENU_USER_SEARCH, Site::OnMenuUserSearch)
    EVT_MENU(MENU_USER_EDIT, Site::OnMenuUserEdit)
    EVT_MENU(MENU_LOG_VIEW, Site::OnMenuLogView)
    EVT_MENU(MENU_HELP, Site::OnMenuHelp)
    EVT_MENU(MENU_HELP_ABOUT, Site::OnMenuHelpAbout)
    EVT_MENU(MENU_SETTINGS_CONFIG, Site::OnMenuSettingsPlant)
END_EVENT_TABLE()

void SiteLayout::OnInitOperation(wxCommandEvent& event)
{
    *this->operation = !(*this->operation);
    this->btnAdvance->Enable(!this->btnAdvance->IsEnabled());

    if (*this->operation)
    {
        this->btnInitOpr->SetBitmap(wxBitmap( "Images/Site/stop.bmp", wxBITMAP_TYPE_ANY ));
        this->btnInitOpr->SetToolTip(_("Stop Operation"));
    }
    else
    {
        this->btnInitOpr->SetBitmap(wxBitmap( "Images/Site/play.bmp", wxBITMAP_TYPE_ANY ));
        this->btnInitOpr->SetToolTip(_("Start Operation"));
    }
}

void SiteLayout::OnAdvanceTime(wxCommandEvent& event)
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

    wxString filename("Controls/alarm.wav");
    wxSound *music = new wxSound(filename);
    music->Create(filename);

    wxString tankName("");
    float perc[3] = { this->t1->level / this->t1->maxLevel,
                      this->t2->level / this->t2->maxLevel,
                      this->t3->level / this->t3->maxLevel };

    for (int i = 0; i < 3; i++)
    {
        tankName = _("Tank") + " " + wxString::Format("%i", (i+1));
        if(perc[i] >= 0.85 && perc[i] < 0.95)
        {
            wxMessageDialog dlg(this, tankName + " " + _("is filled with more than") + " 85% " + _("of its maximum volume!"), _("Warning"), wxICON_ERROR);
            dlg.ShowModal();
        }
        if(perc[i] >= 0.95)
        {
            music->Play(filename, wxSOUND_SYNC);
            wxMessageDialog dlg(this, tankName + " " + _("is filled with more than") + " 95% " + _("of its maximum volume!"), _("Warning"), wxICON_ERROR);
            dlg.ShowModal();
        }
    }
}

void SiteLayout::Reload()
{
    this->t1->Reset(this->cnf->tank1MaxVol, this->cnf->tank1Color);
    this->t2->Reset(this->cnf->tank2MaxVol, this->cnf->tank2Color);
    this->t3->Reset(this->cnf->tank3MaxVol);
}

void SiteLayout::SaveValves()
{
    this->cnf->SaveValves(this->vin1->value, this->vout1->value, this->vin2->value, this->vout2->value, this->vout3->value);
}

SiteLayout::SiteLayout(wxWindow* parent, bool *operation, Config *cnf, std::string uid, wxWindowID id) : wxScrolledWindow(parent, id)
{
    this->operation = operation;
    this->cnf = cnf;
    this->uid = uid;

    this->SetBackgroundColour(wxColour(228, 228, 228));

    btnInitOpr = new wxBitmapButton( this, INITOPR, wxBitmap( "Images/Site/play.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER );
    btnInitOpr->SetToolTip(_("Start Operation"));

    btnAdvance = new wxBitmapButton( this, ADVANCE, wxBitmap( "Images/Site/advenabled.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER );
	btnAdvance->SetBitmapDisabled( wxBitmap( "Images/Site/advdisabled.bmp", wxBITMAP_TYPE_ANY ) );
	btnAdvance->SetToolTip(_("Advance Time"));
	this->btnAdvance->Enable(false);

	top = new wxStaticBitmap( this, wxID_ANY, wxBitmap( "Images/Site/topo.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bottom = new wxStaticBitmap( this, wxID_ANY, wxBitmap( "Images/Site/bottom.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );

    this->vin1  = new Valve(this, this->cnf->vin1 , this->uid, "6", "ValveIn1");
    this->vout1 = new Valve(this, this->cnf->vout1, this->uid, "8", "ValveOut1");
    this->vin2  = new Valve(this, this->cnf->vin2 , this->uid, "7", "ValveIn2");
    this->vout2 = new Valve(this, this->cnf->vout2, this->uid, "9", "ValveOut2");
    this->vout3 = new Valve(this, this->cnf->vout3, this->uid, "10", "ValveOut");

    this->t1 = new Tank(this, this->cnf->tank1Color, 0, this->cnf->tank1MaxVol, "Tank1");
    this->t2 = new Tank(this, this->cnf->tank2Color, 0, this->cnf->tank2MaxVol, "Tank2");
    this->t3 = new TankMix(this, this->t1, this->t2, 0, this->cnf->tank3MaxVol, "Tank3");

    /// -------------------------------------------------------------------------------------------
    wxFlexGridSizer *topo = new wxFlexGridSizer(1, 3, 0, 0);
    topo->SetFlexibleDirection(wxBOTH);
	topo->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    topo->Add( btnInitOpr, 0, wxALL, 0 );
	topo->Add( top, 0, wxALL, 0 );
	topo->Add( btnAdvance, 0, wxALL, 0 );


	wxFlexGridSizer *site = new wxFlexGridSizer(1, 8, 0, 0);
    site->SetFlexibleDirection(wxBOTH);
	site->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    site->Add( vin1, 0, wxALL, 0 );
	site->Add( t1, 0, wxALL, 0 );
	site->Add( vin2, 0, wxALL, 0 );
	site->Add( t2, 0, wxALL, 0 );
	site->Add( vout1, 0, wxALL, 0 );
	site->Add( vout2, 0, wxALL, 0 );
	site->Add( t3, 0, wxALL, 0 );
	site->Add( vout3, 0, wxALL, 0 );


    wxFlexGridSizer *container = new wxFlexGridSizer(3, 1, 0, 0);
    container->SetFlexibleDirection(wxBOTH);
	container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	container->Add( topo, 0, wxALL, 0 );
	container->Add( site, 0, wxALL, 0 );
	container->Add( bottom, 0, wxALL, 0 );

	this->SetSizer( container );
	this->Layout();
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(1,1);
}














Site::Site(const wxString& title, wxApp* app, std::string uid, const wxPoint& pos, const wxSize& size, long style):
    wxFrame((wxFrame*) NULL, wxID_ANY, title, pos, size, style)
{
    this->taskbar = new TaskBar(this);
    this->app = app;
    this->uid = uid;
    this->cnf = new Config(app);
    this->operation = false;

    // Obtém informações do usuário que fez o login
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();

    sql->Table("usuarios")->Where("user_id", uid);
    db->Select(sql);

    this->user_info = db->rows[0];

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	///Menu
    menu = new MyMenu();
    wxString file = _("File"),
             logs = _("Logs"),
             user = _("User"),
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
    if (this->user_info["nivel"] == "1")
    {
        this->menu->AddMenu(user);
        this->menu->AddSubMenu(user, MENU_USER_NEW, _("Add User"), _("Add a new user."));
        this->menu->AddSubMenu(user, MENU_USER_SEARCH, _("Search User"), _("Search for user."));
        this->menu->AddMenu(logs);
        this->menu->AddSubMenu(logs, MENU_LOG_VIEW, _("View Logs"), _("View system logs"));

    }
    else
    {
        this->menu->AddMenu(user);
        this->menu->AddSubMenu(user, MENU_USER_EDIT, _("Edit User"), _("Edit current user."));
    }

    SetMenuBar(this->menu);
	//**********

    this->SetSizeHints( wxSize( 1000, 583 ), wxSize( 1000, 583 ) );
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    this->layout = new SiteLayout(this, &operation, cnf, uid);
    sizer->Add(this->layout, 1, wxEXPAND);

    //StatusBar
    wxString msg = _("Welcome") + " " + wxString(user_info["nome"]) + " :)";
    CreateStatusBar(2);
    SetStatusText(msg, 1);

    this->SetSizer(sizer);
}

Site::~Site()
{
}

void Site::Reload()
{
    this->layout->Reload();
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
    this->layout->SaveValves();
    this->taskbar->CloseParent();
}

void Site::OnMenuFileQuit(wxCommandEvent& event)
{
    this->layout->SaveValves();
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

void Site::OnMenuHelp(wxCommandEvent& event)
{
    Help *help = new Help();
    help->ShowHelp();
}

void Site::OnMenuHelpAbout(wxCommandEvent & event)
{
    wxMessageDialog dlg(this, _("Developed by Luana Michelly and Murilo Camargos\nComputer Aided Project\nUNIMONTES"), _("About"), wxICON_QUESTION);
    dlg.ShowModal();
}
void Site::OnMenuUserNew(wxCommandEvent& event)
{
    InsertUserScreen *ins = new InsertUserScreen(uid, _("Insert User"), this);
    ins->SetIcon(wxICON(ADDUSER_ICON));
    ins->Show(TRUE);
}
void Site::OnMenuUserEdit(wxCommandEvent& event)
{
    InsertUserScreen *ins = new InsertUserScreen(uid, _("Edit User"), this, uid);
    ins->SetIcon(wxICON(ADDUSER_ICON));
    ins->Show(TRUE);
}
void Site::OnMenuUserSearch(wxCommandEvent& event)
{
    SearchUserScreen *sea = new SearchUserScreen(this, uid, wxID_ANY, _("Search User"));
    sea->SetIcon(wxICON(FIND_ICON));
    sea->Show(TRUE);
}

void Site::OnMenuLogView(wxCommandEvent& event)
{
    LogScreen *sea = new LogScreen(this, wxID_ANY, _("Log Audition"));
    sea->SetIcon(wxICON(LOG_ICON));
    sea->Show(TRUE);
}
