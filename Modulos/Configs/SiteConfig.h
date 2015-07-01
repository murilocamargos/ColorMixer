#ifndef __SITECONFIG_H__
#define __SITECONFIG_H__

#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/statline.h>

#include "../../Controls/ColorSelect.h"
#include "../../Controls/DirSelect.h"

//! \class SiteConfig
//! \brief Janela para edição das configurações da planta.
//! \details É responsável por definir as configurações
//! de operação da planta.
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
    //! \param uid ID do usuário que abriu a tela.
    //! \param *cnf Ponteiro para a classe Config.
    //! \param id ID da janela.
    //! \param pos Posição inicial da janela.
    //! \param size Tamanho inicial da janela.
    //! \param style Estilo da janela.
    //! \details É no construtor que todos os campos e suas posições são inicializados.
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

    //! \brief Carrega as informações da classe Config nos campos de entrada.
    void LoadInfo();

    //! \brief Carrega as informações dos campos de entrada na classe Config.
    void PutInfo();

    //! \brief Recarrega as labels da janela com a nova unidade de medida.
    void ReloadLabels();

    //! \brief Insere na tabela de logs do banco de dados quando alguma
    //! alteração é feita nas configurações.
    void InsertLog();

    //! \brief Salva as informações fornecidas pelo usuário no banco da dados.
    //! \param event Evento de clique em botão.
    void Save(wxCommandEvent& event);

    //! \brief Importa um arquivo `.cnf` previamente exportado pelo usuário.
    //! \param event Evento de clique em botão.
    void Import(wxCommandEvent& event);

    //! \brief Exporta um arquivo `.cnf` com as configurações atuais da planta.
    //! \param event Evento de clique em botão.
    void Export(wxCommandEvent& event);

    //! \brief Modifica os labels da janela com a unidade selecionada pelo `wxChoice`.
    //! \param event Evento de seleção num `wxChoice`.
    void ChangeUnit(wxCommandEvent& event);

    //! \brief Destrói a janela ao clicar no símbolo "x" padrão do windows.
    //! \param event Evento de fechamento de janela.
    void OnExit(wxCloseEvent& event);

    /// Enumeração das ações dos botões presentes na janela.
    enum {
        SAVE,
        IMPORT,
        EXPORT,
        CHANGE_UNIT
    };

    DECLARE_EVENT_TABLE();

};

#endif
