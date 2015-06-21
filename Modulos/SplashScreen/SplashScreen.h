#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <wx/wx.h>
#include <wx/splash.h>

//! \class SplashScreen
//! \brief Manipulação de SplashScreen.
//! \details Mostra uma imagem antes que o programa abra
//! por completo. Geralmente a imagem irá permanecer na tela
//! até que todos os componentos da aplicação sejam carregados.
class SplashScreen
{
private:
    wxSplashScreen *splash;
    wxBitmap bitmap;
    long time;
public:
    //! \brief Contrutor.
    //! \details Define o tempo em que a SplashScreen ficará na
    //! tela com um padrão de 1seg.
    SplashScreen();

    //! \brief Define qual imagem irá aparecer.
    //! \param filePath Caminho da imagem.
    //! \param type Tipo da imagem a ser usada (Ex.: wxBITMAP_TYPE_BMP)
    //! \details Esta função só funciona com imagens cuja extensão seha BMP.
    void LoadImage(wxString filePath, wxBitmapType type = wxBITMAP_TYPE_BMP);

    //! \brief Define qual imagem irá aparecer.
    //! \param bitmap wxBitmap já carregado préviamente com o caminho da imagem.
    void LoadImage(wxBitmap);

    //! \brief Define um tempo de exibição qualquer.
    //! \param time tempo em milisegundos.
    void SetTime(long time)
    {
        this->time = time;
    }

    //! \brief Mostra a imagem na tela.
    void Show();

    //! \example SplashScreen.cpp
};

#endif

