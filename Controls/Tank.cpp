#include "../App/Includes.h"
#include "Tank.h"

#include <wx/colourdata.h>
#include <wx/colordlg.h>

TankMix::TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel, wxString name)
    : Tank(parent, wxNullColour, level, maxLevel, name)
{
    this->t1 = t1;
    this->t2 = t2;
    this->lvl_c1 = this->lvl_c2 = 0;
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

Tank::Tank(wxWindow *parent, wxColour color, float level, float maxLevel, wxString name) : wxPanel(parent)
{
    this->level = level;
    this->maxLevel = maxLevel;

    wxString path = "Images/Site/" + name + "/";

	bmpTop = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "top.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpLeft = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "left.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpRight = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "right.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpMiddle = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "middle.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpLevelBottom = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "level.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpTkLeft = new wxStaticBitmap( this, wxID_ANY, wxBitmap( "Images/Site/tkleft.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpTkRight = new wxStaticBitmap( this, wxID_ANY, wxBitmap( "Images/Site/tkright.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );

    lblLevel = new wxStaticText( this, wxID_ANY, _("Level: 0%"), wxDefaultPosition, wxSize( 95,17 ), 0 );

    this->btnColor = new ColorSelect(this, wxSize(115, -1), color);
    this->btnColor->Enable(false);

	this->btnLevel = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 | wxNO_BORDER);
	this->btnLevel->SetMinSize(wxSize(26, 0));
	this->btnLevel->SetBackgroundColour(color);


    wxFlexGridSizer *levelCont = new wxFlexGridSizer(1, 3, 0, 0);
    levelCont->SetFlexibleDirection(wxBOTH);
	levelCont->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	levelCont->Add( bmpLeft, 0, wxALL, 0 );
	levelCont->Add( lblLevel, 0, wxALL, 2 );
	levelCont->Add( bmpRight, 0, wxALL, 0 );


	wxFlexGridSizer *tank = new wxFlexGridSizer(1, 3, 0, 0);
    tank->SetFlexibleDirection(wxBOTH);
	tank->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    tank->Add( bmpTkLeft, 0, wxALL, 0 );
	tank->Add( btnLevel, 0, wxALL, 0 );
	tank->Add( bmpTkRight, 0, wxALL, 0 );


    wxFlexGridSizer *container = new wxFlexGridSizer(7, 1, 0, 0);
    container->SetFlexibleDirection(wxBOTH);
	container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    container->Add( bmpTop, 0, wxALL, 0 );
    container->Add( levelCont, 0, wxALL, 0 );
    container->Add( bmpLevelBottom, 0, wxALL, 0 );
    container->Add( btnColor, 0, wxALL, 0 );
    container->Add( bmpMiddle, 0, wxALL, 0 );
    container->Add( tank, 0, wxALL, 0 );

    if (wxFileExists(path + "bottom.bmp"))
    {
        bmpBottom = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "bottom.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
        container->Add( bmpBottom, 0, wxALL, 0 );
    }

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
    float perc = (this->maxLevel == 0) ? 0 : this->level/this->maxLevel;

    this->btnLevel->SetBackgroundColour(this->btnColor->GetColor());

    this->btnLevel->SetSize(wxSize(26, 183 * perc));
    this->btnLevel->SetPosition(levelIniPos + wxPoint(0, 183 - this->btnLevel->GetSize().GetHeight()));
    this->lblLevel->SetLabel(_("Nível:") + " " + wxString::Format("%.2f", perc * 100) + "%");
}
