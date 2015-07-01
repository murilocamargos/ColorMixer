#ifndef COLORSELECT_H_
#define COLORSELECT_H_

//! \class ColorSelect
//! \brief Controle criado para escolha de cores.
//! \details � basicamente um bot�o que permite ao
//! usu�rio o acesso � paleta de cores do windows.
class ColorSelect : public wxPanel
{
private:
    wxColour color;
    wxButton *button;

public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param *defSize Tamanho padr�o do bot�o que conter� a cor.
    //! \param *defColour Cor padr�o do bot�o.
    //! \param style Estilo do bot�o.
    //! \details Aqui � criado o sizer que conter� o bot�o com suas
    //! vari�veis iniciais definidas.
    ColorSelect(
        wxWindow *parent,
        wxSize defSize = wxSize(-1, -1),
        wxColour defColour = wxNullColour,
        long style = 0 | wxNO_BORDER
    );

    //! \brief Retorna uma string contendo os valores RGB da cor.
    //! \return wxString String no formato `RGB(%r, %g, %b)`
    wxString GetRGB();

    //! \brief Retorna a cor selecionada pelo usu�rio.
    //! \return wxColour cor selecionada pelo usu�rio.
    wxColour GetColor();

    //! \brief Retorna o negativo da cor selecionada pelo usu�rio.
    //! \return wxColour negativo da cor selecionada pelo usu�rio.
    wxColour GetDiff();

    //! \brief Retorna a posi��o na mem�ria da cor selecionada pelo usu�rio.
    //! \return wxColour posi��o na mem�ria da cor selecionada pelo usu�rio.
    wxColour* GetPtr();

    //! \brief Seta uma cor no bot�o de escolha de cores.
    //! \param color A cor a ser setada.
    //! \details Ao setar a cor, muda o label do bot�o para a nova cor tamb�m.
    void SetColor(wxColour color);

    //! \brief Abre a paleta de cores para que o usu�rio possa selecionar uma cor.
    //! \param event Evento de clique em bot�o.
    void ChooseColor(wxCommandEvent &event);

    ~ColorSelect(){}

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum {
        CHOOSE_COLOR
    };

    DECLARE_EVENT_TABLE();
};

#endif // COLORSELECT_H_
