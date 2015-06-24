#ifndef _SQLHandler_H
#define _SQLHandler_H

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

public:
    SQLHandler();

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

    //! \example SQLHandlerSet.cpp
    //! \example SQLHandlerWhere.cpp
    //! \example SQLHandlerColumn.cpp
    //! \example SQLHandlerTable.cpp
};

#endif
