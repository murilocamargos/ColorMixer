#include "SearchUserScreen.h"
#include "../Log/Log.h"

#include <sstream>

BEGIN_EVENT_TABLE(SearchUserScreen, wxDialog)
    EVT_BUTTON(EDIT, SearchUserScreen::Edit)
    EVT_BUTTON(DEL, SearchUserScreen::Delete)
    EVT_CHOICE(CHOICE_ID_OPR, SearchUserScreen::OnChoiceIDOpr)
    EVT_CHOICE(CHOICE_DATE_OPR, SearchUserScreen::OnChoiceDateOpr)
    EVT_CHOICE(ALL_CHOICE, SearchUserScreen::OnChoice)
    EVT_TEXT(ALL_TEXT_CHANGE, SearchUserScreen::OnTextChange)
    EVT_DATE_CHANGED(ALL_DATE, SearchUserScreen::OnDate)
    EVT_DATAVIEW_SELECTION_CHANGED(DSC, SearchUserScreen::DataSelected)
END_EVENT_TABLE()

using namespace std;

SearchUserScreen::SearchUserScreen( wxWindow* parent,std::string uid, wxWindowID id, const wxString& title,
                                   const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	//this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->uid = uid;
	this->sql = new SQLHandler();
	this->db = new SQLiteHandler();

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("ID") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer6->Add( m_staticText2, 0, wxALL, 5 );

	int oprs1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    wxArrayString choices1 = this->sql->GetOpr( oprs1, 8 );
	choice_id = new wxChoice( this, CHOICE_ID_OPR, wxDefaultPosition, wxSize( 110,-1 ), choices1, 0 );
	choice_id->SetSelection( 0 );
	bSizer6->Add( choice_id, 0, wxALL, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	Input_id = new wxTextCtrl( this, ALL_TEXT_CHANGE, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0, wxTextValidator(wxFILTER_NUMERIC) );
	bSizer7->Add( Input_id, 0, wxALL, 5 );

	Input_id2 = new wxTextCtrl( this, ALL_TEXT_CHANGE, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0, wxTextValidator(wxFILTER_NUMERIC) );
	Input_id2->Enable(false);
	bSizer7->Add( Input_id2, 0, wxALL, 5 );


	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice1Choices[] = { _("And"), _("Or") };
	int choice1NChoices = sizeof( choice1Choices ) / sizeof( wxString );
	choice1 = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 50,30 ), choice1NChoices, choice1Choices, 0 );
	choice1->SetSelection( 0 );
	bSizer20->Add( choice1, 0, wxALL, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer20, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );

	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Login") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer61->Add( m_staticText21, 0, wxALL, 5 );

	int oprs2[] = {1, 2, 9, 10, 11};
    wxArrayString choices2 = this->sql->GetOpr( oprs2, 5 );
	choice_login = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 110,-1 ), choices2, 0 );
	choice_login->SetSelection( 0 );
	bSizer61->Add( choice_login, 0, wxALL, 5 );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );

	login = new wxTextCtrl( this, ALL_TEXT_CHANGE, wxEmptyString, wxDefaultPosition, wxSize( 110,-1 ), 0 );
	bSizer71->Add( login, 0, wxALL, 5 );


	bSizer61->Add( bSizer71, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer61, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxVERTICAL );


	bSizer201->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice2Choices[] = { _("And"), _("Or") };
	int choice2NChoices = sizeof( choice2Choices ) / sizeof( wxString );
	choice2 = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 50,30 ), choice2NChoices, choice2Choices, 0 );
	choice2->SetSelection( 0 );
	bSizer201->Add( choice2, 0, wxALL, 5 );


	bSizer201->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer201, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxVERTICAL );

	m_staticText211 = new wxStaticText( this, wxID_ANY, _("Name") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	bSizer611->Add( m_staticText211, 0, wxALL, 5 );

	int oprs3[] = {1, 2, 9, 10, 11};
    wxArrayString choices3 = this->sql->GetOpr( oprs3, 5 );
	choice_name = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 110,-1 ), choices3, 0 );
	choice_name->SetSelection( 0 );
	bSizer611->Add( choice_name, 0, wxALL, 5 );

	wxBoxSizer* bSizer711;
	bSizer711 = new wxBoxSizer( wxHORIZONTAL );

	username = new wxTextCtrl( this, ALL_TEXT_CHANGE, wxEmptyString, wxDefaultPosition, wxSize( 110,-1 ), 0 );
	bSizer711->Add( username, 0, wxALL, 5 );


	bSizer611->Add( bSizer711, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer611, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer202;
	bSizer202 = new wxBoxSizer( wxVERTICAL );


	bSizer202->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice3Choices[] = { _("And"), wxT("OR") };
	int choice3NChoices = sizeof( choice3Choices ) / sizeof( wxString );
	choice3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 50,30 ), choice3NChoices, choice3Choices, 0 );
	choice3->SetSelection( 0 );
	bSizer202->Add( choice3, 0, wxALL, 5 );


	bSizer202->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer202, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6111;
	bSizer6111 = new wxBoxSizer( wxVERTICAL );

	m_staticText2111 = new wxStaticText( this, wxID_ANY, _("Access Level") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2111->Wrap( -1 );
	bSizer6111->Add( m_staticText2111, 0, wxALL, 5 );

	int oprs4[] = {1, 2};
    wxArrayString choices4 = this->sql->GetOpr( oprs4, 2 );
	choice_al = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 110,-1 ), choices4, 0 );
	choice_al->SetSelection( 0 );
	bSizer6111->Add( choice_al, 0, wxALL, 5 );

	wxBoxSizer* bSizer7111;
	bSizer7111 = new wxBoxSizer( wxHORIZONTAL );

	wxString acess_levelChoices[] = { _("All"), _("Admin"),  _("User") };
	int acess_levelNChoices = sizeof( acess_levelChoices ) / sizeof( wxString );
	access_level = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 110,-1 ), acess_levelNChoices, acess_levelChoices, 0 );
	access_level->SetSelection( 0 );
	bSizer7111->Add( access_level, 0, wxALL, 5 );


	bSizer6111->Add( bSizer7111, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer6111, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer203;
	bSizer203 = new wxBoxSizer( wxVERTICAL );


	bSizer203->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice4Choices[] = { _("And"), _("Or") };
	int choice4NChoices = sizeof( choice4Choices ) / sizeof( wxString );
	choice4 = new wxChoice( this, ALL_CHOICE, wxDefaultPosition, wxSize( 50,30 ), choice4NChoices, choice4Choices, 0 );
	choice4->SetSelection( 0 );
	bSizer203->Add( choice4, 0, wxALL, 5 );


	bSizer203->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer203, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxVERTICAL );

	m_staticText22 = new wxStaticText( this, wxID_ANY, _("Registered in") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer62->Add( m_staticText22, 0, wxALL, 5 );

    int oprs5[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    wxArrayString choices5 = this->sql->GetOpr( oprs5, 9 );
	choice_ri = new wxChoice( this, CHOICE_DATE_OPR, wxDefaultPosition, wxSize( 180,-1 ), choices5, 0 );
	choice_ri->SetSelection( 0 );
	bSizer62->Add( choice_ri, 0, wxALL, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	rdate = new wxDatePickerCtrl( this, ALL_DATE, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT|wxDP_DROPDOWN );
	rdate->Enable( false );
	bSizer72->Add( rdate, 0, wxALL, 5 );

	rdate2 = new wxDatePickerCtrl( this, ALL_DATE, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT|wxDP_DROPDOWN );
	rdate2->Enable( false );
	bSizer72->Add( rdate2, 0, wxALL, 5 );


	bSizer62->Add( bSizer72, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer62, 1, wxEXPAND, 5 );


	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	users_result = new wxDataViewListCtrl( this, DSC, wxDefaultPosition, wxSize( 900,300 ), 0 );
    users_result->AppendTextColumn(_("ID"));
	users_result->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, 150);
	users_result->AppendTextColumn(_("Login"), wxDATAVIEW_CELL_INERT, 150);
	users_result->AppendTextColumn(_("Access level"));
	users_result->AppendTextColumn(_("Registered in"), wxDATAVIEW_CELL_INERT, 150);
	users_result->AppendTextColumn(_("Registered by"), wxDATAVIEW_CELL_INERT, 150);

	this->Populate(sql->Table("usuarios u")
                      ->Join("usuarios v", "u.criado_por = v.user_id")
                      ->Column("u.user_id")
                      ->Column("u.nome")
                      ->Column("u.login")
                      ->Column("u.criado_em")
                      ->Column("u.nivel")
                      ->Column("v.nome as criado_por"));

	bSizer11->Add( users_result, 0, wxALL, 5 );


	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );


	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	del = new wxButton( this, DEL, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	del->Enable(false);
	bSizer12->Add( del, 0, wxALL, 5 );

	edit = new wxButton( this, EDIT, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	edit->Enable(false);
	bSizer12->Add( edit, 0, wxALL, 5 );


	bSizer9->Add( bSizer12, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer9 );
	this->Layout();

	this->Centre( wxBOTH );
}

SearchUserScreen::~SearchUserScreen()
{
}

void SearchUserScreen::Find()
{
    where ID, LOGIN, NAME, LEVEL, DATE;

    /////////////////////////////////////////////////////////////
    wxString uid = this->Input_id->GetValue();
    wxString uid2 = this->Input_id2->GetValue();
    wxString uopr = this->choice_id->GetString(this->choice_id->GetSelection());

    ID.col  = "u.user_id";
    ID.opr  = this->sql->GetOpr(uopr);
    ID.val1 = uid;
    ID.val2 = uid2;
    ID.con  = "AND";
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString lgn = this->login->GetValue();
    wxString lopr = this->choice_login->GetString(this->choice_login->GetSelection());
    wxString lcon = (this->choice1->GetSelection() == 0) ? "AND" : "OR";

    LOGIN.col  = "u.login";
    LOGIN.opr  = this->sql->GetOpr(lopr);
    LOGIN.val1 = lgn;
    LOGIN.val2 = "";
    LOGIN.con  = lcon;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString nome = this->username->GetValue();
    wxString nopr = this->choice_name->GetString(this->choice_name->GetSelection());
    wxString ncon = (this->choice2->GetSelection() == 0) ? "AND" : "OR";

    NAME.col  = "u.nome";
    NAME.opr  = this->sql->GetOpr(nopr);
    NAME.val1 = nome;
    NAME.val2 = "";
    NAME.con  = ncon;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString acs("");
    if (this->access_level->GetSelection() > 0)
        acs = wxString::Format("%i", this->access_level->GetSelection());
    wxString alopr = this->choice_al->GetString(this->choice_al->GetSelection());
    wxString alcon = (this->choice3->GetSelection() == 0) ? "AND" : "OR";

    LEVEL.col  = "u.nivel";
    LEVEL.opr  = this->sql->GetOpr(alopr);
    LEVEL.val1 = acs;
    LEVEL.val2 = "";
    LEVEL.con  = alcon;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString dopr = this->choice_ri->GetString(this->choice_ri->GetSelection());
    wxDateTime d1 = this->rdate->GetValue(), d2 = this->rdate2->GetValue();

    DATE = this->sql->GetDateWhere(this->sql->GetOpr(dopr), d1, d2);

    wxString dcon = (this->choice4->GetSelection() == 0) ? "AND" : "OR";

    DATE.col = "u.criado_em";
    DATE.con = dcon;
    /////////////////////////////////////////////////////////////

    sql->Table("usuarios u")
       ->Join("usuarios v", "u.criado_por = v.user_id")
       ->Column("u.user_id")
       ->Column("u.nome")
       ->Column("u.login")
       ->Column("u.criado_em")
       ->Column("u.nivel")
       ->Column("v.nome as criado_por")
       ->Where(ID)
       ->Where(LOGIN)
       ->Where(NAME)
       ->Where(LEVEL)
       ->Where(DATE);

    this->Populate(sql);
}

void SearchUserScreen::Populate(SQLHandler *sql)
{
    wxDateTime date;

    this->users_result->DeleteAllItems();

    this->db->Select(sql);
    wxVector<wxVariant> data;
    std::map<std::string, wxString> levels;

    levels["1"] = _("Admin");
    levels["2"] = _("User");

    for (unsigned int i = 0; i < this->db->rows.size(); i++)
    {
        date = Log::ToDateTime(wxString(this->db->rows[i]["criado_em"]));

        data.clear();
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["user_id"]))));
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["nome"]))));
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["login"]))));
        data.push_back(wxVariant(levels[this->db->rows[i]["nivel"]]));
        data.push_back(wxVariant(date.FormatISOCombined(' ')));
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["criado_por"]))));
        this->users_result->AppendItem(data);
    }
}


void SearchUserScreen::OnTextChange(wxCommandEvent& event)
{
    this->Find();
}

void SearchUserScreen::Edit(wxCommandEvent& event)
{
    std::string selectedUid = std::string(users_result->GetTextValue(users_result->GetSelectedRow(), 0).mb_str());
    InsertUserScreen *ins = new InsertUserScreen(this->uid, _("Edit User"), this, selectedUid);
    ins->SetIcon(wxICON(ADDUSER_ICON));
    ins->Show(TRUE);
    this->Close();
}

void SearchUserScreen::Delete(wxCommandEvent& event)
{
    wxMessageDialog dlg(this, _("Do you really want to delete this user?"), _("Confirmation"), wxYES_NO);
    int answer = dlg.ShowModal();

    if (answer == wxID_YES)
    {
        std::string selectedUid = std::string(users_result->GetTextValue(users_result->GetSelectedRow(), 0).mb_str());
        std::string selectedLogin = std::string(users_result->GetTextValue(users_result->GetSelectedRow(), 2).mb_str());

        new Log("3", this->uid, selectedLogin);

        this->sql->Table("usuarios")
                 ->Where("user_id", selectedUid);

        db->Exec(sql->Delete());

        this->users_result->DeleteItem(this->users_result->GetSelectedRow());
    }
}

void SearchUserScreen::OnChoiceIDOpr(wxCommandEvent& event)
{
    this->Find();
    int opr = this->sql->GetOpr(this->choice_id->GetString(this->choice_id->GetSelection()));
    this->Input_id->Enable(opr > 0);
    this->Input_id2->Enable((opr == 7 || opr == 8));
}

void SearchUserScreen::OnChoiceDateOpr(wxCommandEvent& event)
{
    this->Find();
    int opr = this->sql->GetOpr(this->choice_ri->GetString(this->choice_ri->GetSelection()));
    this->rdate->Enable(opr > 0);
    this->rdate2->Enable((opr == 7 || opr == 8));
}

void SearchUserScreen::OnChoice(wxCommandEvent& event)
{
    this->Find();
}

void SearchUserScreen::OnDate(wxDateEvent& event)
{
    this->Find();
}

void SearchUserScreen::DataSelected(wxDataViewEvent &event)
{
    edit->Enable(true);
    del->Enable(true);
}

