#ifndef _TANK_H
#define _TANK_H

#include "ColorSelect.h"

class Tank : public wxPanel
{
protected:
    wxPoint levelIniPos;
    wxButton *btnLevel;
    wxStaticText *lblLevel;

    wxStaticBitmap *tankTop;
    wxStaticBitmap *tankLeft;
    wxStaticBitmap *tankRight;
    wxStaticBitmap *tankBottom;

public:
    float level, maxLevel;
    ColorSelect *btnColor;

    Tank(wxWindow *parent, wxColour color, float level, float maxLevel);

    void Reset(float maxLevel = 0, wxColour color = wxNullColour);

    void SetLevel(float qty);
};


class TankMix : public Tank
{
private:
    Tank *t1, *t2;

public:
    float lvl_c1, lvl_c2;

    TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel);
    void SetLevel(float qty_c1, float qty_c2);
    float Percent(int ink);
    void MixColors();
};


#endif

