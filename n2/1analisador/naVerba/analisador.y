%{
#include <stdio.h>
#include <string.h>
char resposta[] = "fantastic!!\n";
%}

/* --- TOKENS OPERADORES DE OPERADORES ---*/

//aritmética
%token add sub mult div1 addI subI rsubI multI divI rdivI 

//deslocamento
%token lshift lshiftI rshift rshiftI 

//operadores binarios
%token and andI or orI xor xorI

//operações de memoria
%token loadI load loadAI loadAO cload cloadAI cloadAO
%token store storeAI storeAO cstore cstoreAI cstoreAO

//operaçoes de copia
%token i2i c2c c2i i2c


/* --- TOKENS OPERADORES DE FLUXO DE CONTROLE ---*/
%token	jump jumpI cbr tbl
%token cmp_LT cmp_LE cmp_EQ cmp_GE cmp_GT cmp_NE comp
%token cbr_LT cbr_LE cbr_EQ cbr_GE cbr_GT cbr_NE


/* --- TOKENS ADICIONAIS  ---*/
%token nop
%token reg
%token virgula pontoVirgula doisPontos
%token label
%token num
%token abreColchete fechaColchete
%token erro


%%

programaIloc: listaInstrucoes 
;

listaInstrucoes: instrucao
| label doisPontos instrucao
| instrucao listaInstrucoes
;

instrucao: operacao
| abreColchete listaOperacoes fechaColchete
;

listaOperacoes: operacao
| operacao pontoVirgula listaOperacoes
;

operacao: opNormal
| opFluxoControle
;

opNormal: opcode listaOperandos
;

listaOperandos: operando
| operando separador listaOperandos
;

separador: 
| virgula
;

operando: reg
| num
| label
;

opFluxoControle: cbr reg separador label separador label
| jumpI label
| jump	reg
;


opcode: add|sub|mult|div1|addI|subI|rsubI|multI|divI|rdivI
|lshift|lshiftI|rshift|rshiftI|and|andI|or|orI|xor|xorI
|loadI|load|loadAI|loadAO|cload|cloadAI|cloadAO|store|storeAI|storeAO|cstore|cstoreAI|cstoreAO
|i2i|c2c|c2i|i2c
|jump|jumpI|cbr|tbl
|cmp_LT|cmp_LE|cmp_EQ|cmp_GE|cmp_GT|cmp_NE|comp
|cbr_LT|cbr_LE|cbr_EQ|cbr_GE|cbr_GT|cbr_NE|nop
;

%%

main(int argc, char **argv){

	yyparse();
	printf("%s", resposta);
}

yyerror(char *s){
	strcpy(resposta, "errou otario\n");
}
