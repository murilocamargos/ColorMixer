SQLHandler *sql = new SQLHandler();
sql->Table("usuarios")
   ->Set("login", "murilo")
   ->Set("senha", "123")
   ->Where("user_id", "1")

std::cout << sql->Insert();
// INSERT INTO usuarios (login, senha) VALUES ('murilo', '123')

std::cout << sql->Update();
// UPDATE usuarios SET login = 'murilo', senha = '123' WHERE user_id = '1'

std::cout << sql->Delete();
// DELETE FROM usuarios WHERE user_id = '1'

std::cout << sql->Count();
// SELECT COUNT(*) FROM usuarios WHERE user_id = '1'
