SQLHandler *sql = new SQLHandler();
sql->Table("usuarios u")
   ->NaturalJoin("logs l")

std::cout << sql->Select();
// SELECT * FROM usuarios u NATURAL JOIN logs l
