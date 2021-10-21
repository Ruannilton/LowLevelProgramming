; IO library for Intel64 Linux

; Registradores de argumentos: rdi, rsi, rdx, rcx, r8, r9
; Retorno em rax, rdx
; Callee-Saved: rbx, rbp, rsp, r12-r15

;--------------------------------------------------------------

; Encerra o programa com o valor passado para rsi
; parametros:
;   rsi : código a ser retornado na saída do programa
exit:           
    mov rax, 60 
    syscall     



; Calcula o tamanho de uma string com terminação nula
; parametros:
;   rdi : ponteiro para a string
; retorno:
;   rax : tamanho da string
string_lenght:      
    xor rax,rax     ; zera rax
    .loop:
        cmp byte[rdi+rax],0
        je .end_loop
        inc rax
        jmp .loop
    .end_loop:
        ret



; Exibe uma string em stdout
; parametros:
;   rdi : ponteiro para a string
print_string:
    call string_lenght  ; armazena o tamanho da string em rax 
    mov rsi, rdi        ; seta a string a ser exibida
    mov rdx, rax        ; passa a quantidade de caracteres a serem exibidos
    mov rdi, 1          ; seta o arquivo de saída para stdout
    mov rax, 1          ; define a chamada de sistema WRITE
    syscall
    ret



; Exibe um caractere em stdout
; parametros:
;   rdi : caractere a ser exibido
print_char:
    mov rsi, rdi
    mov rdx, 1
    mov rdi, 1
    mov rax, 1
    syscall
    ret



; Realiza uma quebra de linha
print_newline:
    mov rsi, 10
    mov rdx, 1
    mov rdi, 1
    mov rax, 1
    syscall
    ret



; Exibe um inteiro de 8 bytes sem sinal em formato decimal
; parametros:
;   rdi : numero a ser exibido
print_uint:
    mov rax, rdi        ; passa o dividendo para eax
    push r13            ; salva o estado de r13
    xor r13,r13         ; zera r13
    push 10             ; colocar o fim da string na stack
    
    .loop:
        mov rcx, 10     ; seta 10 para o divisor
        idiv rdx        ; realiza a operação (resultado é armazenado em rax e o resto em rdx)
        add rdx, 48     ; converte decimal para caractere na tabela ASCII
        push rdx        ; armazena o resto da divisão na stack
        inc r13         ; incrementa r13

        test rax,rax    ; caso ainda exista casas decimais continua a divisão
        jnz .loop

    mov rdi,rsp         ; coloca o topo da pilha como string a ser printada
    call print_string   ; printa o numero

    .clear_stack:       ; remove os caracteres adicionados da stack
        pop rdx
        dec r13
        test r13,r13
        jnz clear_stack
    pop rdx             ; remove o terminador nulo
    pop r13             ; restaura o estado inicial de r13
    ret



; Exibe um inteiro de 8 bytes com sinal em formato decimal
; parametros:
;   rdi : numero a ser exibido
print_int:
    cmp 0,rdi           ; se o numero for menor que 0 vai para print_negative, caso contrário chama print_uint
    jl print_negative
    call print_uint
    ret
    
    .print_negative:
        push rdi        ; salva o estado de rdi na stack
        mov rdi, 45     ; coloca o valor de '-' em rdi 
        call print_char ; printa '-'
        pop rdi         ; restaura o estado inicial de rdi

        dec rdi         ; reverte a negação de dois complementos
        not rdi
        call print_uint
        ret