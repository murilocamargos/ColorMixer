#ifndef _VALVE_H
#define _VALVE_H

//! \class Slider
//! \brief Controle criado para o slider da valvula.
//! \details Serve para salvar no Log quando um usu�rio modifica
//! o grau de abertura de uma v�lvula.
class Slider : public wxSlider
{
private:
    wxWindow *parent;
public:
    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param id ID da janela.
    //! \param value Valor inicial do slider.
    //! \param minValue Valor m�nimo do slider.
    //! \param maxValue Valor maximo do slider.
    //! \param pos Posi��o inicial do slider.
    //! \param size Tamanho do slider.
    //! \param style Estilo do slider.
    //! \details N�o faz nada a n�o ser inicializar um `wxSlider` com os par�metros passados.
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

    //! \brief Salva posi��o final da v�lvula no Log.
    //! \param event Evento de soltura do slider.
    //! \details Ao soltar o slider numa nova posi��o, este m�todo
    //! ser� chamado e ir� salvar no banco de dados um Log determinando
    //! a nova posi��o da v�lvula e o usu�rio que modificou a antiga posi��o.
    void OnReleaseSlider(wxScrollEvent& event);

    DECLARE_EVENT_TABLE()
};

//! \class Valve
//! \brief Controle criado para representar as v�lvulas da planta.
//! \details Serve para encapsular as v�lvulas do sistema fazendo
//! com que o usu�rio n�o precise repetir os c�digos de cria��o e
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
    /// Valor inicial de abertura da v�lvula.
    int value;
    /// Texto que indica o valor inicial de abertura.
    wxStaticText* label;
    /// Usu�rio que est� utilizando a v�lvula.
    std::string uid, log_id;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param value Valor inicial de abertura da v�lvula.
    //! \param uid ID do usu�rio que est� utilizando a v�lvula.
    //! \param log_id ID do Log utilizado para a v�lvula em quest�o.
    //! \param name Nome da pasta onde est�o as imagens que compoem a v�lvula.
    //! \details Cria todos os bot�es, labels e imagens que compoem a v�lvula;
    //! coloca esses elementos em sizers e define um sizer principal para representar
    //! o painel
    Valve(wxWindow *parent, int value, std::string uid, std::string log_id = "0", wxString name = "ValveIn1");

    //! \brief Seta o grau de abertura da v�lvula.
    //! \param value Valor de abertura da v�lvula.
    void SetValve(int value);

    //! \brief Chama o m�todo Valve::SetValve a medida em que o usu�rio modifica o slider.
    //! \param event Evento de scroll sobre o slider.
    void OnChangeSlider(wxScrollEvent &event);

    //! \brief Chama o m�todo Valve::SetValve a medida em que o usu�rio clica sobre a v�lvula.
    //! \param event Evento de clique sobre um bot�o.
    void OnValveClick(wxCommandEvent &event);

    /// Enumera��o das a��es dos bot�es presentes na janela.
    enum {
        CHANGE_SLIDER,
        VALVE_CLICK
    };

    DECLARE_EVENT_TABLE()
};

#endif
