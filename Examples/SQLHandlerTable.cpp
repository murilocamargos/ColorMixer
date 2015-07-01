SQLHandler *sql = new SQLHandler();
std::cout << sql->Table("usuarios")->Select();
// SELECT * FROM usuarios
