#ifndef __SITECONFIG_H__
#define __SITECONFIG_H__

#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/statline.h>

#include "../../Controls/ColorSelect.h"
#include "../../Controls/DirSelect.h"

//! \class SiteConfig
//! \brief Janela para edi��o das configura��es da planta.
//! \details � respons�vel por definir as configura��es
//! de opera��o da planta.
class SiteConfig : public wxDialog
{
private:
    wxWindow *parent;
    Config *cnf;
    std::string uid;

protected:
    wxStaticText* lblUnits;
    wxStaticText* valvesBlock;
    wxStaticText* lblFlow;
    wxStaticText* lblVolMaxT1;
    wxStaticText* lblColorT1;
    wxStaticText* lblVolMaxT2;
    wxStaticText* lblColorT2;
    wxStaticText* lblVolMaxT3;

    wxChoice* units;

    wxSpinCtrl* flow;
    wxSpinCtrl* volMaxT1;
    wxSpinCtrl* volMaxT2;
    wxSpinCtrl* volMaxT3;

    wxButton* save;
    wxButton* importFile;
    wxButton* exportFile;

    ColorSelect* colorTank1;
    ColorSelect* colorTank2;

public:
    //! \brief Construtor.
    //! \param title Titulo da janela.
    //! \param *parent Ponteiro para a janela pai.
    //! \param uid ID do usu�rio que abriu a tela.
    //! \param *cnf Ponteiro para a classe Config.
    //! \param id ID da janela.
    //! \param pos Posi��o inicial da janela.
    //! \param size Tamanho inicial da janela.
    //! \param style Estilo da janela.
    //! \details � no construtor que todos os campos e suas posi��es s�o inicializados.
    SiteConfig(
        const wxString& title,
        wxWindow* parent,
        std::string uid,
        Config *cnf,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxSize(450, 520),
        long style = wxDEFAULT_DIALOG_STYLE
    );

    ~SiteConfig();

    //! \brief Retorna um label formatado como titulo.
    //! \param title String do titulo.
    //! \param suf String com o sufixo.
    //! \return title Label alaranjada e em negrito com o titulo e o sufixo.
    wxStaticText* Title(wxString title, wxString suf = ":");

    //! \brief Carrega as informa��es da classe Config nos campos de entrada.
    void LoadInfo();

    //! \brief Carrega as informa��es dos campos de entrada na classe Config.
    void PutInfo();

    //! \brief Recarrega as labels da janela com a nova unidade de medida.
    void ReloadLabels();

    //! \brief Insere na tabela de logs do banco de dados quando alguma
    //! altera��o � feita nas configura��es.
    void InsertLog();

    //! \brief Salva as informa��es fornecidas pelo usu�rio no banco da dados.
    //! \param event Evento de clique em bot�o.
    void Save(wxCommandEvent& event);

    //! \brief Importa um arquivo `.cnf` previamente exportado pelo usu�rio.
    //! \param event Evento de clique em bot�o.
    void Import(wxCommandEvent& event);

    //! \brief Exporta um arquivo `.cnf` com as configura��es atuais da planta.
    //! \param event Evento de clique em bot�o.
    void Export(wxCommandEvent& event);

    //! \brief Modifica os labels da janela com a unidade selecionada pelo `wxChoice`.
    //! \param event Evento de sele��o num `wxChoice`.
    void ChangeUnit(wxCommandEvent& event);

    //! \brief Destr�i a janela ao clicar no s�mbolo "x" padr�o do windows.
    //! \param event Evento de fechamento de janela.
    void OnExit(wxCloseEvent& event);

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum {
        SAVE,
        IMPORT,
        EXPORT,
        CHANGE_UNIT
    };

    DECLARE_EVENT_TABLE();

};

#endif
