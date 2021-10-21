Biblioteca para realizar operações básicas de entrada/saída e conversões

Registradores usados como argumento: **rdi, rsi, rdx, rcx, r8, r9**

Funções:

* exit
    - Aceita um código de saída e encerra o processo atual
* string_lenght.
    - Aceita um ponteiro para uma string e devolve o seu tamanho.
* print_string
    - Aceita um ponteiro para uma string terminada em nulo e exibe-a em **stdout**.
* print_char
    - Aceita um código de caractere diretamente no seu primeiro argumento e exibe-o em **stdout**.
* print_newline
    - Exibe um caractere com código 0xA.
* print_uint
    - Exibe um inteiro de 8 bytes sem sinal em formato decimal. Sugerimos que você crie um buffer na pilha¹ e armazene aí o resultado da divisão. Sempre divida o último valor por 10 e armazene o dígito correspondente no buffer. Não esqueça de que você deve transformar cada dígito em seu código ASCII(por exemplo 0x04 passa a ser 0x34).
* print_int
    - Exibe um inteiro de 8 bytes com sinal em formato decimal.
* read_char
    - Lê um caractere de **stdin** e o devolve. Se o final do stream de entrada ocorrer, devolve 0.
* read_word
    - Aceita um endereço de buffer e o tamanho como argumentos. Lê a próxima palavra de **stdin** (Pula espaçoes em branco no buffer²). Para e devolve 0 se a palavra for muito grande para o buffer especificado; caso contrário, devolve um endereço de buffer. Essa função deve finalizar a string aceita com nulo.
* parse_uint
    - Aceita uma string terminada com nulo e tenta fazer parse de um numero sem sinal a partir de seu início. Devolve o número identificado pelo parse em **rax** e o contador de caracteres em **rdx**.
* parse_int
    - Aceita uma string terminada com nulo e tenta fazer parse de um numero com sinal a partir de seu início. Devolve o número identificado pelo parse em **rax** e o contador de caracteres em **rdx**(incluindo o sinal, se houver). Nenhum espaço entre o sinal e os dígitos é permitido.
* string_equals
    - Aceita dois ponteiros para strings e os compara. Devolve 1 se forem iguais; caso contrário devolve 0.
* string_copy
    - Aceita um ponteiro para uma string, um ponteiro para um buffer e o tamanho do buffer. Copia a string para o destino. O endereço de destino será devolvido se a string couber no buffer; caso contrário 0 será devolvido

1: Decrementar **rsp** cria espaço na pilha <br>
2: Espaços em branco: espaço (0x20), tabulação (0x9), quebra de linha (0x10) <br>