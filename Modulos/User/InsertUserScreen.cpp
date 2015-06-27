#include "InsertUserScreen.h"

#include "../Database/SQLiteHandler.h"
#include "../Database/SQLHandler.h"
#include "../Encryption/SHA256.h"
#include "../Log/Log.h"

BEGIN_EVENT_TABLE(InsertUserScreen, wxDialog)
    EVT_BUTTON(CANCEL, InsertUserScreen::Cancel)
    EVT_BUTTON(SAVE, InsertUserScreen::Save)
END_EVENT_TABLE()

InsertUserScreen::InsertUserScreen( std::string uid, const wxString& title, const wxString& name, const wxString& login, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->uid = uid;
    this->levels["1"] = _("Admin");
    this->levels["2"] = _("Manager");
    this->levels["3"] = _("User");

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );

    labelName = new wxStaticText( this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    labelName->Wrap( -1 );
    bSizer1->Add( labelName, 0, wxALL, 10 );

    inputName = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxSize( 371,-1 ), 0 );
    bSizer1->Add( inputName, 0, wxALL, 10 );

    wxGridSizer* gSizer1;
    gSizer1 = new wxGridSizer( 2, 2, 0, 0 );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    labelLogin = new wxStaticText( this, wxID_ANY, _("Login:"), wxDefaultPosition, wxDefaultSize, 0 );
    labelLogin->Wrap( -1 );
    bSizer2->Add( labelLogin, 0, wxALL, 10 );

    inputLogin = new wxTextCtrl( this, wxID_ANY, login, wxDefaultPosition, wxSize( 175,-1 ), 0 );
    bSizer2->Add( inputLogin, 0, wxALL, 10 );


    gSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    labelLevel = new wxStaticText( this, wxID_ANY, _("Access Level:"), wxDefaultPosition, wxDefaultSize, 0 );
    labelLevel->Wrap( -1 );
    bSizer3->Add( labelLevel, 0, wxALL, 10 );

    inputLevel = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), 0, NULL, wxCB_READONLY );
    for (std::map<std::string, std::string>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        inputLevel->Append(it->second);
    }
    inputLevel->SetSelection( 0 );
    bSizer3->Add( inputLevel, 0, wxALL, 10 );


    gSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxVERTICAL );

    labelPassword = new wxStaticText( this, wxID_ANY, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
    labelPassword->Wrap( -1 );
    bSizer4->Add( labelPassword, 0, wxALL, 10 );

    inputPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), wxTE_PASSWORD );
    bSizer4->Add( inputPassword, 0, wxALL, 10 );


    gSizer1->Add( bSizer4, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxVERTICAL );

    labelPasswordAgain = new wxStaticText( this, wxID_ANY, _("Password Again:"), wxDefaultPosition, wxDefaultSize, 0 );
    labelPasswordAgain->Wrap( -1 );
    bSizer5->Add( labelPasswordAgain, 0, wxALL, 10 );

    inputPasswordAgain = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), wxTE_PASSWORD );
    bSizer5->Add( inputPasswordAgain, 0, wxALL, 10 );


    gSizer1->Add( bSizer5, 1, wxEXPAND, 5 );


    bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer( wxHORIZONTAL );

    buttonCancel = new wxButton( this, CANCEL, _("Erase"), wxDefaultPosition, wxDefaultSize, 0 );
    buttonCancel->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );

    bSizer6->Add( buttonCancel, 0, wxALIGN_BOTTOM|wxALL, 10 );

    buttonSave = new wxButton( this, SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer6->Add( buttonSave, 0, wxALIGN_BOTTOM|wxALL, 10 );


    bSizer1->Add( bSizer6, 1, wxALIGN_RIGHT|wxRIGHT, 0 );


    this->SetSizer( bSizer1 );
    this->Layout();

    this->Centre( wxBOTH );
}

InsertUserScreen::~InsertUserScreen()
{
}

void InsertUserScreen::Cancel(wxCommandEvent& event)
{
    this->inputName->Clear();
    this->inputLogin->Clear();
    this->inputLevel->SetValue(this->levels["1"]);
    this->inputPassword->Clear();
    this->inputPasswordAgain->Clear();
}

void InsertUserScreen::Save(wxCommandEvent& event)
{
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();

    std::string name    = std::string(this->inputName->GetLineText(0).mb_str());
    std::string login   = std::string(this->inputLogin->GetLineText(0).mb_str());
    std::string passwd  = std::string(this->inputPassword->GetLineText(0).mb_str());
    std::string passwd2 = std::string(this->inputPasswordAgain->GetLineText(0).mb_str());
    std::string level = "1";

    for (std::map<std::string, std::string>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        if (it->second == inputLevel->GetValue())
        {
            level = it->first;
            break;
        }
    }

    // Checar se todos os campos foram preenchidos
    if (name == "" || login == "" || passwd == "" || passwd2 == "")
    {
        wxMessageDialog dlg(this, _("You must fill all fields!"), _("Warning"), wxICON_EXCLAMATION);
        dlg.ShowModal();
    }
    // Checar se senhas são iguais
    else if (passwd2 != passwd)
    {
        wxMessageDialog dlg(this, _("The passwords must be equal!"), _("Warning"), wxICON_EXCLAMATION);
        dlg.ShowModal();
    }
    // Checar se login já não está cadastrado
    else if (db->NumRows(sql->Table("usuarios")->Where("login", login)) > 0)
    {
        wxMessageDialog dlg(this, _("This login is already registered!"), _("Warning"), wxICON_EXCLAMATION);
        dlg.ShowModal();
    }
    else
    {
        std::string aux;
        aux = "User created:" + login;
        new Log("1", this->uid, aux);

        sql = new SQLHandler();
        sql->Table("usuarios")
        ->Set("nome", name)
        ->Set("login", login)
        ->Set("senha", sha256(passwd))
        ->Set("criado_em", Log::DateTimeNow())
        ->Set("editado_em", Log::DateTimeNow())
        ->Set("criado_por", this->uid)
        ->Set("editado_por", this->uid)
        ->Set("nivel", level);

        db->Exec(sql->Insert());

        wxMessageDialog dlg(this, _("The user was registered with success!"), _("Success"), wxICON_INFORMATION);
        dlg.ShowModal();
        Close(true);
    }

}
