#ifndef _INSERTUSERSCREEN_H
#define _INSERTUSERSCREEN_H

#include <wx/combobox.h>

//! \class InsertUserScreen
//! \brief Tela de adição de usuários.
//! \details Esta tela está disponível apenas para usuários
//! cujo nível de acesso seja de administrador.
class InsertUserScreen : public wxDialog
{
private:
    std::map<std::string, std::string> levels;
    std::map<std::string, std::string> uidInfo;
    std::map<std::string, std::string> editInfo;

    bool flag;
    wxString name;
    wxString login;

    SQLHandler *sql;
    SQLiteHandler *db;
protected:
    wxStaticText* labelName;
    wxTextCtrl* inputName;
    wxStaticText* labelLogin;
    wxTextCtrl* inputLogin;
    wxStaticText* labelLevel;
    wxComboBox* inputLevel;
    wxStaticText* labelPassword;
    wxTextCtrl* inputPassword;
    wxStaticText* labelPasswordAgain;
    wxTextCtrl* inputPasswordAgain;
    wxButton* buttonSave;

public:

    //! \brief Construtor.
    //! \param uid ID do usuário que abriu a janela.
    //! \param title Título da janela.
    //! \param editId ID do usuário a ser editado, caso essa seja a ação.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param id ID da janela.
    //! \param pos Posição inicial da janela.
    //! \param size Tamanho da janela.
    //! \param style Estilo da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
    InsertUserScreen( std::string uid,
                      const wxString& title,
                      wxWindow* parent,
                      std::string editId = "0",
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxSize( 400,326 ),
                      long style = wxDEFAULT_DIALOG_STYLE);

    ~InsertUserScreen();

    /// Enumeração das ações dos botões presentes na janela.
    enum
    {
        SAVE
    };

    //! \brief Faz o cadastro do usuário.
    //! \param event Evento que ocorre ao clicar num `wxButton`.
    //! \details Antes de salvar um usuário no banco, o método faz as seguintes
    //! checagens:
    //! - Verifica se todos os campos foram preenchidos;
    //! - Verifica se as senhas digitadas são iguais;
    //! - Verifica se o login informado já não está cadastrado.
    //!
    //! Caso as informações fornecidas pelo usuário passe nos três testes,
    //! elas serão adicionadas ao banco. Uma entrada de Log também é adicionada.
    void Save(wxCommandEvent& event);

    //! \brief Destrói a janela ao clicar no símbolo "x" padrão do windows.
    //! \param event Evento de fechamento de janela.
    void OnClose(wxCloseEvent& event);

    DECLARE_EVENT_TABLE();

};

#endif
