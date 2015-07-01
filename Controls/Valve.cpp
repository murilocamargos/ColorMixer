#include "../App/Includes.h"

#include "../Modulos/Log/Log.h"

#include "Valve.h"

BEGIN_EVENT_TABLE(Valve, wxPanel)
    EVT_COMMAND_SCROLL(CHANGE_SLIDER, Valve::OnChangeSlider)
    EVT_BUTTON(VALVE_CLICK, Valve::OnValveClick)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Slider, wxSlider)
    EVT_SCROLL_THUMBRELEASE(Slider::OnReleaseSlider)
END_EVENT_TABLE()

void Slider::OnReleaseSlider(wxScrollEvent& event)
{
    Valve* prt = (Valve*)this->parent;
    wxString desc = wxString::Format("%i", this->GetValue()) + "%";
    Log(prt->log_id, prt->uid, std::string(desc.mb_str()));
}

Valve::Valve(wxWindow *parent, int value, std::string uid, std::string log_id, wxString name) : wxPanel(parent)
{
    this->log_id = log_id;
    this->uid = uid;
    this->value = 0;
    this->name = name;

    wxString path = "Images/Site/" + name + "/";

	bmpTop    = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "top.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpLeft   = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "left.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpRight  = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "right.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
    bmpMiddle = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "middle.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );

    emptyLabel1 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,4 ), 0 );
    emptyLabel2 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,5 ), 0 );
	label = new wxStaticText( this, wxID_ANY, _("Openness") + ": 0%", wxDefaultPosition, wxDefaultSize, 0 );
	slider = new Slider(this, CHANGE_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(98, -1), wxSL_HORIZONTAL);

	valve = new wxBitmapButton( this, VALVE_CLICK, wxBitmap( path + "closed.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxNO_BORDER );

    this->SetValve(value);

    wxFlexGridSizer* mostrador = new wxFlexGridSizer(4, 1, 0, 0);
    mostrador->SetFlexibleDirection(wxBOTH);
    mostrador->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    mostrador->Add(emptyLabel1, 0, wxALL, 0);
    mostrador->Add(label, 0, wxALIGN_CENTER|wxALL, 0);
    mostrador->Add(emptyLabel2, 0, wxALL, 0);
    mostrador->Add(slider, 0, wxALL, 0 );

    wxFlexGridSizer* abertura = new wxFlexGridSizer(1, 3, 0, 0);
    abertura->SetFlexibleDirection(wxBOTH);
    abertura->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    abertura->Add(bmpLeft, 0, wxALL, 0);
    abertura->Add(mostrador, 1, wxEXPAND, 5);
    abertura->Add(bmpRight, 0, wxALL, 0);

    wxFlexGridSizer *container = new wxFlexGridSizer(5, 1, 0, 0);
    container->SetFlexibleDirection(wxBOTH);
	container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	container->Add(this->bmpTop, 0, wxALL, 0);
	container->Add(abertura, 0, wxALL, 0);
	container->Add(this->bmpMiddle, 0, wxALL, 0);
	container->Add(valve, 0, wxALL, 0);
	if (wxFileExists(path + "bottom.bmp"))
    {
        bmpBottom = new wxStaticBitmap( this, wxID_ANY, wxBitmap( path + "bottom.bmp", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( -1,-1 ), 0 );
        container->Add(this->bmpBottom, 0, wxALL, 0);
    }

    this->SetSizer(container);
    this->Layout();
}

void Valve::SetValve(int value)
{
    wxString path = "Images/Site/" + this->name + "/";

    if (value > 100 || value < 0)
    {
        value = 0;
    }

    if (this->value == 0 && value > 0)
    {
        this->valve->SetBitmap(wxBitmap( path + "opened.bmp", wxBITMAP_TYPE_ANY ));
    }

    this->value = value;
    this->label->SetLabel(_("Openness") + ": " + wxString::Format("%i", value) + "%");
    this->slider->SetValue(value);

    if (this->value == 0)
    {
        this->valve->SetBitmap(wxBitmap( path + "closed.bmp", wxBITMAP_TYPE_ANY ));
    }

}

void Valve::OnChangeSlider(wxScrollEvent &event)
{
    this->SetValve(event.GetPosition());
}

void Valve::OnValveClick(wxCommandEvent &event)
{
    wxString desc = wxString::Format("%i", this->value + 10) + "%";
    Log(this->log_id, this->uid, std::string(desc.mb_str()));

    this->SetValve(this->value + 10);
}
