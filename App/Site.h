#ifndef _SITE_H
#define _SITE_H

#include "../Controls/Valve.h"
#include "../Controls/Tank.h"

#include "../Modulos/Taskbar/Taskbar.h"
#include "../Modulos/Menu/MyMenu.h"
#include "../Modulos/User/InsertUserScreen.h"
#include "../Modulos/Help/Help.h"

//! \class SiteLayout
//! \brief Cont�m todo o layout da planta.
//! \details � respons�vel por criar o layout da planta de
//! maneira isolada do frame principal.
class SiteLayout : public wxScrolledWindow
{
private:
    wxStaticBitmap *top, *bottom;

    wxBitmapButton* btnAdvance;
    wxBitmapButton* btnInitOpr;

	Valve *vin1, *vout1, *vin2, *vout2, *vout3;
    Tank *t1, *t2;
    TankMix *t3;

    bool *operation;
    Config *cnf;
    std::string uid;
public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param *operation Ponteiro da vari�vel booleana que determina se a planta est� em opera��o ou n�o.
    //! \param *cnf Ponteiro para a classe Config.
    //! \param id ID da janela.
    //! \details � no construtor que todos os campos e suas posi��es s�o inicializados.
    SiteLayout(wxWindow* parent, bool *operation, Config *cnf, std::string uid, wxWindowID id = wxID_ANY);

    //! \brief Faz o papel de threads, onde o usu�rio clica para que o tempo seja avan�ado.
    //! \param event Evento de clique em bot�o.
    //! \details Esta fun��o ir� calcular o volume dos tanques a medida em que o tempo
    //! avance.
    void OnAdvanceTime(wxCommandEvent& event);

    //! \brief Inicializa ou para a opera��o da planta.
    //! \param event Evento de clique em bot�o.
    void OnInitOperation(wxCommandEvent& event);

    //! \brief Recarrega as configura��es da planta depois de terem sido modificadas por uma outra janela.
    void Reload();

    //! \brief Salva o estado das v�lvulas por interm�dio do m�todo Config::SaveValves.
    void SaveValves();

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum {
        ADVANCE,
        INITOPR
    };

    DECLARE_EVENT_TABLE()
};


//! \class Site
//! \brief � o frame principal da aplica��o.
//! \details Cont�m menus, barra de status e o layout
//! da planta.
class Site : public wxFrame
{
private:
    TaskBar *taskbar;
    MyMenu *menu;
    wxApp *app;
    Config *cnf;
    std::string uid;
    std::map<std::string, std::string> user_info;
    SiteLayout *layout;

public:
    /// Vari�vel que determina se a planta est� ou n�o em opera��o.
    bool operation;

    //! \brief Construtor.
    //! \param title T�tulo da janela.
    //! \param *app	Ponteiro para a aplica��o que executa a janela.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param uid ID do usu�rio utilizado para abrir este frame.
    //! \param pos Posi��o inicial da janela.
    //! \param size Tamanho da janela.
    //! \param style Estilo da janela.
    //! \details � no construtor que todos os campos e suas posi��es s�o inicializados.
    Site(
        const wxString& title,
        wxApp* app,
        std::string uid,
        const wxPoint& pos = wxPoint(30,30),
        const wxSize& size = wxSize(1000, 583),
        long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL
    );
    ~Site();

    //! \brief M�todo chamado ao fechar o frame.
    //! \param event Evento de fechamento de janela.
    //! \details Antes de fechar o frame, salva o estado das valvulas
    //! e pergunta ao usu�rio se ele deseja minimizar a aplia��o para a taskbar
    void OnExit(wxCloseEvent& event);

    //! \brief Salva o estado das v�lvulas por interm�dio do m�todo SiteLayout::SaveValves.
    void SaveValves();

    //! \brief Recarrega as configura��es da planta.
    //! \details Recarrega as configura��es da planta depois de terem sido
    //! modificadas por uma outra janela atrav�s do m�todo SiteLayout::Reload.
    void Reload();

    //! \brief Mostra mensagem de novo arquivo.
    void OnMenuFileNew(wxCommandEvent& event);
    //! \brief Mostra mensagem de salvamento.
    void OnMenuFileSave(wxCommandEvent& event);
    //! \brief Mostra caminho de arquivo selecionado pelo Dialog.
    void OnMenuFileOpen(wxCommandEvent& event);
    //! \brief Faz a mesma coisa que Site::OnExit
    void OnMenuFileQuit(wxCommandEvent& event);
    //! \brief Abre livro de ajuda.
    void OnMenuHelp(wxCommandEvent& event);
    //! \brief Mostra mensagem sobre os desenvolvedores.
    void OnMenuHelpAbout(wxCommandEvent& event);
    //! \brief Abre janela de configura��o das vari�veis da planta.
    void OnMenuSettingsPlant(wxCommandEvent& event);
    //! \brief Abre janela de cria��o de novo usu�rio.
    void OnMenuUserNew(wxCommandEvent& event);
    //! \brief Abre janela de busca de usu�rios.
    void OnMenuUserSearch(wxCommandEvent& event);
    //! \brief Abre janela de edi��o de usupario.
    void OnMenuUserEdit(wxCommandEvent& event);
    //! \brief Abre janela para visualiza��o de logs.
    void OnMenuLogView(wxCommandEvent& event);
    //************************

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum {
        MENU_FILE_NEW,
        MENU_FILE_SAVE,
        MENU_FILE_OPEN,
        MENU_FILE_QUIT,
        MENU_USER_NEW,
        MENU_USER_SEARCH,
        MENU_USER_EDIT,
        MENU_LOG_VIEW,
        MENU_HELP,
        MENU_HELP_ABOUT,
        MENU_SETTINGS_CONFIG
    };

    DECLARE_EVENT_TABLE()

};

#endif

