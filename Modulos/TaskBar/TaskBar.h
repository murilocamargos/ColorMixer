#ifndef __TASKBAR_H__
#define __TASKBAR_H__

#include <wx/wx.h>
#include <wx/taskbar.h>

//! \class TaskBar
//! \brief Minimiza a aplicação para a TaskBar.
//! \details Esta classe define o menu e as ações do ícone
//! na barra de tarefas.
class TaskBar : public wxTaskBarIcon
{
private:
    wxIcon icone;
    wxWindow *parent;
    wxMenu *menu;
public:
    //! \brief Construtor.
    //! \param parent* Ponteiro para a janela 'pai'.
    TaskBar(wxWindow *parent);

    //! \brief Mostra a janela 'pai'.
    //! \param event Evento que ocorre quando se clica no ícone da taskbar.
    //! \details Este método será chamado quando o usuário clicar com o
    //! botão esquerdo do mouse no ícone da aplicação na taskbar.
    void ShowFrame(wxTaskBarIconEvent& event);

    //! \brief Mostra um menu de opções.
    //! \param event Evento que ocorre quando se clica no ícone da taskbar.
    //! \details Este método será chamado quando o usuário clicar com o
    //! botão direito do mouse no ícone da aplicação na taskbar.
    void ShowMenu(wxTaskBarIconEvent& event);

    //! \brief Fecha completamente a aplicação.
    //! \param event Evento que ocorre quando se clica num `wxMenu`.
    void Close(wxCommandEvent& event);

    //! \brief Mostra novamente a aplicação na tela.
    //! \param event Evento que ocorre quando se clica num `wxMenu`.
    void Open(wxCommandEvent& event);

    /// Constantes que ligam os menusda taskbar às suas ações.
    enum
    {
        MENU_TASK_OPEN,
        MENU_TASK_CLOSE
    };

    DECLARE_EVENT_TABLE();
};

#endif
