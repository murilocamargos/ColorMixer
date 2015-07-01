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

    bool join;

    std::map<int, wxString> oprMap;

public:
    //! \brief Define os tipos de operadoes padr�o.
    //! \details Os tipos definidos s�o:
    //! Any, =, !=, >, <, >=, <=, Between, Not between, Contains, Begins with, Ends with.
    SQLHandler();

    //! \brief Obt�m um operador.
    //! \param i �ndice inteiro do operador na lista.
    //! \return opr O operador em forma de string.
    wxString GetOpr(int i);

    //! \brief Obt�m um operador.
    //! \param opr String que determina o operador.
    //! \return i �nidice inteiro do operador na lista.
    int GetOpr(wxString opr);

    //! \brief Obt�m uma lista de operadores.
    //! \param oprs[] Array contendo os �ndices dos operadores.
    //! \param size Tamanho do array.
    //! \return oprs Uma Array de strings com todos os operadores pedidos.
    wxArrayString GetOpr(int oprs[], int size);

    //! \brief Define par�metro where de duas datas relacionadas por um operador.
    //! \param opr �ndice inteiro do operador na lista de operadores.
    //! \param d1 `wxDateTime` primeira data.
    //! \param d2 `wxDateTime` segunda data.
    //! \return where O where processado a partir do operador.
    //! \details Os operadores gerais n�o funcionam da mesma forma com datas,
    //! este m�todo encapsula o processamento de duas datas quaisquer a partir
    //! de um operador qualquer.
    static where GetDateWhere(int opr, wxDateTime d1, wxDateTime d2);

    //! \brief Faz a jun��o de duas tabelas.
    //! \param table Nome da tabela.
    //! \param where Condi��o de jun��o.
    //! \return A pr�pria inst�ncia.
    SQLHandler* Join(std::string table, std::string where);

    //! \brief Faz a jun��o natural de duas tabelas.
    //! \param table Nome da tabela.
    //! \return A pr�pria inst�ncia.
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
    //! - `col`: nome da coluna do banco a que se refere.
    //! - `opr`: tipo do operador a ser utilizado.
    //! - `val1`: valor a ser usado na compara��o.
    //! - `val2`: segundo valor a ser usado na compara��o, caso o usu�rio
    //!            queira usar o Between.
    //! - `con`: O tipo de conex�o entre predicados, AND ou OR.
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
    //! \example SQLHandlerJoin.cpp
    //! \example SQLHandlerNaturalJoin.cpp
};

#endif
