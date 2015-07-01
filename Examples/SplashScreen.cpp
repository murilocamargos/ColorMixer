SplashScreen *splash = new SplashScreen();

// Carrega imagem do arquivo re recursos.
splash->LoadImage(wxBITMAP(SPLBMP));

// Define um tempo de exibição de 2 seg.
splash->SetTime(2000);

// Mostra a imagem na tela.
splash->Show();
