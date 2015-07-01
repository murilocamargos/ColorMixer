#ifndef _TANK_H
#define _TANK_H

#include "ColorSelect.h"

//! \class Tank
//! \brief Controle criado para mostrar tanques de tinta na tela.
//! \details O usuário não precisará repetir código na criação dos
//! tanques no layout da planta.
class Tank : public wxPanel
{
protected:
    wxStaticBitmap *bmpTop, *bmpLeft, *bmpRight, *bmpBottom, *bmpMiddle, *bmpLevelBottom, *bmpTkLeft, *bmpTkRight;
    wxPoint levelIniPos;
    wxButton *btnLevel;
    wxStaticText *lblLevel;

public:
    /// Nível atual e máximo do tanque.
    float level, maxLevel;
    /// Cor da tinha presente no tanque.
    ColorSelect *btnColor;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param color Cor da tinta no tanque.
    //! \param level Nível inicial de tinta no tanque.
    //! \param maxLevel Nível máximo de tinta no tanque.
    //! \param name Nome da pasta onde estão as imagens que compoem o tanque.
    //! \details Cria todos os botões, labels e imagens que compoem o tanque;
    //! coloca esses elementos em sizers e define um sizer principal para representar
    //! o painel
    Tank(wxWindow *parent, wxColour color, float level, float maxLevel, wxString name = "Tank1");

    //! \brief Reta o tanque com as variáveis passadas por parâmetro.
    //! \param maxLevel Novo nível máximo do tanque.
    //! \param color Nova cor de tinta do tanque.
    void Reset(float maxLevel = 0, wxColour color = wxNullColour);

    //! \brief Seta o nível de tinta no tanque.
    //! \param qty Novo nível de tinta.
    //! \details Ao setar o nível do tanque, modifica a label que mostra
    //! a percentual do volume de tinta no tanque e modifica o tamanho do
    //! botão que representa o nível.
    void SetLevel(float qty);
};

//! \class TankMix
//! \brief Controle criado para representar tanques com duas tintas.
//! \details O terceiro tanque da planta mistura duas tintas.
//! Essa classe irá representar esse tanque.
class TankMix : public Tank
{
private:
    Tank *t1, *t2;

public:
    /// Níveis das duas tintas separadamente dentro do tanque.
    float lvl_c1, lvl_c2;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param *t1 O primeiro tanque que fornecerá tinta para a mistura.
    //! \param *t2 O segundo tanque que fornecerá tinta para a mistura.
    //! \param level Nível inicial de tinta no tanque.
    //! \param maxLevel Nível máximo de tinta no tanque.
    //! \param name Nome da pasta onde estão as imagens que compoem o tanque.
    TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel, wxString name);

    //! \brief Seta nível das duas tintas presentes no tanque.
    //! \param qty_c1 Quantidade da primeira cor.
    //! \param qty_c2 Quantidade da segunda cor.
    void SetLevel(float qty_c1, float qty_c2);

    //! \brief Calcula o percentual da uma das cores em relação ao total.
    //! \param ink 1 para a primeira cor e 2 para a segunda.
    //! \return float qtd[ink]/(qtd[ink1] + qtd[ink2])
    float Percent(int ink);

    //! \brief Faz a mistura de cores.
    //! \details Faz a mistura de cores tirando a média ponderada entre a
    //! cor do tanque 1 com a do tanque 2. Os pesos são os percentuais de
    //! cada cor calculados pelo método TankMix::Percent.
    void MixColors();
};


#endif

