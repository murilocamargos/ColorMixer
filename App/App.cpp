#include "Includes.h"
#include "App.h"
#include "../Modulos/SplashScreen/SplashScreen.h"
#include "../Modulos/Login/LoginScreen.h"
#include "Site.h"


#include "../Modulos/Log/LogScreen.h"

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

    //this->OpenFrame("1", wxLANGUAGE_PORTUGUESE);
    LogScreen *frame = new LogScreen(NULL, wxID_ANY, _("Log"));
    frame->SetIcon(wxICON(LOG_ICON));
    frame->Show(TRUE);
    SetTopWindow(frame);

    return true;

}

int App::OnExit()
{
    // Salva ultimo idioma utilizado pelo usu�rio
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
    // A  internacionaliza��o s� ir� funcionar se a pasta ./Languages estiver no
    // mesmo  diret�rio  que  o execut�vel. Nos testes, o execut�vel se encontra
    // em ./Output/MingW
    this->locale = new wxLocale(lang);

    // Busca pelos arquivos de tradu��o nos diret�rios abaixo.
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
