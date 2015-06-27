#include "SearchUserScreen.h"

BEGIN_EVENT_TABLE(SearchUserScreen, wxDialog)
    EVT_BUTTON(SEARCH, SearchUserScreen::Search)
    EVT_BUTTON(EDIT, SearchUserScreen::Edit)
    EVT_BUTTON(DEL, SearchUserScreen::Delete)
    EVT_BUTTON(CANCEL, SearchUserScreen::Cancel)
END_EVENT_TABLE()

SearchUserScreen::SearchUserScreen( wxWindow* parent, wxWindowID id, bool btn_e, bool btn_d, const wxString& title,
                                   const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	bSizer9->SetMinSize( wxSize( 500,400 ) );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	bSizer10->SetMinSize( wxSize( 500,50 ) );
	staticname = new wxStaticText( this, wxID_ANY, _("Username:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticname->Wrap( -1 );
	bSizer10->Add( staticname, 0, wxALL, 9 );

	username = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,-1 ), 0 );
	bSizer10->Add( username, 0, wxALL, 5 );

	searchbtn = new wxButton( this, SEARCH, _("Search"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( searchbtn, 0, wxALL, 5 );


	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	bSizer11->SetMinSize( wxSize( 500,320 ) );
	users_result = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	users_result->SetMinSize( wxSize( 650,300 ) );

	bSizer11->Add( users_result, 0, wxALL, 5 );


	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );


	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	edit = new wxButton( this, EDIT, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	edit->Enable(btn_e);
	bSizer13->Add( edit, 0, wxALL, 5 );

	del = new wxButton( this, DEL, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	del->Enable(btn_d);
	bSizer13->Add( del, 0, wxALL, 5 );

	cancel = new wxButton( this, CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( cancel, 0, wxALL, 5 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );


	bSizer9->Add( bSizer12, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();

	this->Centre( wxBOTH );
}

SearchUserScreen::~SearchUserScreen()
{
}

void SearchUserScreen::Search(wxCommandEvent& event)
{

}
void SearchUserScreen::Edit(wxCommandEvent& event)
{
    InsertUserScreen *ins = new InsertUserScreen("1", _("Insert User"), "Nome", "ID", this);
    ins->SetIcon(wxICON(ADDUS_IC));
    ins->Show(TRUE);
    this->Close();
}
void SearchUserScreen::Delete(wxCommandEvent& event)
{

}
void SearchUserScreen::Cancel(wxCommandEvent& event)
{
    this->username->Clear();
    this->Close();
}
