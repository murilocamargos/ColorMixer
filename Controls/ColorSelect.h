#ifndef COLORSELECT_H_
#define COLORSELECT_H_

class ColorSelect : public wxPanel
{
private:
    wxColour color;
    wxButton *button;

public:
    ColorSelect(
        wxWindow *parent,
        wxSize defSize = wxSize(-1, -1),
        wxColour defColour = wxNullColour,
        long style = 0 | wxNO_BORDER
    );

    wxString GetRGB();
    wxColour GetColor();
    wxColour GetDiff();
    wxColour* GetPtr();

    void SetColor(wxColour color);

    void ChooseColor(wxCommandEvent &event);

    ~ColorSelect(){}

    enum {
        CHOOSE_COLOR
    };

    DECLARE_EVENT_TABLE();
};

#endif // COLORSELECT_H_
