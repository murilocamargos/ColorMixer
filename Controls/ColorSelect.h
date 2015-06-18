#ifndef COLORSELECT_H_
#define COLORSELECT_H_

class ColorSelect : public wxPanel
{
private:
    wxColour color;
    wxButton *button;

public:
    ColorSelect(wxWindow *parent, wxSize defSize = wxSize(-1, -1), wxColour defColour = *wxBLACK, long style = 0 | wxNO_BORDER);

    wxString GetRGB();
    wxColour GetColor();
    wxColour GetDiff();
    wxColour* GetPtr();

    void SetColor(wxColour color);

    ~ColorSelect(){}

    enum {
        CHOOSE_COLOR
    };

    void ChooseColor(wxCommandEvent &event);

    DECLARE_EVENT_TABLE();
};

#endif // COLORSELECT_H_
