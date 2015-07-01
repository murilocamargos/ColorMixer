SQLHandler    *sql = new SQLHandler();
SQLiteHandler *db  = new SQLiteHandler();

sql->Table("usuarios")
   ->Column("user_id")
   ->Column("nome");

db->Select(sql);

if (db->rows.size() > 0)
{
    std::map<std::string, std::string>::iterator it;

    for (int row = 0; row < db->rows.size(); row++)
    {

        for (it = db->rows[row].begin(); it != db->rows[row].end(); ++it)
        {
            std::cout << it->first << ": " << it->second << std::endl;
        }

        std::cout << "----" << std::endl;

    }
}
else
{
    std::cout << "A consulta não retornou nenhum resultado!"
}
// O trecho acima irá mostrar todas as linhas retornadas pela consulta
//   SELECT user_id, nome FROM usuarios
// O resultado será algo como:
//
/*
 *
 * user_id: 1
 * nome: João
 * ----
 * user_id: 2
 * nome: Pedro
 * ----
 * user_id: 3
 * nome: Carlos
 * ----
 * ...
 *
 */
