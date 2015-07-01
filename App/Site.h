#ifndef _SITE_H
#define _SITE_H

#include "../Controls/Valve.h"
#include "../Controls/Tank.h"

#include "../Modulos/Taskbar/Taskbar.h"
#include "../Modulos/Menu/MyMenu.h"
#include "../Modulos/User/InsertUserScreen.h"
#include "../Modulos/Help/Help.h"

class SiteLayout : public wxScrolledWindow
{
protected:
    wxStaticBitmap *top, *bottom;

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

    wxBitmapButton* btnAdvance;
    wxBitmapButton* btnInitOpr;

	Valve *vin1, *vout1, *vin2, *vout2, *vout3;
    Tank *t1, *t2;
    TankMix *t3;

    bool *operation;
    Config *cnf;
    std::string uid;
public:
    SiteLayout(wxWindow* parent, bool *operation, Config *cnf, std::string uid, wxWindowID id = wxID_ANY);

    void OnAdvanceTime(wxCommandEvent& event);
    void OnInitOperation(wxCommandEvent& event);

    void Reload();
    void SaveValves();

    enum {
        ADVANCE,
        INITOPR
    };

    DECLARE_EVENT_TABLE()
};


class Site : public wxFrame
{
private:
    TaskBar *taskbar;
    MyMenu *menu;
    wxApp *app;
    Config *cnf;
    std::string uid;
    std::map<std::string, std::string> user_info;
    SiteLayout *layout;

public:
    bool operation;

    Site(
        const wxString& title,
        wxApp* app,
        std::string uid,
        const wxPoint& pos = wxPoint(30,30),
        const wxSize& size = wxSize(1000, 583),
        long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL
    );
    ~Site();


    void OnExit(wxCloseEvent& event);
    void SaveValves();
    bool CloseFrame();
    void Reload();

    ///Metódos do Menu
    void OnMenuFileNew(wxCommandEvent& event);
    void OnMenuFileSave(wxCommandEvent& event);
    void OnMenuFileOpen(wxCommandEvent& event);
    void OnMenuFileQuit(wxCommandEvent& event);
    void OnMenuHelp(wxCommandEvent& event);
    void OnMenuHelpAbout(wxCommandEvent& event);
    void OnMenuSettingsPlant(wxCommandEvent& event);
    void OnMenuUserNew(wxCommandEvent& event);
    void OnMenuUserSearch(wxCommandEvent& event);
    void OnMenuUserEdit(wxCommandEvent& event);
    void OnMenuLogView(wxCommandEvent& event);
    //************************

    enum {
        MENU_FILE_NEW,
        MENU_FILE_SAVE,
        MENU_FILE_OPEN,
        MENU_FILE_QUIT,
        MENU_USER_NEW,
        MENU_USER_SEARCH,
        MENU_USER_EDIT,
        MENU_LOG_VIEW,
        MENU_HELP,
        MENU_HELP_ABOUT,
        MENU_SETTINGS_CONFIG
    };

    DECLARE_EVENT_TABLE()

};

#endif

