#ifndef _LOGIN_H
#define _LOGIN_H

#include <wx/wx.h>
#include<map>
#include <string>

//! \class LoginScreen
//! \brief Tela de login da aplicação.
//! \details Tela inicial da aplicação, onde o usuário informa
//! seu login, senha e o idioma desejado.
class LoginScreen : public wxDialog
{
private:
    std::map<long, wxString> langs;
    long lang;
    wxApp *app;

protected:
    wxStaticText* labelUsername;
    wxTextCtrl* inputUsername;
    wxStaticText* labelPassword;
    wxTextCtrl* inputPassword;
    wxStaticText* labelLanguage;
    wxComboBox* inputLanguage;
    wxButton* buttonCancel;
    wxButton* buttonLogin;

public:
    //! \brief Construtor.
    //! \param title Título da janela.
    //! \param *app	Ponteiro para a aplicação que executa a janela.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param id ID da janela.
    //! \param pos Posição inicial da janela.
    //! \param size Tamanho da janela.
    //! \param style Estilo da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
    LoginScreen(const wxString& title,
                wxApp *app,
                wxWindow* parent = NULL,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize(495,144),
                long style = wxDEFAULT_DIALOG_STYLE);

    ~LoginScreen();

    //! \brief Fecha a janela.
    //! \param event Evento que ocorre ao fechar a janela.
    //! \details Fecha a janela e a aplicação por completo.
    void OnExit(wxCloseEvent& event);

    /// Enumeração das ações dos botões presentes na janela.
    enum
    {
        CANCEL,
        LOGIN
    };

    //! \brief Cancela preenchimento.
    //! \param event Evento que ocorre ao clicar num `wxButton`.
    //! \details Este método simplesmente limpa tudo que o usuário digitou
    //! nos campos de login e senha, e set o idioma padrão no wxComboBox.
    void Cancel(wxCommandEvent& event);

    //! \brief Faz o login do usuário.
    //! \param event Evento que ocorre ao clicar num `wxButton`.
    //! \details Este método verifica o login e a senha digitados pelo usuário.
    //! Com a classe SHA256 obtém-se o hash da senha e então verifica-se se aquela
    //! combinação de login e senha existe no banco. Caso exista, o metodo
    //! MyApp::OpenFrame é chamado com os parêmetros de inicialização. Também é
    //! registrado um Log dessa ação.
    void Login(wxCommandEvent& event);

    DECLARE_EVENT_TABLE();

};

#endif

