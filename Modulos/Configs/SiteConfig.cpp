#include "../../App/Includes.h"

#include "SiteConfig.h"
#include "../../App/Site.h"
#include "../Log/Log.h"

BEGIN_EVENT_TABLE(SiteConfig, wxDialog)
    EVT_BUTTON(SAVE, SiteConfig::Save)
    EVT_BUTTON(IMPORT, SiteConfig::Import)
    EVT_BUTTON(EXPORT, SiteConfig::Export)
    EVT_CHOICE(CHANGE_UNIT, SiteConfig::ChangeUnit)
    EVT_CLOSE(SiteConfig::OnExit)
END_EVENT_TABLE()

wxStaticText* SiteConfig::Title(wxString title, wxString suf)
{
    wxStaticText* label = new wxStaticText(this, wxID_ANY, title + suf, wxDefaultPosition, wxDefaultSize, 0);
	label->SetFont(wxFont(10, 74, 90, 92, false, "Arial"));
	label->SetForegroundColour(wxColour(221, 112, 2));
	return label;
}

SiteConfig::SiteConfig(const wxString& title, wxWindow* parent, std::string uid, Config *cnf, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog((wxFrame*) NULL, id, title, pos, size, style)
{
    this->parent = parent;
    this->cnf = cnf;
    this->uid = uid;

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);

    // ==================== UNITS ==================== //
	lblUnits = new wxStaticText(this, wxID_ANY, _("Volume unit") + ":", wxDefaultPosition, wxDefaultSize, 0);

	wxString unitsChoices[] = {"l", "ml", "m³", "cm³", "dm³", "mm³"};
	int unitsNChoices = sizeof(unitsChoices) / sizeof(wxString);
	units = new wxChoice(this, CHANGE_UNIT, wxDefaultPosition, wxSize(120,-1), unitsNChoices, unitsChoices, 0);
	units->SetSelection(2);

    wxBoxSizer* unitsSizer1 = new wxBoxSizer(wxHORIZONTAL);
	unitsSizer1->Add(lblUnits, 0, wxALL, 9);
	unitsSizer1->Add(0, 0, 1, wxEXPAND, 5);
    unitsSizer1->Add(units, 0, wxALL, 5);

    wxStaticLine *line1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    sizer1->Add(this->Title(_("Units")), 0, wxALL, 5);
	sizer1->Add(unitsSizer1, 1, wxEXPAND, 5);
    sizer1->Add(line1, 0, wxEXPAND | wxALL, 5);


	// ==================== VALVES ==================== //
	lblFlow = new wxStaticText(this, wxID_ANY, _("Flow at 100% open") + " (m³):", wxDefaultPosition, wxDefaultSize, 0);
	flow = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0, 1000, 0);

    wxBoxSizer* valvesSizer1 = new wxBoxSizer(wxHORIZONTAL);
	valvesSizer1->Add(lblFlow, 0, wxALL, 9);
	valvesSizer1->Add(0, 0, 1, wxEXPAND, 5);
	valvesSizer1->Add(flow, 0, wxALL, 5);

    wxStaticLine *line2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    sizer1->Add(this->Title(_("Valves")), 0, wxALL, 5);
	sizer1->Add(valvesSizer1, 1, wxEXPAND, 5);
    sizer1->Add(line2, 0, wxEXPAND | wxALL, 5);


    // ==================== TANK 1 ==================== //
	lblVolMaxT1 = new wxStaticText(this, wxID_ANY, _("Maximum volume") + " (m³):", wxDefaultPosition, wxDefaultSize, 0);
    volMaxT1 = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0, 10000, 0);
    lblColorT1 = new wxStaticText(this, wxID_ANY, _("Color") + ":", wxDefaultPosition, wxDefaultSize, 0);
    colorTank1 = new ColorSelect(this, wxSize(120, 20));

	wxBoxSizer* tank1Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tank1Sizer1->Add(lblVolMaxT1, 0, wxALL, 9);
	tank1Sizer1->Add(0, 0, 1, wxEXPAND, 5);
    tank1Sizer1->Add(volMaxT1, 0, wxALL, 5);

	wxBoxSizer* tank1Sizer2 = new wxBoxSizer(wxHORIZONTAL);
    tank1Sizer2->Add(lblColorT1, 0, wxALL, 9);
    tank1Sizer2->Add(0, 0, 1, wxEXPAND, 5);
    tank1Sizer2->Add(colorTank1, 0, wxALL, 5);

    wxStaticLine *line3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    sizer1->Add(this->Title(_("Tank 1")), 0, wxALL, 5);
	sizer1->Add(tank1Sizer1, 1, wxEXPAND, 5);
	sizer1->Add(tank1Sizer2, 1, wxEXPAND, 5);
	sizer1->Add(line3, 0, wxEXPAND | wxALL, 5);


	// ==================== TANK 2 ==================== //
	lblVolMaxT2 = new wxStaticText(this, wxID_ANY, _("Maximum volume") + " (m³):", wxDefaultPosition, wxDefaultSize, 0);
    volMaxT2 = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0, 10000, 0);
    lblColorT2 = new wxStaticText(this, wxID_ANY, _("Color") + ":", wxDefaultPosition, wxDefaultSize, 0);
    colorTank2 = new ColorSelect(this, wxSize(120, 20));

	wxBoxSizer* tank2Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tank2Sizer1->Add(lblVolMaxT2, 0, wxALL, 9);
	tank2Sizer1->Add(0, 0, 1, wxEXPAND, 5);
    tank2Sizer1->Add(volMaxT2, 0, wxALL, 5);

	wxBoxSizer* tank2Sizer2 = new wxBoxSizer(wxHORIZONTAL);
    tank2Sizer2->Add(lblColorT2, 0, wxALL, 9);
    tank2Sizer2->Add(0, 0, 1, wxEXPAND, 5);
    tank2Sizer2->Add(colorTank2, 0, wxALL, 5);

    wxStaticLine *line4 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    sizer1->Add(this->Title(_("Tank 2")), 0, wxALL, 5);
	sizer1->Add(tank2Sizer1, 1, wxEXPAND, 5);
	sizer1->Add(tank2Sizer2, 1, wxEXPAND, 5);
	sizer1->Add(line4, 0, wxEXPAND | wxALL, 5);


	// ==================== TANK 3 ==================== //
	lblVolMaxT3 = new wxStaticText(this, wxID_ANY, _("Maximum volume") + " (m³):", wxDefaultPosition, wxDefaultSize, 0);
    volMaxT3 = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0, 20000, 0);

	wxBoxSizer* tank3Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tank3Sizer1->Add(lblVolMaxT3, 0, wxALL, 9);
	tank3Sizer1->Add(0, 0, 1, wxEXPAND, 5);
    tank3Sizer1->Add(volMaxT3, 0, wxALL, 5);

    wxStaticLine *line5 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    sizer1->Add(this->Title(_("Tank 3")), 0, wxALL, 5);
	sizer1->Add(tank3Sizer1, 1, wxEXPAND, 5);
	sizer1->Add(line5, 0, wxEXPAND | wxALL, 5);


	// ==================== BUTTONS ==================== //
	save = new wxButton(this, SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0);
	exportFile = new wxButton(this, EXPORT, _("Export"), wxDefaultPosition, wxDefaultSize, 0);
	importFile = new wxButton(this, IMPORT, _("Import"), wxDefaultPosition, wxDefaultSize, 0);

	wxBoxSizer* sizerBtn = new wxBoxSizer(wxHORIZONTAL);
	sizerBtn->Add(save, 0, wxALL, 5);
	sizerBtn->Add(importFile, 0, wxALL, 5);
	sizerBtn->Add(exportFile, 0, wxALL, 5);

	sizer1->Add(sizerBtn, 1, wxALIGN_RIGHT, 5);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(sizer1, 0, wxALL|wxEXPAND, 10);

	this->SetSizer(sizer);
	this->Layout();

	this->Centre(wxBOTH);

	this->LoadInfo();
}

SiteConfig::~SiteConfig()
{
}

void SiteConfig::OnExit(wxCloseEvent& event)
{
    Site *prt = ((Site*)this->parent);
    if (!prt->operation)
    {
        prt->Reload();
    }

    Destroy();
}

void SiteConfig::ReloadLabels()
{
    wxString newUnit = " (" + this->units->GetString(this->units->GetSelection()) + "):";

    this->lblFlow->SetLabel(_("Flow at 100% open") + newUnit);
    this->lblVolMaxT1->SetLabelText(_("Maximum volume") + newUnit);
    this->lblVolMaxT2->SetLabelText(_("Maximum volume") + newUnit);
    this->lblVolMaxT3->SetLabelText(_("Maximum volume") + newUnit);
}

void SiteConfig::LoadInfo()
{
    this->units->SetSelection(this->cnf->volumeUnit);
    this->flow->SetValue(this->cnf->valveMaxFlow);
    this->volMaxT1->SetValue(this->cnf->tank1MaxVol);
    this->volMaxT2->SetValue(this->cnf->tank2MaxVol);
    this->volMaxT3->SetValue(this->cnf->tank3MaxVol);
    this->colorTank1->SetColor(this->cnf->tank1Color);
    this->colorTank2->SetColor(this->cnf->tank2Color);
    this->ReloadLabels();
}

void SiteConfig::PutInfo()
{
    this->cnf->volumeUnit   = this->units->GetSelection();
    this->cnf->valveMaxFlow = this->flow->GetValue();
    this->cnf->tank1MaxVol  = this->volMaxT1->GetValue();
    this->cnf->tank2MaxVol  = this->volMaxT2->GetValue();
    this->cnf->tank3MaxVol  = this->volMaxT3->GetValue();
    this->cnf->tank1Color   = this->colorTank1->GetColor();
    this->cnf->tank2Color   = this->colorTank2->GetColor();
}

void SiteConfig::InsertLog()
{
    if (this->cnf->volumeUnit   != this->units->GetSelection())
    {
        wxString unitBef = this->units->GetString(this->cnf->volumeUnit),
                 unitAft = this->units->GetString(this->units->GetSelection());
        unitBef.Replace("³", "3");
        unitAft.Replace("³", "3");
        wxString desc = unitBef + " -> " + unitAft;
        Log("14", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->valveMaxFlow != this->flow->GetValue())
    {
        // 10l -> 200ml
        wxString desc = wxString::Format("%i", this->cnf->valveMaxFlow)
                      + "[u] -> "
                      + wxString::Format("%i", this->flow->GetValue()) + "[u]";
        Log("15", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->tank1MaxVol  != this->volMaxT1->GetValue())
    {
        wxString desc = wxString::Format("%i", this->cnf->tank1MaxVol)
                      + "[u] -> "
                      + wxString::Format("%i", this->volMaxT1->GetValue()) + "[u]";
        Log("11", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->tank2MaxVol  != this->volMaxT2->GetValue())
    {
        wxString desc = wxString::Format("%i", this->cnf->tank2MaxVol)
                      + "[u] -> "
                      + wxString::Format("%i", this->volMaxT2->GetValue()) + "[u]";
        Log("12", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->tank3MaxVol  != this->volMaxT3->GetValue())
    {
        wxString desc = wxString::Format("%i", this->cnf->tank3MaxVol)
                      + "[u] -> "
                      + wxString::Format("%i", this->volMaxT3->GetValue()) + "[u]";
        Log("13", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->tank1Color   != this->colorTank1->GetColor())
    {
        wxString desc = this->cnf->tank1Color.GetAsString(wxC2S_CSS_SYNTAX)
                      + " -> "
                      + this->colorTank1->GetColor().GetAsString(wxC2S_CSS_SYNTAX);
        Log("4", this->uid, std::string(desc.mb_str()));
    }
    if (this->cnf->tank2Color   != this->colorTank2->GetColor())
    {
        wxString desc = this->cnf->tank2Color.GetAsString(wxC2S_CSS_SYNTAX)
                      + " -> "
                      + this->colorTank2->GetColor().GetAsString(wxC2S_CSS_SYNTAX);
        Log("5", this->uid, std::string(desc.mb_str()));
    }

}

void SiteConfig::ChangeUnit(wxCommandEvent &event)
{
    this->ReloadLabels();
}

void SiteConfig::Save(wxCommandEvent &event)
{
    if (((Site*)this->parent)->operation)
    {
        wxMessageDialog dlg(this, _("You can not make any changes with the plant operating!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else
    {
        wxMessageDialog dlg(this, _("Do you really want to apply those changes?"), _("Confirmation"), wxYES_NO);
        dlg.SetYesNoLabels(_("Yes"), _("No"));
        int answer = dlg.ShowModal();

        if (answer == wxID_YES)
        {
            this->InsertLog();
            this->PutInfo();
            this->cnf->Save();

            wxMessageDialog dlg(this, _("The configuration was saved!"), _("Success"), wxICON_INFORMATION);
            dlg.ShowModal();
        }
    }
}

void SiteConfig::Import(wxCommandEvent &event)
{
    wxString path = DirSelect::FileDlg("*.cnf");

    if (path == "")
    {
        wxMessageDialog dlg(this, _("You must select a '.cnf' file!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else if (!this->cnf->LoadFile(path))
    {
        wxMessageDialog dlg(this, _("You have provided an invalid '.cnf' file!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else
    {
        this->LoadInfo();
    }
}

void SiteConfig::Export(wxCommandEvent &event)
{
    this->PutInfo();
    wxString path = DirSelect::PathDlg();

    if (path == "")
    {
        wxMessageDialog dlg(this, _("You must select a path to save the file!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else if (!this->cnf->SaveFile(path + "/ColorMixer.cnf"))
    {
        wxMessageDialog dlg(this, _("We couldn't create the file in this directory!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else
    {
        wxMessageDialog dlg(this, _("The configuration file was saved!"), _("Success"), wxICON_INFORMATION);
        dlg.ShowModal();
    }
}
