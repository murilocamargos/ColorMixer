#ifndef _SEARCHUSERSCREEN_H
#define _SEARCHUSERSCREEN_H

#include <wx/wx.h>
#include <wx/dataview.h>//Teve de ser colocado separadamente

#include "InsertUserScreen.h"
class SearchUserScreen : public wxDialog
{
	private:

	protected:
		wxStaticText* staticname;
		wxTextCtrl* username;
		wxButton* searchbtn;
		wxDataViewListCtrl* users_result;
		wxButton* edit;
		wxButton* del;
		wxButton* cancel;

	public:
        //Os botões 'Edit' e 'Delete' são habilitados por padrão
		SearchUserScreen( wxWindow* parent, wxWindowID id = wxID_ANY, bool btn_e = true, bool btn_d = true, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 663,439 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SearchUserScreen();

		void Search(wxCommandEvent& event);
		void Edit(wxCommandEvent& event);
		void Delete(wxCommandEvent& event);
		void Cancel(wxCommandEvent& event);

		enum
		{
		    SEARCH,
		    EDIT,
		    DEL,
		    CANCEL
		};

		DECLARE_EVENT_TABLE();
};
#endif
