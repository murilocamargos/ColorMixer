#include "SplashScreen.h"

/**
 * O construtor define um segundo como tempo padrão de exibição da imagem na te-
 * la.
 */
SplashScreen::SplashScreen()
{
    this->time = 1000; // 1 seg.
}


/**
 * Carrega imagens à partir do caminho dado.
 */
void SplashScreen::LoadImage(wxString filePath, wxBitmapType type)
{
    this->bitmap.LoadFile(filePath, type);
}

/**
 * Caso o usuário já tenha um objeto do tipo wxBitmap, ele poderá utilizá-lo.
 */
void SplashScreen::LoadImage(wxBitmap bitmap)
{
    this->bitmap = bitmap;
}

/**
 * Mostra efetivamente a imagem na tela.
 */
void SplashScreen::Show()
{
    if (this->bitmap.IsOk())
    {
        this->splash = new wxSplashScreen(bitmap,
                                          wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
                                          this->time, NULL, -1, wxDefaultPosition, wxDefaultSize,
                                          wxBORDER_NONE|wxSTAY_ON_TOP);
    }
}
