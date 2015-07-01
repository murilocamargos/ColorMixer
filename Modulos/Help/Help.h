#ifndef _HELP_H
#define _HELP_H

#include <wx/html/helpctrl.h>

//! \class Help
//! \brief Configura a ajuda ao usuário.
//! \details Define o diretório onde se encontra os arquivos
//! de ajuda ao usuário.
class Help : public wxHtmlHelpController
{
private:

public:
    //! \brief Contrutor.
    //! \details Define o diretório dos arquivos de ajuda.
    Help();

    //! \brief Mostra o conteúdo na tela.
    void ShowHelp();

    //! \brief Destrói o objeto que representa a janela de ajuda.
    void OnExit();
};

#endif
