#ifndef _SITE_H
#define _SITE_H

#include "../Controls/Valve.h"
#include "../Controls/Tank.h"

class Site : public wxFrame
{
private:
    float flow;
    /*float vio[5] = {0, 0, 0, 0, 0};
    float v100 = 10;
    float max1 = 100, max2 = 100, max3 = 200;
    float vol1 = 0, vol2 = 0, vol3_1 = 0, vol3_2 = 0;
    wxPoint nivel1, nivel2, nivel3;
    wxColour c1, c2, c3;
    */

protected:
    wxStaticBitmap *leftPipe_valvIn1;
    wxStaticBitmap *rightPipe_valvIn1;
    wxStaticBitmap *leftPipe_valvIn2;
    wxStaticBitmap *rightPipe_valvIn2;

    wxStaticBitmap *leftPipe_valvOut1;
    wxStaticBitmap *rightPipe_valvOut1;
    wxStaticBitmap *leftPipe_valvOut2;
    wxStaticBitmap *rightPipe_valvOut2;
    wxStaticBitmap *leftPipe_valvOut3;
    wxStaticBitmap *rightPipe_valvOut3;

    wxButton* btnAdvance;

	Valve *vin1, *vout1, *vin2, *vout2, *vout3;
    Tank *t1, *t2;
    TankMix *t3;

public:

		Site(
            const wxString& title,
            wxApp* app,
            std::string uid,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(1000,732),
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL
        );

		~Site();

		void OnAdvanceTime(wxCommandEvent& event);

		enum {
            ADVANCE
		};

		DECLARE_EVENT_TABLE()

};

#endif

