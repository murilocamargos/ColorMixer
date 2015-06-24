#ifndef _DATABASE_H
#define _DATABASE_H

#include "SQLHandler.h"
#include "sqlite3.h"

//! \class SQLiteHandler
//! \brief API para lidar com o sqlite3.
//! \details Esta classe pode ser vista como uma API
//! para que o usuário não tenha que lidar diretamente
//! com as funções da API para C do sqlite3. Funciona
//! como um `wrapper` do sqlite3 facilitando a obteção de
//! resultados com a menor quantidade de cógidos possível.
class SQLiteHandler {
private:
    sqlite3 *db;
    bool isOpen;
public:
    //! Esta variável armazena os resultados de uma consulta
    //! SQL. É um vetor de mapas. Basicamente, cada linha do
    //! resultado da consulta é um elemento no vetor; elemento
    //! este que é representado por um mapa cuja chave é o nome
    //! da coluna e o valor associado à esta chave é o valor
    //! daquela coluna naquela linha dentro do banco.
    std::vector<std::map<std::string, std::string> > rows;

    //! \brief Construtor.
    //! \details O construtor faz a conexão com o banco, através
    //! do método SQLiteHandler::OpenDB.
    SQLiteHandler();
    ~SQLiteHandler();

    //! \brief Fecha a conexão com o banco.
    void CloseDB();

    //! \brief Abre a conexão com o banco.
    //! \param dbFile nome do arquivo que representa o banco.
    //! \return Valor lógico que define se a conexão teve sucesso ou não.
    bool OpenDB(std::string dbFile);

    //! \brief Obtém o número de linhas afetadas por uma consulta.
    //! \param *sql Ponteiro para um objeto SQLHandler.
    //! \return Número de linhas afetadas por uma consulta.
    int NumRows(SQLHandler *sql);

    //! \brief Realiza uma consulta de seleção.
    //! \param *sql Ponteiro para um objeto SQLHandler.
    //! \return Valor lógico que define se a consulta foi um sucesso ou não.
    //! \details Realiza a consulta e armazena os resultados na variável
    //! rows.
    int Select(SQLHandler *sql);

    //! \brief Executa um query SQL no banco.
    //! \param sql std::string da consulta em questão.
    //! \return Valor lógico que define se a consulta foi um sucesso ou não.
    int Exec(std::string sql);

    //! \example SQLiteHandlerNumRows.cpp
    //! \example SQLiteHandlerSelect.cpp
    //! \example SQLiteHandlerExec.cpp
};

#endif
