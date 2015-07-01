SQLHandler *sql = new SQLHandler();
sql->Table("usuarios")
   ->Where("login", "murilo")
   ->Where("nivel", "1")
   ->WhereOr("idade", "<", "20");

std::cout << sql->Select();
// SELECT * FROM usuarios WHERE nome = 'Murilo' AND nivel = '1' OR idade < '20'

where NAME, LOGIN;

NAME.col = "nome";
NAME.opr = 9 // Contains
NAME.val1 = "lu"
NAME.val2 = "";
NAME.con = "AND";

LOGIN.col = "login";
LOGIN.opr = 7 // Between
LOGIN.val1 = "5"
LOGIN.val2 = "10";
LOGIN.con = "OR";

sql->Table("usuarios")
   ->Where(NAME)
   ->Where(LOGIN);

std::cout << sql->Select();
// SELECT * FROM usuarios WHERE nome LIKE '%lu%' OR login BETWEEN 5 AND 10
