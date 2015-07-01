#include "Help.h"
#include <wx/filesys.h>

Help::Help()
{
    this->AddBook(wxString("Modulos\\Help\\HelpTool\\ColorMixer.hhp"), false);
    this->SetTitleFormat(_("Help"));
}

void Help::ShowHelp()
{
    DisplayContents();
}

void Help::OnExit()
{
    delete this;
}
