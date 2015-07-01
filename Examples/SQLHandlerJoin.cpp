SQLHandler *sql = new SQLHandler();
sql->Table("usuarios u")
   ->Join("logs l", "u.user_id = l.user_id")

std::cout << sql->Select();
// SELECT * FROM usuarios u JOIN logs l WHERE u.user_id = l.user_id
