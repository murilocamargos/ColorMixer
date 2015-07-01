#include "../../App/Includes.h"

#include "SQLHandler.h"

SQLHandler::SQLHandler()
{
    this->oprMap[0] = _("Any");
    this->oprMap[1] = "=";
    this->oprMap[2] = "!=";
    this->oprMap[3] = ">";
    this->oprMap[4] = "<";
    this->oprMap[5] = ">=";
    this->oprMap[6] = "<=";
    this->oprMap[7] = _("Between");
    this->oprMap[8] = _("Not between");
    this->oprMap[9] = _("Contains");
    this->oprMap[10] = _("Begins with");
    this->oprMap[11] = _("Ends with");
}

wxString SQLHandler::GetOpr(int i)
{
    if (this->oprMap.find(i) == this->oprMap.end())
        return this->oprMap.at(0);
    return this->oprMap.at(i);
}

int SQLHandler::GetOpr(wxString opr)
{
    std::map<int, wxString>::iterator it;
    for (it = this->oprMap.begin(); it != this->oprMap.end(); ++it)
        if (it->second == opr) return it->first;
    return 0;
}

wxArrayString SQLHandler::GetOpr(int oprs[], int size)
{
    wxArrayString choices;
    for ( int i = 0; i < size; i++ )
    {
        choices.Add( this->GetOpr( oprs[i] ) );
    }
    return choices;
}

where SQLHandler::GetDateWhere(int opr, wxDateTime d1, wxDateTime d2)
{
    where DATE;

    if (opr == 1 || opr == 2)
    {
        opr = 6 + opr;
        d2 = d1;
        d2.Add(wxTimeSpan::Hours(24));
    }
    else if (opr == 3 || opr == 6)
    {
        d1.Add(wxTimeSpan::Hours(24));
    }
    else if (opr == 7 || opr == 8)
    {
        d2.Add(wxTimeSpan::Hours(24));
    }

    wxString d1s(""), d2s("");
    if (opr != 0)
        d1s = wxString::Format("%i", d1.GetTicks());
    if (opr == 7 || opr == 8)
        d2s = wxString::Format("%i", d2.GetTicks());

    DATE.col  = "";
    DATE.opr  = opr;
    DATE.val1 = d1s;
    DATE.val2 = d2s;
    DATE.con  = "";

    return DATE;
}

SQLHandler* SQLHandler::Join(std::string table, std::string where)
{
    this->_table += " JOIN " + table;
    this->_where.push_back("AND " + where);
    return this;
}
SQLHandler* SQLHandler::NaturalJoin(std::string table)
{
    this->_table += " NATURAL JOIN " + table;
    return this;
}

SQLHandler* SQLHandler::Table(std::string tableName)
{
    this->Clear();
    this->_table = tableName;
    return this;
}

void SQLHandler::Clear()
{
    this->_table.clear();
    this->_where.clear();
    this->_column.clear();
    this->_vars.clear();
}

SQLHandler* SQLHandler::Set(std::string column, std::string value)
{
    this->_vars[column] = value;
    return this;
}

SQLHandler* SQLHandler::Column(std::string columnName)
{
    this->_column.push_back(columnName);
    return this;
}
std::string SQLHandler::GetColumn()
{
    std::string clm = "";
    int sz = this->_column.size();
    if (sz == 0)
    {
        return "*";
    }

    for (int i = 0; i < sz; i++)
    {
        clm += this->_column[i] + ", ";
    }

    return clm.substr(0, clm.size() - 2);
}

std::string SQLHandler::DefineWhere(std::string column, std::string signal, std::string value)
{
    std::string whr = column + " " + signal + " '" + value + "'";

    return whr;
}

SQLHandler* SQLHandler::Where(where info)
{
    if (info.val1 == "")
        return this;

    std::string format = "";
    if (info.opr == 1)
		format = "= '{1}'";
	else if (info.opr == 2)
		format = "!= '{1}'";
	else if (info.opr == 3)
		format = "> {1}";
	else if (info.opr == 4)
		format = "< {1}";
	else if (info.opr == 5)
		format = ">= {1}";
	else if (info.opr == 6)
		format = "<= {1}";
	else if (info.opr == 7)
		format = "BETWEEN {1} AND {2}";
    else if (info.opr == 8)
        format = "NOT BETWEEN {1} AND {2}";
	else if (info.opr == 9)
		format = "LIKE '%%{1}%%'";
	else if (info.opr == 10)
		format = "LIKE '{1}%%'";
	else if (info.opr == 11)
		format = "LIKE '%%{1}'";
    else
    	format = "= '{1}'";

    std::string con = (info.con == "AND") ? "AND " : "OR  ";
    std::string val = format;

    size_t v1 = val.find("{1}");
    if (v1 != std::string::npos) val.replace(v1, 3, info.val1);

    size_t v2 = val.find("{2}");
    if (v2 != std::string::npos) val.replace(v2, 3, info.val2);

    this->_where.push_back(std::string((con + info.col + " " + val).mb_str()));
    return this;
}

SQLHandler* SQLHandler::Where(std::string column, std::string value)
{
    this->_where.push_back("AND " + this->DefineWhere(column, "=", value));
    return this;
}

SQLHandler* SQLHandler::Where(std::string column, std::string signal, std::string value)
{
    this->_where.push_back("AND " + this->DefineWhere(column, signal, value));
    return this;
}

SQLHandler* SQLHandler::WhereOr(std::string column, std::string value)
{
    this->_where.push_back("OR  " + this->DefineWhere(column, "=", value));
    return this;
}

SQLHandler* SQLHandler::WhereOr(std::string column, std::string signal, std::string value)
{
    this->_where.push_back("OR  " + this->DefineWhere(column, signal, value));
    return this;
}

std::string SQLHandler::GetWhere()
{
    std::string whr = "WHERE ";
    int sz = this->_where.size();

    if (sz == 0)
    {
        return "";
    }

    whr += this->_where[0].substr(4);
    for (int i = 1; i < sz; i++)
    {
        whr += " " + this->_where[i];
    }

    return whr;
}

std::string SQLHandler::Select()
{
    std::string sql;

    sql = "SELECT " + this->GetColumn() + " FROM " + this->_table + " " + this->GetWhere();

    return sql;
}


std::string SQLHandler::Delete()
{
    std::string sql;

    sql = "DELETE FROM " + this->_table + " " + this->GetWhere();

    return sql;
}

std::string SQLHandler::Insert()
{
    std::string sql, cols = "", vals = "";
    std::map<std::string, std::string>::iterator it;

    for (it = this->_vars.begin(); it != this->_vars.end(); it++)
    {
        cols += it->first + ", ";
        vals += it->second + "', '";
    }
    cols = cols.substr(0, cols.size() - 2);
    vals = vals.substr(0, vals.size() - 3);

    sql = "INSERT INTO " + this->_table + " (" + cols + ") VALUES ('" + vals + ")";

    return sql;
}


std::string SQLHandler::Update()
{
    std::string sql = "UPDATE " + this->_table + " SET ";
    std::map<std::string, std::string>::iterator it;

    for (it = this->_vars.begin(); it != this->_vars.end(); it++)
    {
        sql += it->first + " = '" + it->second + "', ";
    }

    return sql.substr(0, sql.size() - 2) + " " + this->GetWhere();
}

std::string SQLHandler::Count()
{
    return "SELECT COUNT(*) FROM " + this->_table + " " + this->GetWhere();
}
