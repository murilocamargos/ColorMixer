#include "../../App/Includes.h"

#include "Log.h"

#include "../Database/SQLHandler.h"
#include "../Database/SQLiteHandler.h"

Log::Log(std::string log_id, std::string user_id, std::string desc)
{
    this->log_id  = log_id;
    this->user_id = user_id;

    SQLiteHandler *db  = new SQLiteHandler();
    SQLHandler *sql = new SQLHandler();

    sql->Table("logs")->Set("log_id", this->log_id)
       ->Set("user_id", this->user_id)
       ->Set("ocorrencia", Log::DateTimeNow())
       ->Set("descricao", desc);

    db->Exec(sql->Insert());
}

std::string Log::DateTimeNow()
{
    wxDateTime now = wxDateTime::Now();
    std::stringstream ss;
    ss << now.GetTicks();
    return ss.str();
}

wxDateTime Log::ToDateTime(wxString datetime)
{
    unsigned long date;
    datetime.ToULong(&date);
    return wxDateTime(static_cast<time_t>(date));
}
