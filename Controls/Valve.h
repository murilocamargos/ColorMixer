#ifndef _VALVE_H
#define _VALVE_H

class Slider : public wxSlider
{
private:
    wxWindow *parent;
public:
    Slider(
        wxWindow *parent,
        wxWindowID id,
        int value,
        int minValue,
        int maxValue,
        const wxPoint &pos=wxDefaultPosition,
        const wxSize &size=wxDefaultSize,
        long style=wxSL_HORIZONTAL
    ) : wxSlider(
        parent,
        id,
        value,
        minValue,
        maxValue,
        pos,
        size,
        style
    ) { this->parent = parent; }

    void OnReleaseSlider(wxScrollEvent& event);

    DECLARE_EVENT_TABLE()
};

class Valve : public wxPanel
{
private:

    Slider *slider;
    wxBitmapButton *valve;

public:
    int value;
    wxStaticText* label;
    std::string uid, log_id;

    Valve(wxWindow *parent, int value, std::string uid, std::string log_id = "0");

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
