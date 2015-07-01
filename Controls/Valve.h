#ifndef _VALVE_H
#define _VALVE_H

//! \class Slider
//! \brief Controle criado para o slider da valvula.
//! \details Serve para salvar no Log quando um usuário modifica
//! o grau de abertura de uma válvula.
class Slider : public wxSlider
{
private:
    wxWindow *parent;
public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param id ID da janela.
    //! \param value Valor inicial do slider.
    //! \param minValue Valor mínimo do slider.
    //! \param maxValue Valor maximo do slider.
    //! \param pos Posição inicial do slider.
    //! \param size Tamanho do slider.
    //! \param style Estilo do slider.
    //! \details Não faz nada a não ser inicializar um `wxSlider` com os parâmetros passados.
    Slider(
        wxWindow *parent,
        wxWindowID id,
        int value,
        int minValue,
        int maxValue,
        const wxPoint &pos=wxDefaultPosition,
        const wxSize &size=wxDefaultSize,
        long style=wxSL_HORIZONTAL
    ) : wxSlider(
        parent,
        id,
        value,
        minValue,
        maxValue,
        pos,
        size,
        style
    ) { this->parent = parent; }

    //! \brief Salva posição final da válvula no Log.
    //! \param event Evento de soltura do slider.
    //! \details Ao soltar o slider numa nova posição, este método
    //! será chamado e irá salvar no banco de dados um Log determinando
    //! a nova posição da válvula e o usuário que modificou a antiga posição.
    void OnReleaseSlider(wxScrollEvent& event);

    DECLARE_EVENT_TABLE()
};

//! \class Valve
//! \brief Controle criado para representar as válvulas da planta.
//! \details Serve para encapsular as válvulas do sistema fazendo
//! com que o usuário não precise repetir os códigos de criação e
//! posicionamento das mesmas.
class Valve : public wxPanel
{
private:
    wxStaticBitmap* bmpTop, *bmpLeft, *bmpRight, *bmpBottom, *bmpMiddle;
    wxStaticText *emptyLabel1, *emptyLabel2;

    Slider *slider;
    wxBitmapButton *valve;
    wxString name;

public:
    /// Valor inicial de abertura da válvula.
    int value;
    /// Texto que indica o valor inicial de abertura.
    wxStaticText* label;
    /// Usuário que está utilizando a válvula.
    std::string uid, log_id;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param value Valor inicial de abertura da válvula.
    //! \param uid ID do usuário que está utilizando a válvula.
    //! \param log_id ID do Log utilizado para a válvula em questão.
    //! \param name Nome da pasta onde estão as imagens que compoem a válvula.
    //! \details Cria todos os botões, labels e imagens que compoem a válvula;
    //! coloca esses elementos em sizers e define um sizer principal para representar
    //! o painel
    Valve(wxWindow *parent, int value, std::string uid, std::string log_id = "0", wxString name = "ValveIn1");

    //! \brief Seta o grau de abertura da válvula.
    //! \param value Valor de abertura da válvula.
    void SetValve(int value);

    //! \brief Chama o método Valve::SetValve a medida em que o usuário modifica o slider.
    //! \param event Evento de scroll sobre o slider.
    void OnChangeSlider(wxScrollEvent &event);

    //! \brief Chama o método Valve::SetValve a medida em que o usuário clica sobre a válvula.
    //! \param event Evento de clique sobre um botão.
    void OnValveClick(wxCommandEvent &event);

    /// Enumeração das ações dos botões presentes na janela.
    enum {
        CHANGE_SLIDER,
        VALVE_CLICK
    };

    DECLARE_EVENT_TABLE()
};

#endif
