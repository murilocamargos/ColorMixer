#ifndef _APP_H
#define _APP_H

//! \class App
//! \brief Declara e executa a aplicação.
//! \details É responsável por definir o idioma da aplicação e
//! abrir a tela de login e o frame principal.
class App : public wxApp
{
public:
    /// Variável que armazena as propriedades de idioma da aplicação
    wxLocale *locale;

    //! \brief Método chamado sempre que a aplicação é inicializada.
    //! \return Valor lógico sempre verdadeiro.
    //! \details Mostra o SplashScreen na tela por dois segundos, carrega
    //! o último idioma utilizado na aplicação e abre o formulário de login.
    virtual bool OnInit();

    //! \brief Carrega o último idioma usado na aplicação.
    //! \return Uma constante inteira que representa o idioma.
    //! \details Esta função faz uso da biblioteca wxConfig para procurar o
    //! registro do windows salvo na última utilização da aplicação, contento
    //! o último idioma usado. Caso não haja nenhum registro ainda, utiliza o
    //! Português como idioma padrão.
    long LoadLang();

    //! \brief Define qual dicionário o sistema deverá utilizar.
    //! \param  lang Inteiro que representa o idioma a ser carregado.
    //! \return Valor lógico que determina se o dicionário foi carregado com
    //! sucesso ou não.
    //! \details Define o idioma a ser utilizado e procura pelo dicionário numa
    //! pasta de dicionários pré-definida.
    bool SetLocale(long lang);

    //! \brief Abre o frame principal da aplicação.
    //! \param uid ID do usuário que está tentanto abrir o frame.
    //! \param lang Idioma que o usuário escolheu na tela de login.
    //! \return Um valor lógico sempre verdadeiro.
    //! \details Define o idioma escolhido e abre o frame passando o id do usuário
    //! por parâmetro.
    bool OpenFrame(std::string uid, long lang);
};

DECLARE_APP(App)

#endif
