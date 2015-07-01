#ifndef CONFIG_H_
#define CONFIG_H_

//! \class Config
//! \brief Armazena as configura��es da planta.
//! \details � respons�vel por armazenar, salvar, exportar
//! e importar arquivos de configura��o da planta.
class Config
{
private:
    wxApp *app;
    SQLHandler *sql;
    SQLiteHandler *db;
    /// Mapa de configura��es
    std::map<std::string, std::string> cnfs;

public:
    int      volumeUnit,
             valveMaxFlow,
             tank1MaxVol,
             tank2MaxVol,
             tank3MaxVol,
             vin1,
             vout1,
             vin2,
             vout2,
             vout3,
             id;

    wxColour tank1Color,
             tank2Color;

    //! \brief Inicializa as vari�veis.
    //! \param *app Ponteiro para o app.
    //! \details Inicializa as vari�veis com valores padr�o e
    //! chama o m�todo Config::Load().
    Config(wxApp *app);

    //! \brief Salva vari�veis no banco de dados.
    //! \param valves (bool) Vontade do usu�rio de salvar o estado das v�lvulas.
    //! \details Salva Todas as configura��es modificadas pelo
    //! usu�rio na tabela `configs` fo banco de dados.
    void Save(bool valves = false);

    //! \brief Carrega vari�veis do banco de dados.
    //! \details Carrega todas as configura��es que est�o salvas
    //! no bando de dados.
    void Load();

    //! \brief Salva o estado de todas as valvulas no banco.
    //! \param vin1 Abertura da v�lvula de entrada do tanque 1.
    //! \param vout1 Abertura da v�lvula de sa�da do tanque 1.
    //! \param vin2 Abertura da v�lvula de entrada do tanque 2.
    //! \param vout2 Abertura da v�lvula de sa�da do tanque 2.
    //! \param vout3 Abertura da v�lvula de sa�da do tanque 3.
    void SaveValves(int vin1, int vout1, int vin2, int vout2, int vout3);

    //! \brief Salva as configura��es num arquivo `.cnf`.
    //! \param filePath Caminho do arquivo que ser� criado.
    //! \details Salva as configura��es da planta num arquivo
    //! para que o usu�rio possa carreg�-lo posteriormente, se quiser.
    bool SaveFile(wxString filePath);

    //! \brief Carrega as informa��es de um arquivo `.cnf`
    //! \param filePath Caminho do arquivo que ser� criado.
    //! \details Carrega as informa��es contidas num arquivo gerado
    //! pelo m�todo Config::SaveFile(). Verifica a validade do arquivo
    //! atrav�s de um identificados colocado no in�cio do mesmo.
    bool LoadFile(wxString filePath);
};

#endif // CONFIG_H_
