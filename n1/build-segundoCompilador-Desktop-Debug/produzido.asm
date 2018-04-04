	global main			;indica que o main sera visivel fora do arquivo
	extern printf			;funções escritas em c que serão usadas no programa

	section .data			;segmento de dados inicializados
		imprimir db "Resultado da expressao: %lf",10,0	;constante utilizada para imprimir um double
		c dq 1.0		;variavel utilizada para mover para xmm0


	; --- Início da definição das macros ---

	%macro empilhar 1		;macro para empilhar recebe 1 parametro
	section .data			;define a variavel passada por parametro
		.valor dq %1		;.valor = parametro
	section .text			;segmento de procedimentos da macro
		fld qword[.valor]	;empilha o valor real
	%endmacro 			;fim da macro


	; --- Segmento de codigo, onde ficam as instruções ---
	section .text			;segmento de procedimentos
	main:
		push rbp	;constante utilizada para imprimir um double

	lab0:
		empilhar 1.0		;chama a macro para empilhar o valor passado

	lab1:
		empilhar 2.900000		;chama a macro para empilhar o valor passado

	lab2:
		empilhar 2.0		;chama a macro para empilhar o valor passado
		fsub			;pop st(0) e st(1). depois push st(1)-st(0)

	lab3:
		empilhar 1.0		;chama a macro para empilhar o valor passado
		fmul			;pop st(0) e st(1). depois push st(0)*st(1)

	lab4:
		empilhar 3.500000		;chama a macro para empilhar o valor passado

	lab5:
		empilhar 49.999900		;chama a macro para empilhar o valor passado
		fadd			;desempilha dois valores, soma e empilha o resultado
		fdiv			;pop st(0) e st(1). depois push st(1)/st(0)
		fadd			;desempilha dois valores, soma e empilha o resultado

	lab6:
		empilhar 2.564800		;chama a macro para empilhar o valor passado
		fsub			;pop st(0) e st(1). depois push st(1)-st(0)


	; --- imprimindo o resultado ---
		mov rdi, imprimir	;desempilhando a pilha de float na variavel c
		fstp qword [c]		;desempilhando a pilha de float na variavel c
		movq xmm0, [c]		;xmm0 = [c], printf utiliza xmm0 para passagem de float 
		mov rax, 1		;uma variavel float passada para o printf
		call printf		;chamada a funçao do c printf

		pop rbp			;desempilha novamente rbp
		xor rax, rax		;indica que não houve erro no programa

	ret				;final do programa
