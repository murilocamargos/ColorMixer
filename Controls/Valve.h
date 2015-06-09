#ifndef _VALVE_H
#define _VALVE_H

class Valve : public wxPanel
{
private:
    wxStaticText* label;
    wxSlider *slider;
    wxBitmapButton *valve;

public:
    int value;

    Valve(wxWindow *parent, int value);

    void SetValve(int value);

    void OnChangeSlider(wxScrollEvent &event);
    void OnValveClick(wxCommandEvent &event);

    enum {
        CHANGE_SLIDER,
        VALVE_CLICK
    };

    DECLARE_EVENT_TABLE()
};

#endif
