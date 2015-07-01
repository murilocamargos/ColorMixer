MyMenu *menu = new MyMenu();

wxString file = "File",
         help = "Help",
         lang = "Languages";

menu->AddMenu(file);
menu->AddMenu(help);
menu->AddMenu(lang, false); // Veja que o menu ainda não foi acoplado à barra

// Começo a tratar o submenu `lang` como se fosse um menu e adiciono
// submenus a ele.
menu->AddSubMenu(lang, MENU_LANG_EN, "English", "Change to english.");
menu->AddSubMenu(lang, MENU_LANG_PT, "Portuguese", "Change to portuguese.");


menu->AddSubMenu(file, MENU_FILE_NEW, "New\tCtrl+N", "New File.");
menu->AddSubMenu(file, MENU_FILE_OPEN, "Open\tCtrl+O", "Open File.");
menu->AddSubMenu(file, MENU_FILE_SAVE, "Save\tCtrl+S", "Save File.");
menu->Separator(file);
menu->AddSubMenu(file, MENU_FILE_QUIT, "Quit\tCtrl+Q", "Quit App.");


menu->AddSubMenu(help, -1, "Help\tF1", "Get Help.");
menu->AddSubMenu(help, -1, "About\tF2", "Get to know us better!");
menu->Separator(help);
// Ao usar essa definição de AddSubMenu, acoplei o menu `lang` como um submenu de `help`
menu->AddSubMenu(help, lang, "Change languages!");

/* Os menus vão ficar da seguinte forma:

File
  New   Ctrl+N
  Open  Ctrl+O
  Save  Ctrl+S
  ------------
  Quit  Ctrl+Q

Help
  Help      F1
  About     F2
  ------------
  Languages
    English
    Portuguese

*/
