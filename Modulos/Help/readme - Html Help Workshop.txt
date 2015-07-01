Como adicionar arquivos de ajuda
=================================

1. Instale o programa HTML Help Workshop
(Disponível no site: https://www.microsoft.com/en-us/download/details.aspx?id=21138)

2. Crie todas páginas de ajuda em formato .htm

3. Abra o arquivo "helpmap.h" e defina um id e um número que será relacionado com o arquivo htm.
(Siga o exemplo).

4. Abra o programa instalado na opção 1. Clique em File, Open e o arquivo "LibraryHelp.hhp".

5. Na aba Project clique em HtmlHelp API Information. É o quarto botão que está ao lado esquerdo da tela.

6. Na aba Alias, clique em "Add...". No primeiro espaço, escreva o nome da constante ou do número definido no map. Dê preferência à constante, para preservar a estética.

7. No segundo espaço faça um link com o arquivo htm criado na opção 2. Dê OK nas duas janelas.

8. Na aba Contents Clique em Insert Heading(2º botão à esquerda) para uma nova secção e Insert Page(3º botão à esquerda) para nova página. Obs.: Caso queira uma nova secção ou uma página fora da secção atual, clique em OK na mensagem de aviso : "Do you want to insert this entry at the beginning of the table of contents? ", clique em NO caso queira a secção/página dentro da secção atual.

9. Na aba Index, cria-se chaves que relacionam palavras com uma página.