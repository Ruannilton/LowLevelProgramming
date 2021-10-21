; IO library for Intel64 Linux
; registradores de argumentos: rdi, rsi, rdx, rcx, r8, r9
; retorn em rax, rdx
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