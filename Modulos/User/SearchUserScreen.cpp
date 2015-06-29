#include "SearchUserScreen.h"

BEGIN_EVENT_TABLE(SearchUserScreen, wxDialog)
    EVT_BUTTON(SEARCH, SearchUserScreen::Search)
    EVT_BUTTON(EDIT, SearchUserScreen::Edit)
    EVT_BUTTON(DEL, SearchUserScreen::Delete)
    EVT_BUTTON(CANCEL, SearchUserScreen::Cancel)
    EVT_CHOICE(ID, SearchUserScreen::Choice_ID)
    EVT_DATAVIEW_SELECTION_CHANGED(DSC, SearchUserScreen::DataSelected)
END_EVENT_TABLE()

using namespace std;
///Funcao para retornar string correspondente ao wxChoice a fim de fazer pesquisa no BD
std::string int2string(int opc)
{
    std::string ans;
    switch(opc)
    {
    case 0:
        ans = "AND";
    case 1:
        ans = "OR";
    default:
        ans = "*";
    }
    return ans;
}
///Função para formatar dados para pesquisa em BD
std::string str2str(std::string opc)
{
    if (opc == wxEmptyString)
        return "";
    return opc;
}
SearchUserScreen::SearchUserScreen( wxWindow* parent, wxWindowID id, bool btn_e, bool btn_d, const wxString& title,
                                   const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer6->Add( m_staticText2, 0, wxALL, 5 );

	wxString choice_idChoices[] = { wxT("="), wxT("!="), wxT(">"), wxT("<"), wxT(">="), wxT("<="), wxT("Between") };
	int choice_idNChoices = sizeof( choice_idChoices ) / sizeof( wxString );
	choice_id = new wxChoice( this, ID, wxDefaultPosition, wxSize( 110,-1 ), choice_idNChoices, choice_idChoices, 0 );
	choice_id->SetSelection( 0 );
	bSizer6->Add( choice_id, 0, wxALL, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	Input_id = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer7->Add( Input_id, 0, wxALL, 5 );

	Input_id2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	Input_id2->Enable(false);
	bSizer7->Add( Input_id2, 0, wxALL, 5 );


	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice1Choices[] = { wxT("And"), wxT("Or") };
	int choice1NChoices = sizeof( choice1Choices ) / sizeof( wxString );
	choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 50,30 ), choice1NChoices, choice1Choices, 0 );
	choice1->SetSelection( 0 );
	bSizer20->Add( choice1, 0, wxALL, 5 );


	bSizer20->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer20, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Login:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer61->Add( m_staticText21, 0, wxALL, 5 );

	wxString choice_loginChoices[] = { wxT("="), wxT("!="), wxT("Contains"), wxT("Begins with"), wxT("Ends with") };
	int choice_loginNChoices = sizeof( choice_loginChoices ) / sizeof( wxString );
	choice_login = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 110,-1 ), choice_loginNChoices, choice_loginChoices, 0 );
	choice_login->SetSelection( 0 );
	bSizer61->Add( choice_login, 0, wxALL, 5 );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );

	login = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 110,-1 ), 0 );
	bSizer71->Add( login, 0, wxALL, 5 );


	bSizer61->Add( bSizer71, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer61, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxVERTICAL );


	bSizer201->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice2Choices[] = { wxT("And"), wxT("Or") };
	int choice2NChoices = sizeof( choice2Choices ) / sizeof( wxString );
	choice2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 50,30 ), choice2NChoices, choice2Choices, 0 );
	choice2->SetSelection( 0 );
	bSizer201->Add( choice2, 0, wxALL, 5 );


	bSizer201->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer201, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxVERTICAL );

	m_staticText211 = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	bSizer611->Add( m_staticText211, 0, wxALL, 5 );

	wxString choice_nameChoices[] = { wxT("="), wxT("!="), wxT("Contains"), wxT("Begins with"), wxT("Ends with") };
	int choice_nameNChoices = sizeof( choice_nameChoices ) / sizeof( wxString );
	choice_name = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 110,-1 ), choice_nameNChoices, choice_nameChoices, 0 );
	choice_name->SetSelection( 0 );
	bSizer611->Add( choice_name, 0, wxALL, 5 );

	wxBoxSizer* bSizer711;
	bSizer711 = new wxBoxSizer( wxHORIZONTAL );

	username = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 110,-1 ), 0 );
	bSizer711->Add( username, 0, wxALL, 5 );


	bSizer611->Add( bSizer711, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer611, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer202;
	bSizer202 = new wxBoxSizer( wxVERTICAL );


	bSizer202->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice3Choices[] = { wxT("And"), wxT("Or") };
	int choice3NChoices = sizeof( choice3Choices ) / sizeof( wxString );
	choice3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 50,30 ), choice3NChoices, choice3Choices, 0 );
	choice3->SetSelection( 0 );
	bSizer202->Add( choice3, 0, wxALL, 5 );


	bSizer202->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer202, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6111;
	bSizer6111 = new wxBoxSizer( wxVERTICAL );

	m_staticText2111 = new wxStaticText( this, wxID_ANY, wxT("Access Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2111->Wrap( -1 );
	bSizer6111->Add( m_staticText2111, 0, wxALL, 5 );

	wxString choice_alChoices[] = { wxT("="), wxT("!=") };
	int choice_alNChoices = sizeof( choice_alChoices ) / sizeof( wxString );
	choice_al = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 110,-1 ), choice_alNChoices, choice_alChoices, 0 );
	choice_al->SetSelection( 0 );
	bSizer6111->Add( choice_al, 0, wxALL, 5 );

	wxBoxSizer* bSizer7111;
	bSizer7111 = new wxBoxSizer( wxHORIZONTAL );

	wxString acess_levelChoices[] = { wxT("All"), wxT("Admin"), wxT("Manager"), wxT("User") };
	int acess_levelNChoices = sizeof( acess_levelChoices ) / sizeof( wxString );
	acess_level = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 110,-1 ), acess_levelNChoices, acess_levelChoices, 0 );
	acess_level->SetSelection( 0 );
	bSizer7111->Add( acess_level, 0, wxALL, 5 );


	bSizer6111->Add( bSizer7111, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer6111, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer203;
	bSizer203 = new wxBoxSizer( wxVERTICAL );


	bSizer203->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString choice4Choices[] = { wxT("And"), wxT("Or") };
	int choice4NChoices = sizeof( choice4Choices ) / sizeof( wxString );
	choice4 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 50,30 ), choice4NChoices, choice4Choices, 0 );
	choice4->SetSelection( 0 );
	bSizer203->Add( choice4, 0, wxALL, 5 );


	bSizer203->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer203, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxVERTICAL );

	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Registered in:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer62->Add( m_staticText22, 0, wxALL, 5 );

	wxString choice_riChoices[] = { wxT("="), wxT("!="), wxT(">"), wxT("<"), wxT(">="), wxT("<="), wxT("Between") };
	int choice_riNChoices = sizeof( choice_riChoices ) / sizeof( wxString );
	choice_ri = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 180,-1 ), choice_riNChoices, choice_riChoices, 0 );
	choice_ri->SetSelection( 0 );
	bSizer62->Add( choice_ri, 0, wxALL, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	rdate = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT );
	bSizer72->Add( rdate, 0, wxALL, 5 );

	m_datePicker2 = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT );
	m_datePicker2->Enable( false );

	bSizer72->Add( m_datePicker2, 0, wxALL, 5 );


	bSizer62->Add( bSizer72, 1, wxEXPAND, 5 );


	bSizer10->Add( bSizer62, 1, wxEXPAND, 5 );


	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	users_result = new wxDataViewListCtrl( this, DSC, wxDefaultPosition, wxSize( 900,300 ), 0 );
    users_result->AppendTextColumn("User ID");
	users_result->AppendTextColumn("Name");
	users_result->AppendTextColumn("Login");
	users_result->AppendTextColumn("Nivel de Acesso");
	bSizer11->Add( users_result, 0, wxALL, 5 );


	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );


	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	sea = new wxButton( this, SEARCH, wxT("Search"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( sea, 0, wxALL, 5 );

	del = new wxButton( this, DEL, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	del->Enable(btn_d);
	bSizer12->Add( del, 0, wxALL, 5 );

	edit = new wxButton( this, EDIT, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	edit->Enable(btn_e);
	bSizer12->Add( edit, 0, wxALL, 5 );

	cancel = new wxButton( this, CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( cancel, 0, wxALL, 5 );


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
    this->users_result->DeleteAllItems();
    wxVector<wxVariant> data;
    // Define a query sql a ser executada
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();
    std::string Iid = str2str(string(this->Input_id->GetLineText(0).mb_str()));
    std::string login = str2str(string(this->login->GetLineText(0).mb_str()));
    std::string user = str2str(string(this->username->GetLineText(0).mb_str()));
    int alevel = this->acess_level->GetCurrentSelection();
    /**
    alevel :
    0-> All
    1-> Admin
    2-> Manager
    3-> User
    */
    sql ->Table("usuarios")
        ->Where("user_id", Iid)
        ->WhereOr("nome", user)
        ->WhereOr("login", login)
        ->Column("user_id")
        ->Column("nome")
        ->Column("login")
        ->Column("nivel");
    db->Select(sql);
    int nrows = db->NumRows(sql);
    for (int i = 0;i<nrows;i++)
    {
        data.push_back(db->rows[i]["user_id"]);
        data.push_back(db->rows[i]["nome"]);
        data.push_back(db->rows[i]["login"]);
        data.push_back(db->rows[i]["nivel"]);
        this->users_result->AppendItem(data);
        data.clear();
    }
}
void SearchUserScreen::Edit(wxCommandEvent& event)
{
    InsertUserScreen *ins = new InsertUserScreen("1", _("Insert User"), true, uname, ulogin, this);//**Falta acess level!
    ins->SetIcon(wxICON(ADDUS_IC));
    ins->Show(TRUE);
    this->Close();
}
void SearchUserScreen::Delete(wxCommandEvent& event)
{
    // Define a query sql a ser executada
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();
    //Deletar do bd
    sql ->Table("usuarios")
        ->Where("user_id", uid);
    db->Exec(sql->Delete());
    //Deletar da tabela de resposta à busca
    this->users_result->DeleteItem(this->users_result->GetSelectedRow());
}
void SearchUserScreen::Cancel(wxCommandEvent& event)
{
    this->Input_id->Clear();
    this->login->Clear();
    this->username->Clear();
    this->Close();
}

void SearchUserScreen::Choice_ID(wxCommandEvent& event)
{
    this->Input_id2->Enable(this->choice_id->GetCurrentSelection()!= 0 && this->choice_id->GetCurrentSelection() != 1);
    //Esse campo só será desabilitado quando a escolha for "=" ou "!=", onde ele não é necessário.
}

void SearchUserScreen::DataSelected(wxDataViewEvent &event)
{
    if(!edit->IsEnabled()&&!del->IsEnabled())
    {
        edit->Enable(true);
        del->Enable(true);
    }
    int row = users_result->GetSelectedRow();
    uid = users_result->GetTextValue(row,0);
    uname = users_result->GetTextValue(row,1);
    ulogin = users_result->GetTextValue(row,2);
    ual = users_result->GetTextValue(row,3);
}
