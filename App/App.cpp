#include "Includes.h"
#include "App.h"
#include "../Modulos/SplashScreen/SplashScreen.h"
#include "../Modulos/Login/LoginScreen.h"
#include "Site.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
    this->SetLocale(this->LoadLang());

    /*
    ///SplashScreen
    SplashScreen *splash = new SplashScreen();
    splash->LoadImage(wxBITMAP(SPLBMP));
    splash->SetTime(2000);
    splash->Show();
    */
    /*
    /// Tela de login
    LoginScreen *login = new LoginScreen(_("Login"), this);

    login->SetIcon(wxICON(LOGIN_IC));
    login->Show(TRUE);

    SetTopWindow(login);
    */

    this->OpenFrame("1", wxLANGUAGE_PORTUGUESE);


    /*
    Exemplo de utilização do no SQLHandler
    //////////////////////////////////////
    SQLHandler *sql = new SQLHandler();
    SQLiteHandler *db = new SQLiteHandler();

    where ID, NAME;

    ID.name = "user_id";
    ID.signal = "Between";
    ID.val_1 = "30";
    ID.val_2 = "35";
    ID.connector = "AND";

    NAME.name = "nome";
    NAME.signal = "Contains";
    NAME.val_1 = "Lu";
    NAME.val_2 = "";
    NAME.connector = "OR";

    wxLogMessage(wxString(sql->Table("usuarios")->Where(ID)->Where(NAME)->Select()));
    //wxLogMessage(wxString::Format("%i", db->NumRows(sql->Table("usuarios")->Where(ID)->Where(NAME))));
    */

    return true;

}

int App::OnExit()
{
    // Salva ultimo idioma utilizado pelo usuário
    /*wxConfig config(GetAppName());
    long language = (this->locale->GetLanguage());
    config.Write(wxT("wxTranslation_Language"), language);
    config.Flush();
    */
    return 1;
}

long App::LoadLang()
{
    wxConfig config(GetAppName());
    long language;
    if(!config.Read(wxT("wxTranslation_Language"), &language, wxLANGUAGE_PORTUGUESE))
    {
        language = wxLANGUAGE_PORTUGUESE;
    }
    return language;
}

bool App::SetLocale(long lang)
{
    // A  internacionalização só irá funcionar se a pasta ./Languages estiver no
    // mesmo  diretório  que  o executável. Nos testes, o executável se encontra
    // em ./Output/MingW
    this->locale = new wxLocale(lang);

    // Busca pelos arquivos de tradução nos diretórios abaixo.
    this->locale->AddCatalogLookupPathPrefix(wxT("./Languages"));
    this->locale->AddCatalogLookupPathPrefix(wxT("../../Languages"));

    this->locale->AddCatalog(wxT("App"));

    return this->locale->IsOk();
}

bool App::OpenFrame(std::string uid, long lang)
{
    this->SetLocale(lang);

    Site *frame = new Site(_("ColorMixer"), this, uid);
    frame->SetIcon(wxICON(APP_ICON));
    frame->Show(TRUE);
    frame->Maximize();

    SetTopWindow(frame);

    return true;
}
