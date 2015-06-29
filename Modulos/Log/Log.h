#ifndef _LOG_H
#define _LOG_H

#include <wx/wx.h>
#include <map>
#include <string>
#include <sstream>

//! \class Log
//! \brief Gerencia os logs da aplicação.
//! \details É responsável pelo gerenciamento das mensagens de log do sistema.
class Log
{
private:
    std::map<int, std::string> descs;
    std::string log_id, user_id;
public:
    //! \brief Construtor da classe.
    //! \param log_id ID da mensagem de log no banco de dados.
    //! \param user_id ID do usuário responsável pelo log.
    //! \param desc Descrição mais detalhada do log.
    //! \details O construtor da classe já recebe os valores do <b>log_id</b>
    //! e do <b>user_id</b> e salva a ocorrência no banco de dados.
    Log(std::string log_id, std::string user_id, std::string desc = "");

    //! \brief Retorna o instante atual em formato UNIX.
    //! \return Uma string contendo o inteiro que representa o instante atual em formato UNIX.
    static std::string DateTimeNow();

    //! \brief Retorna um objeto do tipo `wxDateTime` calculado a partir de uma `wxString` em formator UNIX.
    //! \return Um Objeto do tipo `wxDateTime`.
    static wxDateTime ToDateTime(wxString datetime);

    //! \example Log.cpp
};

#endif
