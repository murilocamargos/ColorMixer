#include "../App/Includes.h"
#include "Tank.h"

#include <wx/colourdata.h>
#include <wx/colordlg.h>

BEGIN_EVENT_TABLE(Tank, wxPanel)
    EVT_BUTTON(CHOOSE_COLOR, Tank::ChooseColor)
END_EVENT_TABLE()

TankMix::TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel)
    : Tank(parent, wxNullColour, level, maxLevel)
{
    this->t1 = t1;
    this->t2 = t2;
    this->lvl_c1 = this->lvl_c2 = 0;
    this->btnColor->Enable(false);
}

void TankMix::SetLevel(float qty_c1, float qty_c2)
{
    this->lvl_c1 += qty_c1;
    this->lvl_c2 += qty_c2;
    this->level  += qty_c1 + qty_c2;
    float perc = this->level/this->maxLevel;

    this->btnLevel->SetSize(wxSize(26, 183 * perc));
    this->btnLevel->SetPosition(levelIniPos + wxPoint(0, 183 - this->btnLevel->GetSize().GetHeight()));
    this->lblLevel->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");


    this->MixColors();
    this->btnColor->SetBackgroundColour(this->color);
    this->btnLevel->SetBackgroundColour(this->color);
    this->btnColor->SetLabel(this->GetRGB());
}

void TankMix::MixColors()
{
    int r = this->Cont1() * this->t1->color.Red()   + this->Cont2() * this->t2->color.Red();
    int g = this->Cont1() * this->t1->color.Green() + this->Cont2() * this->t2->color.Green();
    int b = this->Cont1() * this->t1->color.Blue()  + this->Cont2() * this->t2->color.Blue();
    this->color = wxColour(r, g, b);
}

float TankMix::Cont1()
{
    return this->lvl_c1/(this->lvl_c1 + this->lvl_c2);
}

float TankMix::Cont2()
{
    return this->lvl_c2/(this->lvl_c1 + this->lvl_c2);
}

Tank::Tank(wxWindow *parent, wxColour color, float level, float maxLevel) : wxPanel(parent)
{
    this->color = color;
    this->level = level;
    this->maxLevel = maxLevel;

	this->btnColor = new wxButton(this, CHOOSE_COLOR, this->GetRGB(), wxDefaultPosition, wxSize(115, -1), 0 | wxNO_BORDER);
	this->btnColor->SetBackgroundColour(this->color);

	this->btnLevel = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 | wxNO_BORDER);
	this->btnLevel->SetMinSize(wxSize(26, 0));
	this->btnLevel->SetBackgroundColour(this->color);

	this->lblLevel = new wxStaticText(this, wxID_ANY, _("Nível:") + " 0.00%", wxDefaultPosition, wxSize(105, -1), 5);

	this->tankTop    = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(TANK_TOP), wxDefaultPosition, wxDefaultSize, 0);
    this->tankBottom = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(TANK_BOTTOM), wxDefaultPosition, wxDefaultSize, 0);
    this->tankLeft   = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(TANK_LEFT), wxDefaultPosition, wxDefaultSize, 0);
	this->tankRight  = new wxStaticBitmap(this, wxID_ANY, wxBITMAP(TANK_RIGHT), wxDefaultPosition, wxDefaultSize, 0);


	wxFlexGridSizer *container_ins = new wxFlexGridSizer(1, 3, 0, 0);
	container_ins->SetFlexibleDirection(wxBOTH);
	container_ins->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	container_ins->Add(this->tankLeft, 0, wxALIGN_BOTTOM | wxALL, 0);
	container_ins->Add(this->btnLevel, 0, wxALIGN_BOTTOM | wxALL, 0);
	container_ins->Add(this->tankRight, 0, wxALIGN_BOTTOM | wxALL, 0);



    wxFlexGridSizer* container = new wxFlexGridSizer(6, 1, 0, 0);
	container->SetFlexibleDirection(wxBOTH);
	container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    // Espaço de 25 pixels na parte de cima do container
	container->Add(0, 25, 1, wxEXPAND, 5);
    container->Add(this->btnColor, 0, wxALL, 0);
	container->Add(this->lblLevel, 0, wxALL, 5);
	container->Add(this->tankTop, 0, wxALIGN_BOTTOM | wxALL, 0);
	container->Add(container_ins, 1, wxEXPAND, 0);
    container->Add(this->tankBottom, 0, wxALIGN_BOTTOM | wxALL, 0);

    this->SetSizer(container);
    this->Layout();

    this->levelIniPos = this->btnLevel->GetPosition();
}

wxString Tank::GetRGB()
{
    return wxString::Format("RGB (%i, %i, %i)", this->color.Red(), this->color.Green(), this->color.Blue());
}

void Tank::SetLevel(float qty)
{
    this->level += qty;
    float perc = this->level/this->maxLevel;

    this->btnLevel->SetSize(wxSize(26, 183 * perc));
    this->btnLevel->SetPosition(levelIniPos + wxPoint(0, 183 - this->btnLevel->GetSize().GetHeight()));
    this->lblLevel->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");
}

void Tank::ChooseColor(wxCommandEvent &event) {
    wxColourData data;
    data.SetChooseFull(true);
    data.SetColour(this->color);

    wxColourDialog dialog(this, &data);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxColour c = dialog.GetColourData().GetColour();
        this->color = c;
        this->btnColor->SetBackgroundColour(c);
        this->btnColor->SetLabel(this->GetRGB());
        this->btnLevel->SetBackgroundColour(c);
    }
}
