#ifndef __SITECONFIG_H__
#define __SITECONFIG_H__

#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/statline.h>

#include "../../Controls/ColorSelect.h"
#include "../../Controls/DirSelect.h"

class SiteConfig : public wxDialog
{
private:
    wxApp *app;
    Config *cnf;

protected:
    wxStaticText* lblUnits;
    wxStaticText* valvesBlock;
    wxStaticText* lblFlow;
    wxStaticText* lblVolMaxT1;
    wxStaticText* lblColorT1;
    wxStaticText* lblVolMaxT2;
    wxStaticText* lblColorT2;
    wxStaticText* lblVolMaxT3;

    wxChoice* units;

    wxSpinCtrl* flow;
    wxSpinCtrl* volMaxT1;
    wxSpinCtrl* volMaxT2;
    wxSpinCtrl* volMaxT3;

    wxButton* save;
    wxButton* importFile;
    wxButton* exportFile;

    ColorSelect* colorTank1;
    ColorSelect* colorTank2;

public:
    SiteConfig(
        const wxString& title,
        wxApp* app,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxSize(450, 520),
        long style = wxDEFAULT_DIALOG_STYLE
    );

    ~SiteConfig();

    wxStaticText* Title(wxString title, wxString suf = ":");

    void LoadInfo();
    void ReloadLabels();

    void Save(wxCommandEvent& event);
    void Import(wxCommandEvent& event);
    void Export(wxCommandEvent& event);
    void ChangeUnit(wxCommandEvent& event);

    enum {
        SAVE,
        IMPORT,
        EXPORT,
        CHANGE_UNIT
    };

    DECLARE_EVENT_TABLE();

};

#endif
