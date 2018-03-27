	global main
	extern printf, scanf

	section .data			;contem as constantes

	%macro somar			;macro para somar
		pop rcx			;desempilha o segundo operador
		pop rbx			;desempilha o primeiro operador
		add rbx, rcx		;soma rbx a rcx e guarda em rbx
		push rbx		;empilha o resultado
	%endmacro 			;sai da macro

	%macro subtrair			;macro para subtrair
		pop rcx			;desempilha o segundo operador
		pop rbx			;desempilha o primeiro operador
		sub rbx, rcx		;subtrai rbx = rbx - rcx
		push rbx		;empilha o resultado
	%endmacro 			;sai da macro

	%macro multiplicar		;macro para multiplicar
		pop rdx			;desempilha o segundo operador
		pop rax			;desempilha o primeiro operador
		mul rdx			;multiplica rax = rax * rdx
		push rbx		;empilha o resultado
	%endmacro 			;sai da macro

	%macro dividir			;macro para dividir
		pop rdx			;desempilha o segundo operador
		pop rax			;desempilha o primeiro operador
		div rdx			;divide rax = rax / rdx
		push rbx		;empilha o resultado
	%endmacro 			;sai da macro

	section .text
	main:

		dividir			;chama macro de dividir
		push,1			;Empilha o numero encontrado
		push,5			;Empilha o numero encontrado

		multiplicar		;chama macro de multiplicar
		push,3			;Empilha o numero encontrado
		push,2			;Empilha o numero encontrado

		multiplicar		;chama macro de multiplicar

		somar			;chama macro de soma
		push,5			;Empilha o numero encontrado
		push,2			;Empilha o numero encontrado

		dividir			;chama macro de dividir

	ret				;final do programa
