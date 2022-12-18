/**
* Autores: Thiago Gariani Quinto, Iago Ortega Carmona, Reginaldo Gregorio de Souza Neto
*
* Sobre: arquivo de informação sobre como compilar e executar o programa, sendo que após
* realizar o comando de execução, um shell irá aparecer na tela do usuário, sendo por esta 
* tela a interface de manipulação do sistema arquivos.
*/

Compilação:
    Para realizar a compilação, basta digitar o comando make pelo terminal.

Execução:
    Para executar, o processo é análogo à compilação, porém, o comando a ser utilizado é o ./main myext2image.img, 
    ao inserir este comando um shell será inicicializado.

Bibliotecas:

    <inttypes.h>: providencia configurações de tipo integer cujas definições são consistenentes em 
    diferentes máquinas e Sindependente de Sistemass Operacionais ou outras implementações.
    
    <stdint.h>: declara configurações de tipos integer contendo larguras especificadas, e define 
    configurações correspondentes de macros. Também de define macros que especificam limites de 
    tipos integer de outros cabeçalhos.

    <sys/stat.h>: define as estruturas de dados retornadas pelas funções fstat(), lstat() e stat().