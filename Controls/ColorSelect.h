#ifndef COLORSELECT_H_
#define COLORSELECT_H_

//! \class ColorSelect
//! \brief Controle criado para escolha de cores.
//! \details É basicamente um botão que permite ao
//! usuário o acesso à paleta de cores do windows.
class ColorSelect : public wxPanel
{
private:
    wxColour color;
    wxButton *button;

public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param *defSize Tamanho padrão do botão que conterá a cor.
    //! \param *defColour Cor padrão do botão.
    //! \param style Estilo do botão.
    //! \details Aqui é criado o sizer que conterá o botão com suas
    //! variáveis iniciais definidas.
    ColorSelect(
        wxWindow *parent,
        wxSize defSize = wxSize(-1, -1),
        wxColour defColour = wxNullColour,
        long style = 0 | wxNO_BORDER
    );

    //! \brief Retorna uma string contendo os valores RGB da cor.
    //! \return wxString String no formato `RGB(%r, %g, %b)`
    wxString GetRGB();

    //! \brief Retorna a cor selecionada pelo usuário.
    //! \return wxColour cor selecionada pelo usuário.
    wxColour GetColor();

    //! \brief Retorna o negativo da cor selecionada pelo usuário.
    //! \return wxColour negativo da cor selecionada pelo usuário.
    wxColour GetDiff();

    //! \brief Retorna a posição na memória da cor selecionada pelo usuário.
    //! \return wxColour posição na memória da cor selecionada pelo usuário.
    wxColour* GetPtr();

    //! \brief Seta uma cor no botão de escolha de cores.
    //! \param color A cor a ser setada.
    //! \details Ao setar a cor, muda o label do botão para a nova cor também.
    void SetColor(wxColour color);

    //! \brief Abre a paleta de cores para que o usuário possa selecionar uma cor.
    //! \param event Evento de clique em botão.
    void ChooseColor(wxCommandEvent &event);

    ~ColorSelect(){}

    /// Enumeração das ações dos botões presentes na janela.
    enum {
        CHOOSE_COLOR
    };

    DECLARE_EVENT_TABLE();
};

#endif // COLORSELECT_H_
