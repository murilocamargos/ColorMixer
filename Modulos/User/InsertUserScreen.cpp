#include "../../App/Includes.h"

#include "InsertUserScreen.h"

#include "../Encryption/SHA256.h"
#include "../Log/Log.h"

#include "../../App/Site.h"

BEGIN_EVENT_TABLE(InsertUserScreen, wxDialog)
    EVT_CLOSE(InsertUserScreen::OnClose)
    EVT_BUTTON(SAVE, InsertUserScreen::Save)
END_EVENT_TABLE()

InsertUserScreen::InsertUserScreen( std::string uid, const wxString& title, wxWindow* parent, std::string editId, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->sql = new SQLHandler();
    this->db = new SQLiteHandler();

    this->db->Select(this->sql->Table("usuarios")->Where("user_id", uid));
    this->uidInfo = this->db->rows[0];

    if (editId != "0")
    {
        this->db->Select(this->sql->Table("usuarios")->Where("user_id", editId));
        this->editInfo = this->db->rows[0];
    }

    this->flag = (editId != "0");

    this->levels["1"] = _("User");

    if (this->uidInfo["nivel"] == "1")
    {
        this->levels["2"] = _("Admin");
    }

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );

    labelName = new wxStaticText( this, wxID_ANY, _("Name") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelName->Wrap( -1 );
    bSizer1->Add( labelName, 0, wxALL, 10 );

    inputName = new wxTextCtrl( this, wxID_ANY, name, wxDefaultPosition, wxSize( 371,-1 ), 0, wxTextValidator(wxFILTER_ALPHA));
    bSizer1->Add( inputName, 0, wxALL, 10 );

    wxGridSizer* gSizer1;
    gSizer1 = new wxGridSizer( 2, 2, 0, 0 );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    labelLogin = new wxStaticText( this, wxID_ANY, _("Login") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelLogin->Wrap( -1 );
    bSizer2->Add( labelLogin, 0, wxALL, 10 );

    wxTextValidator text_v(wxFILTER_EMPTY|wxFILTER_EXCLUDE_CHAR_LIST);
    text_v.SetCharExcludes(" ");

    inputLogin = new wxTextCtrl( this, wxID_ANY, login, wxDefaultPosition, wxSize( 175,-1 ), 0, text_v);
    bSizer2->Add( inputLogin, 0, wxALL, 10 );


    gSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    labelLevel = new wxStaticText( this, wxID_ANY, _("Access Level") + ":", wxDefaultPosition, wxDefaultSize, 0 );
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

    labelPassword = new wxStaticText( this, wxID_ANY, _("Password") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelPassword->Wrap( -1 );
    bSizer4->Add( labelPassword, 0, wxALL, 10 );

    inputPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), wxTE_PASSWORD );
    bSizer4->Add( inputPassword, 0, wxALL, 10 );


    gSizer1->Add( bSizer4, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxVERTICAL );

    labelPasswordAgain = new wxStaticText( this, wxID_ANY, _("Password Again") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelPasswordAgain->Wrap( -1 );
    bSizer5->Add( labelPasswordAgain, 0, wxALL, 10 );

    inputPasswordAgain = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 175,-1 ), wxTE_PASSWORD );
    bSizer5->Add( inputPasswordAgain, 0, wxALL, 10 );


    gSizer1->Add( bSizer5, 1, wxEXPAND, 5 );


    bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer( wxHORIZONTAL );

    buttonSave = new wxButton( this, SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
    buttonSave->SetDefault();
    bSizer6->Add( buttonSave, 0, wxALIGN_BOTTOM|wxALL, 10 );


    bSizer1->Add( bSizer6, 1, wxALIGN_RIGHT|wxRIGHT, 0 );

    if (flag)
    {
        this->inputName->SetValue(this->editInfo["nome"]);

        this->inputLogin->SetValue(this->editInfo["login"]);

        int lvl = (this->editInfo["nivel"] == "2") ? 0 : 1;
        this->inputLevel->SetSelection(lvl);
    }


    this->SetSizer( bSizer1 );
    this->Layout();

    this->Centre( wxBOTH );
}

InsertUserScreen::~InsertUserScreen()
{
}

void InsertUserScreen::OnClose(wxCloseEvent& event)
{
    Site *prt = (Site*) this->GetParent();
    prt->Raise();
    Destroy();
}

void InsertUserScreen::Save(wxCommandEvent& event)
{
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();

    std::string name    = std::string(this->inputName->GetLineText(0).mb_str());
    std::string login   = std::string(this->inputLogin->GetLineText(0).mb_str());
    std::string passwd  = std::string(this->inputPassword->GetLineText(0).mb_str());
    std::string passwd2 = std::string(this->inputPasswordAgain->GetLineText(0).mb_str());
    std::string level   = (inputLevel->GetValue() == "Admin") ? "1" : "2";

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
    else if ((db->NumRows(sql->Table("usuarios")->Where("login", login)) > 0) && (login != editInfo["login"]))
    {
        wxMessageDialog dlg(this, _("This login is already registered!"), _("Warning"), wxICON_EXCLAMATION);
        dlg.ShowModal();
    }
    else
    {
        sql = new SQLHandler();
        sql->Table("usuarios")
        ->Set("nome", name)
        ->Set("login", login)
        ->Set("senha", sha256(passwd))
        ->Set("editado_em", Log::DateTimeNow())
        ->Set("editado_por", this->uidInfo["user_id"])
        ->Set("nivel", level);

        if (flag)
        {
            new Log("2", this->uidInfo["user_id"], this->editInfo["login"] + " -> " + login);
            sql->Where("user_id", this->editInfo["user_id"]);
            db->Exec(sql->Update());
        }
        else
        {
            new Log("1", this->uidInfo["user_id"], login);

            sql->Set("criado_por", this->uidInfo["user_id"])
               ->Set("criado_em", Log::DateTimeNow());

            db->Exec(sql->Insert());
        }

        wxString msg = (this->flag) ? _("The user was edited with success!") : _("The user was registered with success!");

        wxMessageDialog dlg(this, msg, _("Success"), wxICON_INFORMATION);
        dlg.ShowModal();
        this->Close(true);
    }

}
