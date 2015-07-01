#ifndef _SEARCHUSERSCREEN_H
#define _SEARCHUSERSCREEN_H

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dataview.h>
#include <wx/button.h>
#include <wx/dialog.h>

#include "../Database/SQLiteHandler.h"
#include "../Database/SQLHandler.h"
#include "InsertUserScreen.h"
class SearchUserScreen : public wxDialog
{
private:
        std::string uid;

        SQLHandler *sql;
        SQLiteHandler *db;
protected:
		wxStaticText* m_staticText2;
		wxChoice* choice_id;
		wxTextCtrl* Input_id;
		wxTextCtrl* Input_id2;
		wxChoice* choice1;
		wxStaticText* m_staticText21;
		wxChoice* choice_login;
		wxTextCtrl* login;
		wxChoice* choice2;
		wxStaticText* m_staticText211;
		wxChoice* choice_name;
		wxTextCtrl* username;
		wxChoice* choice3;
		wxStaticText* m_staticText2111;
		wxChoice* choice_al;
		wxChoice* access_level;
		wxChoice* choice4;
		wxStaticText* m_staticText22;
		wxChoice* choice_ri;
		wxDatePickerCtrl* rdate;
		wxDatePickerCtrl* rdate2;
		wxDataViewListCtrl* users_result;
		wxButton* sea;
		wxButton* del;
		wxButton* edit;
		wxButton* cancel;

public:
    SearchUserScreen( wxWindow* parent, std::string uid, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 913,464 ), long style = wxDEFAULT_DIALOG_STYLE );
    ~SearchUserScreen();

    void Edit(wxCommandEvent& event);
    void Delete(wxCommandEvent& event);

    void OnChoiceIDOpr(wxCommandEvent& event);
    void OnChoiceDateOpr(wxCommandEvent& event);
    void OnTextChange(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    void OnDate(wxDateEvent& event);
    void DataSelected(wxDataViewEvent &event);

    void Find();
    void Populate(SQLHandler* sql);

    enum
    {
        EDIT,
        DEL,
        DSC,
        CHOICE_ID_OPR,
        CHOICE_DATE_OPR,
        ALL_TEXT_CHANGE,
        ALL_DATE,
        ALL_CHOICE
    };

    DECLARE_EVENT_TABLE();
};
#endif
