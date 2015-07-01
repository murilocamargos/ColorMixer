#ifndef DIRSELECT_H_
#define DIRSELECT_H_

//! \class DirSelect
//! \brief Permite a sele��o de diret�rios/arquivos.
//! \details Permite que o usu�rio possa selecionar diret�rios e arquivos
//! de maneira simples atrav�s de m�todos est�ticos.
class DirSelect
{
private:
    wxString path;
    wxButton *button;

public:
    DirSelect(){}
    ~DirSelect(){}

    //! \brief Abre di�logo para sele��o de diret�rios.
    //! \param title T�tulo do di�logo.
    //! \param defDir Diret�rio inicial de busca.
    static wxString PathDlg(wxString title = "", wxString defDir = "");

    //! \brief Abre di�logo para sele��o de arquivos.
    //! \param ext Extens�es a serem mostradas para o usu�rio.
    //! \param title T�tulo do di�logo.
    //! \param defDir Diret�rio inicial de busca.
    static wxString FileDlg(wxString ext = "*.*", wxString title = "", wxString defDir = "");
};

#endif // DIRSELECT_H_
