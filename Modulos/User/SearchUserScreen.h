#ifndef _SEARCHUSERSCREEN_H
#define _SEARCHUSERSCREEN_H

#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dataview.h>
#include <wx/combo.h>

//! \class SearchUserScreen
//! \brief Janela para visualiza��o dos usu�rios cadastrados.
//! \details Permite ao usu�rio administrador visualizar todos
//! os usu�rios cadastrados e edit�-los ou exclu�-los dos sistema.
class SearchUserScreen : public wxDialog
{
private:
        std::string uid;

        SQLHandler *sql;
        SQLiteHandler *db;
protected:
		wxStaticText* m_staticText2;
		wxChoice* choice_id;
		wxTextCtrl* Input_id;
		wxTextCtrl* Input_id2;
		wxChoice* choice1;
		wxStaticText* m_staticText21;
		wxChoice* choice_login;
		wxTextCtrl* login;
		wxChoice* choice2;
		wxStaticText* m_staticText211;
		wxChoice* choice_name;
		wxTextCtrl* username;
		wxChoice* choice3;
		wxStaticText* m_staticText2111;
		wxChoice* choice_al;
		wxChoice* access_level;
		wxChoice* choice4;
		wxStaticText* m_staticText22;
		wxChoice* choice_ri;
		wxDatePickerCtrl* rdate;
		wxDatePickerCtrl* rdate2;
		wxDataViewListCtrl* users_result;
		wxButton* sea;
		wxButton* del;
		wxButton* edit;
		wxButton* cancel;

public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para a janela pai.
    //! \param uid ID do usu�rio que abriu essa janela.
    //! \param id ID da janela.
    //! \param title Titulo da janela.
    //! \param pos Posi��o inicial da janela.
    //! \param size Tamanho inicial da janela.
    //! \param style Estilo da janela.
    //! \details � no construtor que todos os campos e suas posi��es s�o inicializados.
    SearchUserScreen( wxWindow* parent,
                      std::string uid,
                      wxWindowID id = wxID_ANY,
                      const wxString& title = wxEmptyString,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxSize( 913,464 ),
                      long style = wxDEFAULT_DIALOG_STYLE );
    ~SearchUserScreen();

    //! \brief Abre a janela de adi��o de usu�rios com um flag para edi��o.
    //! \param event Evento de clique em bot�o.
    void Edit(wxCommandEvent& event);

    //! \brief Exclui usu�rio.
    //! \param event Evento de clique em bot�o.
    //! \details Antes de excluir pergunta se o usu�rio realmente seja concluir
    //! a a��o.
    void Delete(wxCommandEvent& event);

    //! \brief Mostra os campos necess�rios ao escolher o operador de ID.
    //! \param event Evento de mudan�a num `wxChoice`.
    //! \details S� habilita o segundo campo de de ID, caso o usu�rio escolha
    //! `Between` ou `Not Between` como operadores. Ao modificar o operador
    //! realiza automaticamente uma nova busca.
    void OnChoiceIDOpr(wxCommandEvent& event);

    //! \brief Mostra os campos necess�rios ao escolher o operador de data.
    //! \param event Evento de mudan�a num `wxChoice`.
    //! \details S� habilita o segundo campo de data, caso o usu�rio escolha
    //! `Between` ou `Not Between` como operadores. Ao modificar o operador
    //! realiza automaticamente uma nova busca.
    void OnChoiceDateOpr(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se modificar algum campo de texto.
    //! \param event Evento de mudan�a em `wxTextCtrl`
    void OnTextChange(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se utilizar um `wxChoice`.
    //! \param event Evento de mudan�a em `wxChoice`
    void OnChoice(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se modificar algum campo de data.
    //! \param event Evento de mudan�a em `wxDatePickerCtrl`
    void OnDate(wxDateEvent& event);

    //! \brief Habilita os bot�es `Edit` e `Delete` caso o usu�rio selecione algum
    //! usu�rio da tabela.
    void DataSelected(wxDataViewEvent &event);

    //! \brief Realiza uma busca com os valores dos nos campos de entrada.
    void Find();

    //! \brief Coloca os valores encontrados em SearchUserScreen::Find na tabela.
    //! \param *sql SQLHandler gerado pelos campos de entrada.
    void Populate(SQLHandler* sql);

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum
    {
        EDIT,
        DEL,
        DSC,
        CHOICE_ID_OPR,
        CHOICE_DATE_OPR,
        ALL_TEXT_CHANGE,
        ALL_DATE,
        ALL_CHOICE
    };

    DECLARE_EVENT_TABLE();
};
#endif
