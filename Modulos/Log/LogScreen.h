#ifndef _LOGSCREEN_H
#define _LOGSCREEN_H

#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dataview.h>
#include <wx/combo.h>

//! \class LogScreen
//! \brief Janela para visualização de logs.
//! \details Permite ao usuário administrador visualizar todos
//! os logs do sistema e exportá-los.
class LogScreen : public wxDialog
{
private:
    SQLHandler *sql;
    SQLiteHandler *db;
protected:
    wxStaticText* SFULabel;
    wxChoice* SFUOperator;
    wxComboBox* SFUsers;
    wxChoice* SFConnector1;
    wxStaticText* SFTLabel;
    wxChoice* SFTOperator;
    wxComboBox* SFTypes;
    wxChoice* SFConnector2;
    wxStaticText* SFDLabel;
    wxChoice* SFDOperator;
    wxDatePickerCtrl* SFDatePicker1;
    wxDatePickerCtrl* SFDatePicker2;
    wxDataViewListCtrl* logsTable;
    wxButton* btnExport;

public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para a janela pai.
    //! \param id ID da janela.
    //! \param title Titulo da janela.
    //! \param pos Posição inicial da janela.
    //! \param size Tamanho inicial da janela.
    //! \param style Estilo da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
    LogScreen( wxWindow* parent,
               wxWindowID id = wxID_ANY,
               const wxString& title = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxSize( 580,470 ),
               long style = wxDEFAULT_DIALOG_STYLE );
    ~LogScreen();


    //! \brief Mostra os campos necessários ao escolher o operador de data.
    //! \param event Evento de mudança num `wxChoice`.
    //! \details Só habilita o segundo campo de data, caso o usuário escolha
    //! `Between` ou `Not Between` como operadores. Ao modificar o operador
    //! realiza automaticamente uma nova busca.
    void OnChoiceOprDate(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se utilizar um `wxChoice`.
    //! \param event Evento de mudança em `wxChoice`
    void OnChoice(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se utilizar um `wxComboBox`.
    //! \param event Evento de mudança em `wxCombo`
    void OnCombo(wxCommandEvent& event);

    //! \brief Realiza automaticamente uma nova busca ao se modificar algum campo de data.
    //! \param event Evento de mudança em `wxDatePickerCtrl`
    void OnDate(wxDateEvent& event);

    //! \brief Executada ao fechar o frame.
    //! \param event Evento de fechamento de janela.
    void OnExit(wxCloseEvent& event);

    //! \brief Exporta os logs mostrados na tabela para um arquivo `.txt`
    //! \param event Evento de clique em botão.
    void OnExport(wxCommandEvent& event);

    //! \brief Realiza uma busca com os valores dos nos campos de entrada.
    void Find();

    //! \brief Coloca os valores encontrados em LogScreen::Find na tabela.
    //! \param *sql SQLHandler gerado pelos campos de entrada.
    void Populate(SQLHandler* sql);

    /// Enumeração das ações dos botões presentes na janela.
    enum
    {
        CHOICE_DATE_OPR,
        ALL_CHOICES,
        ALL_COMBO,
        ALL_DATE,
        EXPORT
    };

    DECLARE_EVENT_TABLE()

};

#endif //_LOGSCREEN_H
