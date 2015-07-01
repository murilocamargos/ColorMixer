SQLHandler *sql = new SQLHandler();
std::cout << sql->Table("usuarios")->Column("nome")->Column("idade")->Select();
// SELECT nome, idade FROM usuarios
