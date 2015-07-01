#ifndef _SITE_H
#define _SITE_H

#include "../Controls/Valve.h"
#include "../Controls/Tank.h"

#include "../Modulos/Taskbar/Taskbar.h"
#include "../Modulos/Menu/MyMenu.h"
#include "../Modulos/User/InsertUserScreen.h"
#include "../Modulos/Help/Help.h"

//! \class SiteLayout
//! \brief Contém todo o layout da planta.
//! \details É responsável por criar o layout da planta de
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
    //! \param *operation Ponteiro da variável booleana que determina se a planta está em operação ou não.
    //! \param *cnf Ponteiro para a classe Config.
    //! \param id ID da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
    SiteLayout(wxWindow* parent, bool *operation, Config *cnf, std::string uid, wxWindowID id = wxID_ANY);

    //! \brief Faz o papel de threads, onde o usuário clica para que o tempo seja avançado.
    //! \param event Evento de clique em botão.
    //! \details Esta função irá calcular o volume dos tanques a medida em que o tempo
    //! avance.
    void OnAdvanceTime(wxCommandEvent& event);

    //! \brief Inicializa ou para a operação da planta.
    //! \param event Evento de clique em botão.
    void OnInitOperation(wxCommandEvent& event);

    //! \brief Recarrega as configurações da planta depois de terem sido modificadas por uma outra janela.
    void Reload();

    //! \brief Salva o estado das válvulas por intermédio do método Config::SaveValves.
    void SaveValves();

    /// Enumeração das ações dos botões presentes na janela.
    enum {
        ADVANCE,
        INITOPR
    };

    DECLARE_EVENT_TABLE()
};


//! \class Site
//! \brief É o frame principal da aplicação.
//! \details Contém menus, barra de status e o layout
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
    /// Variável que determina se a planta está ou não em operação.
    bool operation;

    //! \brief Construtor.
    //! \param title Título da janela.
    //! \param *app	Ponteiro para a aplicação que executa a janela.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param uid ID do usuário utilizado para abrir este frame.
    //! \param pos Posição inicial da janela.
    //! \param size Tamanho da janela.
    //! \param style Estilo da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
    Site(
        const wxString& title,
        wxApp* app,
        std::string uid,
        const wxPoint& pos = wxPoint(30,30),
        const wxSize& size = wxSize(1000, 583),
        long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL
    );
    ~Site();

    //! \brief Método chamado ao fechar o frame.
    //! \param event Evento de fechamento de janela.
    //! \details Antes de fechar o frame, salva o estado das valvulas
    //! e pergunta ao usuário se ele deseja minimizar a apliação para a taskbar
    void OnExit(wxCloseEvent& event);

    //! \brief Salva o estado das válvulas por intermédio do método SiteLayout::SaveValves.
    void SaveValves();

    //! \brief Recarrega as configurações da planta.
    //! \details Recarrega as configurações da planta depois de terem sido
    //! modificadas por uma outra janela através do método SiteLayout::Reload.
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
    //! \brief Abre janela de configuração das variáveis da planta.
    void OnMenuSettingsPlant(wxCommandEvent& event);
    //! \brief Abre janela de criação de novo usuário.
    void OnMenuUserNew(wxCommandEvent& event);
    //! \brief Abre janela de busca de usuários.
    void OnMenuUserSearch(wxCommandEvent& event);
    //! \brief Abre janela de edição de usupario.
    void OnMenuUserEdit(wxCommandEvent& event);
    //! \brief Abre janela para visualização de logs.
    void OnMenuLogView(wxCommandEvent& event);
    //************************

    /// Enumeração das ações dos botões presentes na janela.
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

