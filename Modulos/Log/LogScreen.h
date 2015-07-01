#ifndef _LOGSCREEN_H
#define _LOGSCREEN_H

#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dataview.h>
#include <wx/combo.h>

class LogScreen : public wxDialog
{
	private:
        SQLHandler *sql;
        SQLiteHandler *db;
	protected:
		wxStaticText* SFULabel;
		wxChoice* SFUOperator;
		wxComboBox* SFUsers;
		wxChoice* SFConnector1;
		wxStaticText* SFTLabel;
		wxChoice* SFTOperator;
		wxComboBox* SFTypes;
		wxChoice* SFConnector2;
		wxStaticText* SFDLabel;
		wxChoice* SFDOperator;
		wxDatePickerCtrl* SFDatePicker1;
		wxDatePickerCtrl* SFDatePicker2;
		wxDataViewListCtrl* logsTable;
		wxButton* btnExport;

	public:

		LogScreen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 580,470 ), long style = wxDEFAULT_DIALOG_STYLE );
		~LogScreen();



		void OnChoiceOprDate(wxCommandEvent& event);
		void OnChoice(wxCommandEvent& event);
		void OnCombo(wxCommandEvent& event);
		void OnDate(wxDateEvent& event);
		void OnExit(wxCloseEvent& event);
		void OnExport(wxCommandEvent& event);

		void Find();
		void Populate(SQLHandler* sql);

        enum {
            CHOICE_DATE_OPR,
            ALL_CHOICES,
            ALL_COMBO,
            ALL_DATE,
            EXPORT
        };

		DECLARE_EVENT_TABLE()

};

#endif //_LOGSCREEN_H
