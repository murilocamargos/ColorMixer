#ifndef DIRSELECT_H_
#define DIRSELECT_H_

//! \class DirSelect
//! \brief Permite a seleção de diretórios/arquivos.
//! \details Permite que o usuário possa selecionar diretórios e arquivos
//! de maneira simples através de métodos estáticos.
class DirSelect
{
private:
    wxString path;
    wxButton *button;

public:
    DirSelect(){}
    ~DirSelect(){}

    //! \brief Abre diálogo para seleção de diretórios.
    //! \param title Título do diálogo.
    //! \param defDir Diretório inicial de busca.
    static wxString PathDlg(wxString title = "", wxString defDir = "");

    //! \brief Abre diálogo para seleção de arquivos.
    //! \param ext Extensões a serem mostradas para o usuário.
    //! \param title Título do diálogo.
    //! \param defDir Diretório inicial de busca.
    static wxString FileDlg(wxString ext = "*.*", wxString title = "", wxString defDir = "");
};

#endif // DIRSELECT_H_
