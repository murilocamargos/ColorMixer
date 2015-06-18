#include "TaskBar.h"

BEGIN_EVENT_TABLE(TaskBar, wxTaskBarIcon)
    EVT_TASKBAR_LEFT_DOWN(TaskBar::ShowFrame)
    EVT_TASKBAR_RIGHT_DOWN(TaskBar::ShowMenu)
    EVT_MENU(MENU_TASK_OPEN, TaskBar::Open)
    EVT_MENU(MENU_TASK_CLOSE, TaskBar::Close)
END_EVENT_TABLE()

TaskBar::TaskBar(wxWindow *parent)
{
    this->parent = parent;

    menu = new wxMenu();
    menu->Append(MENU_TASK_OPEN,_("Show window") ,_("Reopen application"));
    menu->Append(MENU_TASK_CLOSE,_("Close window") ,_("Close application"));
}

void TaskBar::ShowFrame(wxTaskBarIconEvent& event)
{
    this->RemoveIcon();
    this->parent->Show(true);
}

void TaskBar::ShowMenu(wxTaskBarIconEvent& event)
{
    this->PopupMenu(menu);
}

void TaskBar::Open(wxCommandEvent& event)
{
    this->RemoveIcon();
    this->parent->Show(true);
}

void TaskBar::Close(wxCommandEvent& event)
{
    this->parent->Close(true);
}

void TaskBar::CloseParent()
{
    wxMessageDialog dlg(this->parent, _("Do you really want to close the app?"), _("Confirmation"), wxYES_NO | wxCANCEL);

    dlg.SetYesNoCancelLabels(_("Close"), _("Minimize"), _("Cancel"));

    int answer = dlg.ShowModal();

    if (answer != wxID_CANCEL)
    {
        if (answer == wxID_NO)
        {
            // Só esconde o frame para não ter de criá-lo novamente
            this->parent->Hide();
            this->SetIcon(wxICON(APP_ICON), _("Library"));
        }
        else
        {
            this->parent->Destroy();
        }
    }
}
