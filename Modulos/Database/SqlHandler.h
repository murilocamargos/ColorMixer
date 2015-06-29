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
//! \details Cria strings que representam comandos SQL de inser��o,
//! exclus�o, edi��o, leitura e contagem a partir dos par�metros
//! definidos pelo usu�rio.
class SQLHandler
{
private:
    //!< String que armazena a tabela a ser utilizada pelo usu�rio.
    std::string _table;
    //!< Lista com os diversos atributos Where usado na query.
    std::vector<std::string> _where;
    //!< Lista de colunas a serem usadas na query.
    std::vector<std::string> _column;
    //!< Mapa que relaciona uma coluna com seu valor.
    std::map<std::string, std::string> _vars;

    std::map<int, wxString> oprMap;

public:
    SQLHandler();

    wxString GetOpr(int i);
    int GetOpr(wxString opr);

    static where GetDateWhere(int opr, wxDateTime d1, wxDateTime d2);

    SQLHandler* Join(std::string table, std::string where);
    SQLHandler* NaturalJoin(std::string table);

    //! \brief Defini��o da tabela.
    //! \param tableName Nome da tabela a ser utilizada.
    //! \return A pr�pria inst�ncia.
    //! \details Define a tabela a ser utilizada na consulta sql.
    SQLHandler* Table(std::string tableName);

    //! \brief Defini��o da(s) coluna(s) utilizada(s).
    //! \param columnName Nome da coluna no banco.
    //! \return A pr�pria inst�ncia.
    //! \details Adiciona a coluna recebida numa lista de strings.
    SQLHandler* Column(std::string columnName);

    //! \brief Obt�m as colunas da lista.
    //! \return As colunas da lista separadas por v�rgula.
    std::string GetColumn();

    //! \brief Define o par�metro <b>`where`</b> de uma consulta SQL.
    //! \param info Informa��es do tipo <b>where</b>.
    //! \return A pr�pria inst�ncia.
    //! \details Utiliza o novo tipo de dados <b>where</b> para adicionar
    //! novos par�metros <b>`where`</b> de uma consulta SQL. A vantagem de sua
    //! utiliza��o, est� na adi��o de novos operadores para consultas, como
    //! o Between, Contains, Begins With e o Ends With.
    //!
    //! O novo tipo <b>where</b> possui os atributos
    //! - `nome`: nome da coluna do banco a que se refere.
    //! - `signal`: tipo do operador a ser utilizado.
    //! - `val_1`: valor a ser usado na compara��o.
    //! - `val_2`: segundo valor a ser usado na compara��o, caso o usu�rio
    //!            queira usar o Between.
    //! - `connector`: O tipo de conex�o entre predicados, AND ou OR.
    SQLHandler* Where(where info);

    //! \brief Define o par�metro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribu�do a esta coluna.
    //! \return A pr�pria inst�ncia.
    //! \details Adiciona o predicado numa lista de strings. Este
    //! predicado possui como padr�o a preposi��o <b>AND</b> e o
    //! operador que relaciona os par�metros <b>column</b> e <b>value</b>
    //! � o de igualdade.
    SQLHandler* Where(std::string column, std::string value);

    //! \brief Define o par�metro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de rela��o entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribu�do a esta coluna.
    //! \return A pr�pria inst�ncia.
    //! \details A �nica diferen�a � que, nesse, o operador � definido pelo
    //! usu�rio.
    SQLHandler* Where(std::string column, std::string signal, std::string value);

    //! \brief Define o par�metro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribu�do a esta coluna.
    //! \return A pr�pria inst�ncia.
    //! \details Operador padr�o de igualdade e com preposi��o <b>OR</b>.
    SQLHandler* WhereOr(std::string column, std::string value);

    //! \brief Define o par�metro <b>`where`</b> de uma consulta SQL.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de rela��o entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribu�do a esta coluna.
    //! \return A pr�pria inst�ncia.
    //! \details Sem operador padr�o e com preposi��o <b>OR</b>.
    SQLHandler* WhereOr(std::string column, std::string signal, std::string value);

    //! \brief Formata numa string os par�metros <b>where</b>.
    //! \param column Nome da coluna no banco.
    //! \param signal Sinal de rela��o entre o <b>`column`</b> e <b>`value`</b>
    //! \param value Valor atribu�do a esta coluna.
    //! \return Uma string formatada da seguinte maneira: <b>column signal 'value'</b>.
    //! \details � interessante a implementa��o de um m�todo �nico de
    //! formata��o, pois � nele que poderemos implementar diretrizes de
    //! seguran�a que impedem ataques do tipo SQL Injection.
    std::string DefineWhere(std::string column, std::string signal, std::string value);

    //! \brief Obt�m todos os predicados <b>where</b> definidos pelo usu�rio.
    //! \return Uma string conectando todos os predicados <b>where</b>.
    std::string GetWhere();

    //! \brief Insere um item num dicion�rio com chave e valor do tipo std::string.
    //! \param column Nome da coluna no banco.
    //! \param value Valor atribu�do a esta coluna.
    //! \return A pr�pria inst�ncia.
    SQLHandler* Set(std::string column, std::string value);

    //! \brief Gera o comando SQL de sele��o.
    //! \return Uma string que representa o comando SQL de sele��o.
    std::string Select();

    //! \brief Gera o comando SQL de exclus�o.
    //! \return Uma string que representa o comando SQL de exclus�o.
    std::string Delete();

    //! \brief Gera o comando SQL de inser��o.
    //! \return Uma string que representa o comando SQL de inser��o.
    std::string Insert();

    //! \brief Gera o comando SQL de edi��o.
    //! \return Uma string que representa o comando SQL de edi��o.
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
};

#endif
