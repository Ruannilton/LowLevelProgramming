section .data
	codes: db '0123456789ABCDEF' ; string com os caracteres hexadecimais
	new_line: db 10				 ; caractere de nova linha 
section .text
global _start

_start:
	mov rax, 1122334455667788  ; numero a ser printado
	
	mov rdi, 1					 ; seleciona o arquivo de escrita "stdout"
	mov rdx, 1					 ; quantidade de bytes a serem escritas
	
	mov rcx, 64					 ; tamanho de bits do numero

	; cada 4 bits devem ser representados como um caractere hexadecimal
	
	.loop:
		push rax				 ; salva o numero na stack
		sub rcx, 4
		sar rax, cl				 ; cl são os 8 menores bits de rcx
		and rax, 0xf			 ; pega o index do caractere hexadecimal  

		lea rsi,[codes + rax]	 ; coloca o endereço do caractere a ser printado em rsi
		mov rax, 1 				 ; prepara o registrador com a chamada de sistema "write"

		push rcx				 ; salva o valor de rcx na stack, pois uma chamada de sistema altera o seu conteúdo
		syscall					 ; realiza a chamada de sistema (rax:1 -> write)
		pop rcx					 ; pega o valor de rcx de volta da stack (linha 27)
		pop rax					 ; pega o valor de rax de volta da stack (linha 19)

		test rcx, rcx			 ; forma mais rapida de verificar se um valor é zero
		jnz .loop				 ; caso não seja zero, volta para .loop (linha 18)
	
	mov rax, 1
	mov rsi, new_line
	syscall						 ; printa quebra de linha no programa

	mov rax, 60					 ; prepara o registrador com a chamada de sistema "exit"
	xor rdi, rdi
	syscall						 ; fim do programa