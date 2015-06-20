#include "../App/Includes.h"
#include "Valve.h"

BEGIN_EVENT_TABLE(Valve, wxPanel)
    EVT_COMMAND_SCROLL(CHANGE_SLIDER, Valve::OnChangeSlider)
    EVT_BUTTON(VALVE_CLICK, Valve::OnValveClick)
END_EVENT_TABLE()

Valve::Valve(wxWindow *parent, int value) : wxPanel(parent)
{
    this->value  = 0;
    this->label  = new wxStaticText(this, wxID_ANY, _("Abertura:") + " 0%", wxDefaultPosition, wxDefaultSize, 0);
	this->slider = new wxSlider(this, CHANGE_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(95, -1), wxSL_HORIZONTAL);
    this->valve  = new wxBitmapButton(this, VALVE_CLICK, wxBITMAP(CLOSED_VALVE), wxDefaultPosition, wxDefaultSize, wxNO_BORDER); //new wxStaticBitmap(this, wxID_ANY, wxBITMAP(CLOSED_VALVE), wxDefaultPosition, wxDefaultSize, 0);

    this->SetValve(value);

    // -----------------
    wxFlexGridSizer *container = new wxFlexGridSizer(3, 1, 0, 0);

    container->SetFlexibleDirection(wxBOTH);
	container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    container->Add(this->label, 0, wxALL, 5);
    container->Add(this->slider, 0, wxALL, 0);
    container->Add(this->valve, 0, wxALIGN_BOTTOM|wxALL, 0);

    this->SetSizer(container);
}

void Valve::SetValve(int value)
{
    if (value > 100 || value < 0)
    {
        value = 0;
    }

    if (this->value == 0 && value > 0)
    {
        this->valve->SetBitmap(wxBITMAP(OPENED_VALVE));
    }

    this->value = value;
    this->label->SetLabel(_("Abertura:") + " " + wxString::Format("%i", value) + "%");
    this->slider->SetValue(value);

    if (this->value == 0)
    {
        this->valve->SetBitmap(wxBITMAP(CLOSED_VALVE));
    }

}

void Valve::OnChangeSlider(wxScrollEvent &event)
{
    this->SetValve(event.GetPosition());
}

void Valve::OnValveClick(wxCommandEvent &event)
{
    this->SetValve(this->value + 10);
}