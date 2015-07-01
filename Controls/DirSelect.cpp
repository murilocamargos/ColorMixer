#include "../App/Includes.h"

#include "DirSelect.h"

#include <wx/dirdlg.h>
#include <wx/filedlg.h>

wxString DirSelect::PathDlg(wxString title, wxString defDir)
{
    if (title == "")
    {
        title = _("Choose directory");
    }
    wxDirDialog dlg(NULL, title, defDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (dlg.ShowModal() == wxID_CANCEL)
        return "";

    return dlg.GetPath();
}

wxString DirSelect::FileDlg(wxString ext, wxString title, wxString defDir)
{
    if (title == "")
    {
        title = _("Choose file");
    }
    wxFileDialog fd(NULL, title, defDir, "", ext, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (fd.ShowModal() == wxID_CANCEL)
        return "";

    return fd.GetPath();
}
