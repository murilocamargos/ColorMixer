#ifndef MYMENU_H
#define MYMENU_H

#include <string>
#include <map>
#include <wx/wx.h>

//! \class MyMenu
//! \brief Cria a barra de menus e algumas de suas funções.
//! \details Facilita a criação de menus e submenus se
//! comportando como um <i>wrapper</i> da classe <b>wxMenuBar</b>.
//! Serve também para reaproveitamento de código de algumas
//! funcionalidades que podem se repetir em diversos aplicativos.
class MyMenu: public wxMenuBar
{
private:
    std::map<wxString, wxMenu*> menus;
public:
    MyMenu();

    //! \brief Adiciona um menu.
    //! \param label Título do menu adicionado.
    //! \param append Acopla ou não o novo menu à barra de menus.
    //! \return void
    //! \details Inicialmente, o menu será inserido num mapa de menus.
    //! Caso o usuário queria que este seja um menu principal, ele pode
    //! acoplá-lo à barra de menus através do parâmetro <b>append</b>.
    void AddMenu(wxString label, bool append = true);

    //! \brief Adiciona um submenu.
    //! \param menuLabel Título do submenu adicionado.
    //! \param ID Constante que liga o submenu à uma função.
    //! \param label Título do menu ao qual este submenu será acoplado.
    //! \param help Mensagem de ajuda do submenu.
    //! \return void
    void AddSubMenu(wxString menuLabel, int ID, wxString label, wxString help);

    //! \brief Adiciona um submenu.
    //! \param menuLabel Título do menu ao qual este submenu será acoplado.
    //! \param label Título do submenu adicionado.
    //! \param help Mensagem de ajuda do submenu.
    //! \return void
    //! \details Neste caso, o submenu adicionado será um menu préviamente
    //! inserido no dicionário mas não acoplado à barra de menus. O efeito
    //! disso é a criação de um submenu que possui seus submenus.
    void AddSubMenu(wxString menuLabel, wxString label, wxString help);

    //! \brief Adiciona um separador num dos menus.
    //! \param menuLabel Título do menu onde o separador será inserido.
    //! \return void
    void Separator(wxString menuLabel);

    //! \brief Formulário para seleção de um arquivo do computador.
    //! \param title Titulo da nova janela.
    //! \param extensions Extensões de arquivo que o formulário irá suportar.
    //! \param defDir Diretório inicial.
    //! \return O caminho completo do arquivo selecionado em forma de string.
    //! \details Abre  um `wxFileDialog` com titulo, extensões e diretório padrão
    //! passados por parâmetro. Retorna uma `wxString` do caminho completo do
    //! arquivo selecionado.
    wxString FilePath(wxString title, wxString extensions, wxString defDir = "");

    //! \example MyMenu.cpp
};

#endif

