#include "../../App/Includes.h"
#include "LoginScreen.h"

#include "../Encryption/SHA256.h"

#include "../../App/App.h"
#include "../Log/Log.h"

BEGIN_EVENT_TABLE(LoginScreen, wxDialog)
    EVT_BUTTON(CANCEL, LoginScreen::Cancel)
    EVT_BUTTON(LOGIN, LoginScreen::Login)
    EVT_CLOSE(LoginScreen::OnExit)
END_EVENT_TABLE()

LoginScreen::LoginScreen(const wxString& title, wxApp *app, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, style)
{

    this->lang = ((App*) app)->locale->GetLanguage();
    this->app = app;

    this->langs[wxLANGUAGE_ENGLISH]    = _("English");
    this->langs[wxLANGUAGE_FRENCH]     = _("French");
    this->langs[wxLANGUAGE_PORTUGUESE] = _("Portuguese");
    this->langs[wxLANGUAGE_SPANISH]    = _("Spanish");

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* generalSizer;
    generalSizer = new wxBoxSizer( wxVERTICAL );

    wxGridSizer* textFieldSizer;
    textFieldSizer = new wxGridSizer( 1, 3, 0, 0 );

    wxBoxSizer* usernameSizer;
    usernameSizer = new wxBoxSizer( wxVERTICAL );

    labelUsername = new wxStaticText( this, wxID_ANY, _("Username") + ":", wxPoint( -1,-1 ), wxSize( -1,-1 ), 0 );
    labelUsername->Wrap( -1 );
    usernameSizer->Add( labelUsername, 0, wxALL, 5 );

    inputUsername = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
    usernameSizer->Add( inputUsername, 0, wxALL, 5 );


    textFieldSizer->Add( usernameSizer, 1, wxEXPAND, 5 );

    wxBoxSizer* passwordSizer;
    passwordSizer = new wxBoxSizer( wxVERTICAL );

    labelPassword = new wxStaticText( this, wxID_ANY, _("Password") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelPassword->Wrap( -1 );
    passwordSizer->Add( labelPassword, 0, wxALL, 5 );

    inputPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), wxTE_PASSWORD );
    passwordSizer->Add( inputPassword, 0, wxALL, 5 );


    textFieldSizer->Add( passwordSizer, 1, wxEXPAND, 5 );

    wxBoxSizer* languageSizer;
    languageSizer = new wxBoxSizer( wxVERTICAL );

    labelLanguage = new wxStaticText( this, wxID_ANY, _("Language") + ":", wxDefaultPosition, wxDefaultSize, 0 );
    labelLanguage->Wrap( -1 );
    languageSizer->Add( labelLanguage, 0, wxALL, 5 );

    inputLanguage = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0, NULL, wxCB_READONLY );
    int n = 0, i = 0;
    for (std::map<long, wxString>::iterator it = this->langs.begin(); it != this->langs.end(); ++it)
    {
        inputLanguage->Append(it->second);
        if (it->first == this->lang)
        {
            n = i;
        }
        i++;
    }
    inputLanguage->SetSelection(n);

    languageSizer->Add( inputLanguage, 0, wxALL, 5 );


    textFieldSizer->Add( languageSizer, 1, wxEXPAND, 5 );


    generalSizer->Add( textFieldSizer, 1, wxALL|wxEXPAND, 5 );

    wxBoxSizer* buttonSizer;
    buttonSizer = new wxBoxSizer( wxHORIZONTAL );

    buttonCancel = new wxButton( this, CANCEL, _("Cancel"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
    buttonSizer->Add( buttonCancel, 0, wxALL, 5 );

    buttonLogin = new wxButton( this, LOGIN, _("Login"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
    buttonSizer->Add( buttonLogin, 0, wxALL, 5 );


    generalSizer->Add( buttonSizer, 1, wxALIGN_RIGHT|wxALL, 5 );


    this->SetSizer( generalSizer );
    this->Layout();

    this->Centre( wxBOTH );
}

LoginScreen::~LoginScreen()
{
}

void LoginScreen::OnExit(wxCloseEvent& event)
{
    Destroy();
    event.Skip();
}

void LoginScreen::Cancel(wxCommandEvent& event)
{
    inputUsername->Clear();
    inputPassword->Clear();
    inputLanguage->SetValue(this->langs[this->lang]);
}

void LoginScreen::Login(wxCommandEvent& event)
{
    // Define a query sql a ser executada
    SQLHandler *sql = new SQLHandler();
    std::string username = std::string(inputUsername->GetLineText(0).mb_str());
    std::string password = std::string(inputPassword->GetLineText(0).mb_str());

    sql->Table("usuarios")->Where("login", username)->Where("senha", sha256(password))->Column("user_id");

    // Obtem o idioma escolhido pelo usu�rio
    long choosenLang = -1;
    for (std::map<long, wxString>::iterator it = this->langs.begin(); it != this->langs.end(); ++it)
    {
        if (it->second == inputLanguage->GetValue())
        {
            choosenLang = it->first;
        }
    }
    if (choosenLang == -1)
    {
        choosenLang = wxLANGUAGE_ENGLISH;
    }

    SQLiteHandler *db = new SQLiteHandler();
    db->Select(sql);

    if (db->rows.size() > 0)
    {
        ((App*)app)->OpenFrame(db->rows[0]["user_id"], choosenLang);
        Destroy();
    }
    else
    {
        wxMessageDialog dlg(this, _("There is something wrong with your credentials!"), _("Warning"), wxICON_ERROR);
        dlg.ShowModal();
    }
}
