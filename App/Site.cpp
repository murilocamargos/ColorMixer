#include "Includes.h"

#include "Site.h"

BEGIN_EVENT_TABLE(Site, wxFrame)
    EVT_BUTTON(ADVANCE, Site::OnAdvanceTime)
    EVT_CLOSE(Site::OnExit)
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

    /*

    float perc = this->vol1/this->max1;
    wxPoint pos = this->nivel1 + wxPoint(0, (-183) * perc);
    this->btn_nivel1->SetSize(wxSize(26, 183 * perc));
    this->btn_nivel1->SetPosition(pos);
    this->lbl_nivel1->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");

    perc = this->vol2/this->max2;
    pos = this->nivel2 + wxPoint(0, (-183) * perc);
    this->btn_nivel2->SetSize(wxSize(26, 183 * perc));
    this->btn_nivel2->SetPosition(pos);
    this->lbl_nivel2->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");

    perc = (this->vol3_1 + this->vol3_2)/this->max3;
    pos = this->nivel3 + wxPoint(0, (-183) * perc);
    this->btn_nivel3->SetSize(wxSize(26, 183 * perc));
    this->btn_nivel3->SetPosition(pos);
    this->lbl_nivel3->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");

    // Mistura
    int r = (this->vol3_1*this->c1.Red() + this->vol3_2*this->c2.Red())/(this->vol3_1 + this->vol3_2);
    int g = (this->vol3_1*this->c1.Green() + this->vol3_2*this->c2.Green())/(this->vol3_1 + this->vol3_2);
    int b = (this->vol3_1*this->c1.Blue() + this->vol3_2*this->c2.Blue())/(this->vol3_1 + this->vol3_2);
    wxColour c3(r,g,b);
    this->btn_rgb3->SetLabel(this->GetRGB(c3));
    this->btn_rgb3->SetBackgroundColour(c3);
    this->btn_nivel3->SetBackgroundColour(c3);

    Refresh();
    */
}


Site::Site(const wxString& title, wxApp* app, std::string uid, const wxPoint& pos, const wxSize& size, long style):
    wxFrame((wxFrame*) NULL, wxID_ANY, title, pos, size, style)
{
    taskbar = new TaskBar(this);
    this->flow = 10;

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(228, 228, 228));

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
    if (this->CloseFrame())
    {
        this->taskbar->Destroy();
        Destroy();
        event.Skip();
    }
}

bool Site::CloseFrame()
{
    wxMessageDialog dlg(this, _("Do you really want to close the app?"), _("Confirmation"), wxYES_NO | wxCANCEL);

    dlg.SetYesNoCancelLabels(_("Close"), _("Minimize"), _("Cancel"));

    int answer = dlg.ShowModal();

    if (answer != wxID_CANCEL)
    {
        /*
        MyApp *app = (MyApp*)this->app;
        app->SetExitOnFrameDelete(bool(answer == wxID_YES));
        */
        if (answer == wxID_NO)
        {
            // Só esconde o frame para não ter de criá-lo novamente
            this->Hide();
            this->taskbar->SetIcon(wxICON(APP_ICON), _("Color Mixer"));
        }
        else
        {
            /*
            // Salva ultimo idioma utilizado pelo usuário
            wxConfig config(app->GetAppName());
            long language = (app->locale->GetLanguage());
            config.Write(wxT("wxTranslation_Language"), language);
            config.Flush();
            */
            return true;
        }
    }

    return false;
}
