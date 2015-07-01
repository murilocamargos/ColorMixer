#ifndef _TANK_H
#define _TANK_H

#include "ColorSelect.h"

//! \class Tank
//! \brief Controle criado para mostrar tanques de tinta na tela.
//! \details O usu�rio n�o precisar� repetir c�digo na cria��o dos
//! tanques no layout da planta.
class Tank : public wxPanel
{
protected:
    wxStaticBitmap *bmpTop, *bmpLeft, *bmpRight, *bmpBottom, *bmpMiddle, *bmpLevelBottom, *bmpTkLeft, *bmpTkRight;
    wxPoint levelIniPos;
    wxButton *btnLevel;
    wxStaticText *lblLevel;

public:
    /// N�vel atual e m�ximo do tanque.
    float level, maxLevel;
    /// Cor da tinha presente no tanque.
    ColorSelect *btnColor;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param color Cor da tinta no tanque.
    //! \param level N�vel inicial de tinta no tanque.
    //! \param maxLevel N�vel m�ximo de tinta no tanque.
    //! \param name Nome da pasta onde est�o as imagens que compoem o tanque.
    //! \details Cria todos os bot�es, labels e imagens que compoem o tanque;
    //! coloca esses elementos em sizers e define um sizer principal para representar
    //! o painel
    Tank(wxWindow *parent, wxColour color, float level, float maxLevel, wxString name = "Tank1");

    //! \brief Reta o tanque com as vari�veis passadas por par�metro.
    //! \param maxLevel Novo n�vel m�ximo do tanque.
    //! \param color Nova cor de tinta do tanque.
    void Reset(float maxLevel = 0, wxColour color = wxNullColour);

    //! \brief Seta o n�vel de tinta no tanque.
    //! \param qty Novo n�vel de tinta.
    //! \details Ao setar o n�vel do tanque, modifica a label que mostra
    //! a percentual do volume de tinta no tanque e modifica o tamanho do
    //! bot�o que representa o n�vel.
    void SetLevel(float qty);
};

//! \class TankMix
//! \brief Controle criado para representar tanques com duas tintas.
//! \details O terceiro tanque da planta mistura duas tintas.
//! Essa classe ir� representar esse tanque.
class TankMix : public Tank
{
private:
    Tank *t1, *t2;

public:
    /// N�veis das duas tintas separadamente dentro do tanque.
    float lvl_c1, lvl_c2;

    //! \brief Construtor.
    //! \param *parent Ponteiro para o wxWindow pai desta janela.
    //! \param *t1 O primeiro tanque que fornecer� tinta para a mistura.
    //! \param *t2 O segundo tanque que fornecer� tinta para a mistura.
    //! \param level N�vel inicial de tinta no tanque.
    //! \param maxLevel N�vel m�ximo de tinta no tanque.
    //! \param name Nome da pasta onde est�o as imagens que compoem o tanque.
    TankMix(wxWindow *parent, Tank *t1, Tank *t2, float level, float maxLevel, wxString name);

    //! \brief Seta n�vel das duas tintas presentes no tanque.
    //! \param qty_c1 Quantidade da primeira cor.
    //! \param qty_c2 Quantidade da segunda cor.
    void SetLevel(float qty_c1, float qty_c2);

    //! \brief Calcula o percentual da uma das cores em rela��o ao total.
    //! \param ink 1 para a primeira cor e 2 para a segunda.
    //! \return float qtd[ink]/(qtd[ink1] + qtd[ink2])
    float Percent(int ink);

    //! \brief Faz a mistura de cores.
    //! \details Faz a mistura de cores tirando a m�dia ponderada entre a
    //! cor do tanque 1 com a do tanque 2. Os pesos s�o os percentuais de
    //! cada cor calculados pelo m�todo TankMix::Percent.
    void MixColors();
};


#endif

