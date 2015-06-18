#ifndef DIRSELECT_H_
#define DIRSELECT_H_

class DirSelect
{
private:
    wxString path;
    wxButton *button;

public:
    DirSelect(){}
    ~DirSelect(){}

    static wxString PathDlg(wxString title = _("Choose directory"), wxString defDir = "");
    static wxString FileDlg(wxString ext = "*.*", wxString title = _("Choose file"), wxString defDir = "");
};

#endif // DIRSELECT_H_
