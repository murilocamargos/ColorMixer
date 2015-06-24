#include "../App/Includes.h"
#include "Tank.h"

#include <wx/colourdata.h>
#include <wx/colordlg.h>

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

    float perc = (this->maxLevel <= 0) ? 0 : this->level/this->maxLevel;

    this->btnLevel->SetSize(wxSize(26, 183 * perc));
    this->btnLevel->SetPosition(levelIniPos + wxPoint(0, 183 - this->btnLevel->GetSize().GetHeight()));
    this->lblLevel->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");

    this->MixColors();
    this->btnLevel->SetBackgroundColour(this->btnColor->GetColor());
}

void TankMix::MixColors()
{
    wxColour c1 = this->t1->btnColor->GetColor();
    wxColour c2 = this->t2->btnColor->GetColor();

    int r = this->Percent(1) * c1.Red()   + this->Percent(2) * c2.Red();
    int g = this->Percent(1) * c1.Green() + this->Percent(2) * c2.Green();
    int b = this->Percent(1) * c1.Blue()  + this->Percent(2) * c2.Blue();

    if (this->lvl_c1 + this->lvl_c2 != 0)
    {
        this->btnColor->SetColor(wxColour(r, g, b));
    }
}

float TankMix::Percent(int ink)
{
    if (ink == 1)
    {
        return this->lvl_c1/(this->lvl_c1 + this->lvl_c2);
    }
    if (ink == 2)
    {
        return this->lvl_c2/(this->lvl_c1 + this->lvl_c2);
    }
    return -1;
}

Tank::Tank(wxWindow *parent, wxColour color, float level, float maxLevel) : wxPanel(parent)
{
    this->level = level;
    this->maxLevel = maxLevel;

    this->btnColor = new ColorSelect(this, wxSize(115, -1), color);

	this->btnLevel = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 | wxNO_BORDER);
	this->btnLevel->SetMinSize(wxSize(26, 0));
	this->btnLevel->SetBackgroundColour(color);

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

void Tank::Reset(float maxLevel, wxColour color)
{
    this->btnColor->SetColor(color);
    this->maxLevel = maxLevel;
    this->SetLevel(-this->level);
}

void Tank::SetLevel(float qty)
{
    this->level += qty;
    float perc = this->level/this->maxLevel;

    this->btnLevel->SetBackgroundColour(this->btnColor->GetColor());

    this->btnLevel->SetSize(wxSize(26, 183 * perc));
    this->btnLevel->SetPosition(levelIniPos + wxPoint(0, 183 - this->btnLevel->GetSize().GetHeight()));
    this->lblLevel->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");
}
