#ifndef _INSERTUSERSCREEN_H
#define _INSERTUSERSCREEN_H

#include <wx/combobox.h>

//! \class InsertUserScreen
//! \brief Tela de adi��o de usu�rios.
//! \details Esta tela est� dispon�vel apenas para usu�rios
//! cujo n�vel de acesso seja de administrador.
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
    //! \param uid ID do usu�rio que abriu a janela.
    //! \param title T�tulo da janela.
    //! \param editId ID do usu�rio a ser editado, caso essa seja a a��o.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param id ID da janela.
    //! \param pos Posi��o inicial da janela.
    //! \param size Tamanho da janela.
    //! \param style Estilo da janela.
    //! \details � no construtor que todos os campos e suas posi��es s�o inicializados.
    InsertUserScreen( std::string uid,
                      const wxString& title,
                      wxWindow* parent,
                      std::string editId = "0",
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxSize( 400,326 ),
                      long style = wxDEFAULT_DIALOG_STYLE);

    ~InsertUserScreen();

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum
    {
        SAVE
    };

    //! \brief Faz o cadastro do usu�rio.
    //! \param event Evento que ocorre ao clicar num `wxButton`.
    //! \details Antes de salvar um usu�rio no banco, o m�todo faz as seguintes
    //! checagens:
    //! - Verifica se todos os campos foram preenchidos;
    //! - Verifica se as senhas digitadas s�o iguais;
    //! - Verifica se o login informado j� n�o est� cadastrado.
    //!
    //! Caso as informa��es fornecidas pelo usu�rio passe nos tr�s testes,
    //! elas ser�o adicionadas ao banco. Uma entrada de Log tamb�m � adicionada.
    void Save(wxCommandEvent& event);

    //! \brief Destr�i a janela ao clicar no s�mbolo "x" padr�o do windows.
    //! \param event Evento de fechamento de janela.
    void OnClose(wxCloseEvent& event);

    DECLARE_EVENT_TABLE();

};

#endif
