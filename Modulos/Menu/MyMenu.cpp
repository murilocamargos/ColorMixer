#include "MyMenu.h"

MyMenu::MyMenu() : wxMenuBar()
{
}

void MyMenu::AddMenu(wxString label, bool append)
{
    wxMenu *menu = new wxMenu();
    menus[label] = menu;

    if (append)
        this->Append(menu, label);
}

void MyMenu::AddSubMenu(wxString menuLabel, int ID, wxString label, wxString help)
{

    if (menus.find(menuLabel) != menus.end())
        menus[menuLabel]->Append(ID, label, help);

}

void MyMenu::AddSubMenu(wxString menuLabel, wxString label, wxString help) {
    if (menus.find(menuLabel) != menus.end()
            && menus.find(label) != menus.end())
        menus[menuLabel]->AppendSubMenu(menus[label], label, help);
}

void MyMenu::Separator(wxString menuLabel)
{
    if (menus.find(menuLabel) != menus.end())
        menus[menuLabel]->AppendSeparator();
}

wxString MyMenu::FilePath(wxString title, wxString extensions, wxString defDir)
{

    wxFileDialog fd(this, title, defDir, "", extensions,
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (fd.ShowModal() == wxID_CANCEL)
        return "";

    return fd.GetPath();

}
