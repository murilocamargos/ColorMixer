#ifndef _SQLHandler_H
#define _SQLHandler_H

#include <string>
#include <vector>
#include <map>

typedef struct {
  wxString col, val1, val2, con;
  int opr;
} where;

//! \class SQLHandler
//! \brief Gera comandos SQL.
//! \details Cria strings que representam comandos SQL de inserção,
//! exclusão, edição, leitura e contagem a partir dos parâmetros
//! definidos pelo usuário.
class SQLHandler
{
private:
    //!< String que armazena a tabela a ser utilizada pelo usuário.
    std::string _table;
    //!< Lista com os diversos atributos Where usado na query.
    std::vector<std::string> _where;
    //!< Lista de colunas a serem usadas na query.
    std::vector<std::string> _column;
    //!< Mapa que relaciona uma coluna com seu valor.
    std::map<std::string, std::string> _vars;

    bool join;

    std::map<int, wxString> oprMap;

public:
    //! \brief Define os tipos de operadoes padrão.
    //! \details Os tipos definidos são:
    //! Any, =, !=, >, <, >=, <=, Between, Not between, Contains, Begins with, Ends with.
    SQLHandler();

    //! \brief Obtém um operador.
    //! \param i Índice inteiro do operador na lista.
    //! \return opr O operador em forma de string.
    wxString GetOpr(int i);

    //! \brief Obtém um operador.
    //! \param opr String que determina o operador.
    //! \return i Ínidice inteiro do operador na lista.
    int GetOpr(wxString opr);

    //! \brief Obtém uma lista de operadores.
    //! \param oprs[] Array contendo os índices dos operadores.
    //! \param size Tamanho do array.
    //! \return oprs Uma Array de strings com todos os operadores pedidos.
    wxArrayString GetOpr(int oprs[], int size);

    //! \brief Define parâmetro where de duas datas relacionadas por um operador.
    //! \param opr Índice inteiro do operador na lista de operadores.
    //! \param d1 `wxDateTime` primeira data.
    //! \param d2 `wxDateTime` segunda data.
    //! \return where O where processado a partir do operador.
    //! \details Os operadores gerais não funcionam da mesma forma com datas,
    //! este método encapsula o processamento de duas datas quaisquer a partir
    //! de um operador qualquer.
    static where GetDateWhere(int opr, wxDateTime d1, wxDateTime d2);

    //! \brief Faz a junção de duas tabelas.
    //! \param table Nome da tabela.
    //! \param where Condição de junção.
    //! \return A própria instância.
    SQLHandler* Join(std::string table, std::string where);

    //! \brief Faz a junção natural de duas tabelas.
    //! \param table Nome da tabela.
    //! \return A própria instância.
    SQLHandler* NaturalJoin(std::string table);

    //! \brief Definição da tabela.
    //! \param tableName Nome da tabela a ser utilizada.
    //! \return A própria instância.
    //! \details Define a tabela a ser utilizada na consulta sql.
    SQLHandler* Table(std::string tableName);

    //! \brief Definição da(s) coluna(s) utilizada(s).
    //! \param columnName Nome da coluna no banco.
    //! \return A própria instância.
    //! \details Adiciona a coluna recebida numa lista de strings.
    SQLHandler* Column(std::string columnName);

    //! \brief Obtém as colunas da lista.
    //! \return As colunas da lista separadas por vírgula.
    std::string GetColumn();

    //! \brief Define o parâmetro <b>`where`</b> de uma consulta SQL.
    //! \param info Informações do tipo <b>where</b>.
    //! \return A própria instância.
    //! \details Utiliza o novo tipo de dados <b>where</b> para adicionar
    //! novos parâmetros <b>`where`</b> de uma consulta SQL. A vantagem de sua
    //! utilização, está na adição de novos operadores para consultas, como
    //! o Between, Contains, Begins With e o Ends With.
    //!
    //! O novo tipo <b>where</b> possui os atributos
    //! - `col`: nome da coluna do banco a que se refere.
    //! - `opr`: tipo do operador a ser utilizado.
    //! - `val1`: valor a ser usado na comparação.
    //! - `val2`: segundo valor a ser usado na comparação, caso o usuário
    //!            queira usar o Between.
    //! - `con`: O tipo de conexão entre predicados, AND ou OR.
    SQLHandler* Where(where info);

    //! \brief Define o parâmetro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribuído a esta coluna.
    //! \return A própria instância.
    //! \details Adiciona o predicado numa lista de strings. Este
    //! predicado possui como padrão a preposição <b>AND</b> e o
    //! operador que relaciona os parâmetros <b>column</b> e <b>value</b>
    //! é o de igualdade.
    SQLHandler* Where(std::string column, std::string value);

    //! \brief Define o parâmetro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de relação entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribuído a esta coluna.
    //! \return A própria instância.
    //! \details A única diferença é que, nesse, o operador é definido pelo
    //! usuário.
    SQLHandler* Where(std::string column, std::string signal, std::string value);

    //! \brief Define o parâmetro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribuído a esta coluna.
    //! \return A própria instância.
    //! \details Operador padrão de igualdade e com preposição <b>OR</b>.
    SQLHandler* WhereOr(std::string column, std::string value);

    //! \brief Define o parâmetro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de relação entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribuído a esta coluna.
    //! \return A própria instância.
    //! \details Sem operador padrão e com preposição <b>OR</b>.
    SQLHandler* WhereOr(std::string column, std::string signal, std::string value);

    //! \brief Formata numa string os parâmetros <b>where</b>.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de relação entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribuído a esta coluna.
    //! \return Uma string formatada da seguinte maneira: <b>column signal 'value'</b>.
    //! \details É interessante a implementação de um método único de
    //! formatação, pois é nele que poderemos implementar diretrizes de
    //! segurança que impedem ataques do tipo SQL Injection.
    std::string DefineWhere(std::string column, std::string signal, std::string value);

    //! \brief Obtém todos os predicados <b>where</b> definidos pelo usuário.
    //! \return Uma string conectando todos os predicados <b>where</b>.
    std::string GetWhere();

    //! \brief Insere um item num dicionário com chave e valor do tipo std::string.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribuído a esta coluna.
    //! \return A própria instância.
    SQLHandler* Set(std::string column, std::string value);

    //! \brief Gera o comando SQL de seleção.
    //! \return Uma string que representa o comando SQL de seleção.
    std::string Select();

    //! \brief Gera o comando SQL de exclusão.
    //! \return Uma string que representa o comando SQL de exclusão.
    std::string Delete();

    //! \brief Gera o comando SQL de inserção.
    //! \return Uma string que representa o comando SQL de inserção.
    std::string Insert();

    //! \brief Gera o comando SQL de edição.
    //! \return Uma string que representa o comando SQL de edição.
    std::string Update();

    //! \brief Gera o comando SQL de contagem.
    //! \return Uma string que representa o comando SQL de contagem.
    std::string Count();

    //! \brief Limpa todos os atributos dessa classe
    void Clear();

    //! \example SQLHandlerSet.cpp
    //! \example SQLHandlerWhere.cpp
    //! \example SQLHandlerColumn.cpp
    //! \example SQLHandlerTable.cpp
    //! \example SQLHandlerJoin.cpp
    //! \example SQLHandlerNaturalJoin.cpp
};

#endif
