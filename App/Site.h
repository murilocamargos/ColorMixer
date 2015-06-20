#ifndef _SITE_H
#define _SITE_H

#include "../Controls/Valve.h"
#include "../Controls/Tank.h"
#include "../Modulos/Taskbar/Taskbar.h"

#include "../Modulos/Menu/MyMenu.h"
class Site : public wxFrame
{
private:
    float flow;
    TaskBar *taskbar;
    MyMenu *menu;
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
		void OnExit(wxCloseEvent& event);
		bool CloseFrame();

		///Met�dos do Menu
		void OnMenuFileNew(wxCommandEvent& event);
        void OnMenuFileSave(wxCommandEvent& event);
        void OnMenuFileOpen(wxCommandEvent& event);
        void OnMenuFileQuit(wxCommandEvent& event);
        void OnMenuHelp(wxCommandEvent& event);
        void OnMenuHelpAbout(wxCommandEvent & event);
		//************************

		enum {
            ADVANCE,
            MENU_FILE_NEW,
            MENU_FILE_SAVE,
            MENU_FILE_OPEN,
            MENU_FILE_QUIT,
            MENU_HELP,
            MENU_HELP_ABOUT
		};

		DECLARE_EVENT_TABLE()

};

#endif
