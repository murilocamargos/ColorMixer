#ifndef CONFIG_H_
#define CONFIG_H_

//! \class Config
//! \brief Armazena as configurações da planta.
//! \details É responsável por armazenar, salvar, exportar
//! e importar arquivos de configuração da planta.
class Config
{
private:
    wxApp *app;
    SQLHandler *sql;
    SQLiteHandler *db;
    /// Mapa de configurações
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

    //! \brief Inicializa as variáveis.
    //! \param *app Ponteiro para o app.
    //! \details Inicializa as variáveis com valores padrão e
    //! chama o método Config::Load().
    Config(wxApp *app);

    //! \brief Salva variáveis no banco de dados.
    //! \param valves (bool) Vontade do usuário de salvar o estado das válvulas.
    //! \details Salva Todas as configurações modificadas pelo
    //! usuário na tabela `configs` fo banco de dados.
    void Save(bool valves = false);

    //! \brief Carrega variáveis do banco de dados.
    //! \details Carrega todas as configurações que estão salvas
    //! no bando de dados.
    void Load();

    //! \brief Salva o estado de todas as valvulas no banco.
    //! \param vin1 Abertura da válvula de entrada do tanque 1.
    //! \param vout1 Abertura da válvula de saída do tanque 1.
    //! \param vin2 Abertura da válvula de entrada do tanque 2.
    //! \param vout2 Abertura da válvula de saída do tanque 2.
    //! \param vout3 Abertura da válvula de saída do tanque 3.
    void SaveValves(int vin1, int vout1, int vin2, int vout2, int vout3);

    //! \brief Salva as configurações num arquivo `.cnf`.
    //! \param filePath Caminho do arquivo que será criado.
    //! \details Salva as configurações da planta num arquivo
    //! para que o usuário possa carregá-lo posteriormente, se quiser.
    bool SaveFile(wxString filePath);

    //! \brief Carrega as informações de um arquivo `.cnf`
    //! \param filePath Caminho do arquivo que será criado.
    //! \details Carrega as informações contidas num arquivo gerado
    //! pelo método Config::SaveFile(). Verifica a validade do arquivo
    //! através de um identificados colocado no início do mesmo.
    bool LoadFile(wxString filePath);
};

#endif // CONFIG_H_
