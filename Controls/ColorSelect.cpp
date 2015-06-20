#include "../App/Includes.h"

#include "ColorSelect.h"

#include <wx/colourdata.h>
#include <wx/colordlg.h>

BEGIN_EVENT_TABLE(ColorSelect, wxPanel)
    EVT_BUTTON(CHOOSE_COLOR, ColorSelect::ChooseColor)
END_EVENT_TABLE()

ColorSelect::ColorSelect(wxWindow *parent, wxSize defSize, wxColour defColour, long style)
    :wxPanel(parent)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    this->button = new wxButton(this, CHOOSE_COLOR, wxEmptyString, wxDefaultPosition, defSize, style);
    this->SetColor(defColour);

    sizer->Add(this->button, 0, wxALL, 0);

    this->SetSizer(sizer);
    this->Layout();
}

void ColorSelect::SetColor(wxColour color)
{
    this->color = color;
    if (color == wxNullColour)
    {
        this->button->SetBackgroundColour(wxColour(255, 255, 255));
        this->button->SetForegroundColour(wxColour(0, 0, 0));
        this->button->SetLabel(_("None"));
    }
    else
    {
        this->button->SetBackgroundColour(this->color);
        this->button->SetForegroundColour(this->GetDiff());
        this->button->SetLabel(this->GetRGB());
    }
}

wxColour* ColorSelect::GetPtr()
{
    return &this->color;
}

wxColour ColorSelect::GetDiff()
{
    return wxColour(255 - this->color.Red(), 255 - this->color.Green(), 255 - this->color.Blue());
}

wxColour ColorSelect::GetColor()
{
    return this->color;
}

wxString ColorSelect::GetRGB()
{
    return wxString::Format("RGB (%i, %i, %i)", this->color.Red(), this->color.Green(), this->color.Blue());
}

void ColorSelect::ChooseColor(wxCommandEvent &event)
{
    wxColourData data;
    data.SetChooseFull(true);
    data.SetColour(this->color);

    wxColourDialog dialog(this, &data);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxColour c = dialog.GetColourData().GetColour();
        this->SetColor(c);
    }
}
