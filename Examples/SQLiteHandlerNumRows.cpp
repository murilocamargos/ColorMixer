SQLHandler    *sql = new SQLHandler();
SQLiteHandler *db  = new SQLiteHandler();

sql->Table("usuarios");

std::cout << db->NumRows(sql);
// Irá mostrar a quantidade de usuário no banco usando a query:
//   SELECT COUNT(*) FROM usuarios

sql = new SQLHandler();
sql->Table("logs")
   ->Where("log_id", ">", "1");

std::cout << db->NumRows(sql);
// Irá mostrar a quantidade de logs cujo log_id seja maior que 1
//   SELECT COUNT(*) FROM logs WHERE log_id > '1'
