#ifndef _TANK_H
#define _TANK_H

class Tank : public wxPanel
{
protected:
    wxPoint levelIniPos;
    wxButton *btnColor, *btnLevel;
    wxStaticText *lblLevel;

    wxStaticBitmap *tankTop;
    wxStaticBitmap *tankLeft;
    wxStaticBitmap *tankRight;
    wxStaticBitmap *tankBottom;

public:
    float level, maxLevel;
    wxColor color;

    Tank(wxWindow *parent, wxColour color, float level, float maxLevel);

    enum {
        CHOOSE_COLOR
    };

    void SetLevel(float qty);
    wxString GetRGB();
    void ChooseColor(wxCommandEvent &event);

    DECLARE_EVENT_TABLE();
};


class TankMix : public Tank
{
private:
    Tank *t1, *t2;

public:
    float lvl_c1, lvl_c2;

    TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel);
    void SetLevel(float qty_c1, float qty_c2);
    float Cont1();
    float Cont2();
    void MixColors();
};


#endif

