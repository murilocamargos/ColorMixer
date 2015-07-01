Languages
=========


O   arquivo   `original.pot`   foi  gerado  através  de  uma
ferramenta   para   obtenção   de  textos  que  possuem  uma
determinada   flag  em  um  lote  de  arquivos.  O  nome  da
ferramenta é xgettext.

A  flag  utilizada  foi  `_()`. Todo texto dentro do app que
estava  entre  esta  tag  `ex.:  _("File")` foi extraído dos
arquivos `.cpp` e colocados no arquivo `.pot`.

Para  a  criação  dos  arquivos  `.mo` que são utilizados no
aplicativo  como  dicionário, o programa `Poedit` foi usado.
Nele,  podemos  criar  versões  em diversos idiomas do texto
original do app.


======================== Como Usar =========================


1) Baixe o xgettext através do link:
   http://gnuwin32.sourceforge.net/packages/gettext.htm
   Baixe o `Complete package, except sources`.

2) Após  a instalação, adicione a pasta `C:\GnuWin32\bin` no
   path do windows. Caso você tenha instalado diretamente no
   diretório `C:\`.

3) Abra o `PowerShell` do windows em modo administrador.

4) Entre no diretório do projeto: `cd "nome_diretorio"`.

5) Salve uma lista com todos os arquivos `.cpp` utilizando o
   comando:

   $cpp = get-childitem -r -filter *.cpp | % { $_.FullName }

6) Execute o xgettext sobre este conjunto:
   
   xgettext -d orig -s --keyword=_ -p ./ -o orig.pot $cpp

7) Agora  você  terá  um  arquivo `orig.pot` no diretório do
   projeto. Basta usar o Poedit para criar versões em vários
   idiomas.



============== Criando Novos Idiomas: Poedit ===============


Caso  você  queira  criar  um  arquivo de idioma do zero, ou
seja,  um  novo  idioma  para  a  aplicação,  siga os passos
abaixo:

1) Baixe e instale o Poedit: http://poedit.net/

2) Abra o programa e vá em `Create new translation`

3) Selecione o arquivo `.pot`, o idioma, e comece a traduzir

Caso  você  tenha  aumentado  a  quantidade  de  strings  no
aplicativo  e  tenha que editar uma tradução, siga os passos
abaixo:

1) Abra o arquivo `.po` do idioma desejado.

2) Vá em `Catalog` > `Update from POT file`

3) Abra o novo arquivo `.pot` e complete as traduções.

Tanto  no  primeiro  caso quanto no segundo, ao salvar, você
terá  dois  arquivos  de tradução, um `.po` e um `.mo`. Você
deve  criar  uma  pasta  (caso  não  exista) com o código do
idioma (disponi. em http://xml.coverpages.org/iso639a.html),
colocar o arquivo `.mo` dentro e renomeá-lo para `myapp.mo`.