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
| label doisPontos listaInstrucoes
| instrucao listaInstrucoes
;

instrucao: operacao
| abreColchete listaOperacoes fechaColchete
;

listaOperacoes: operacao
| operacao pontoVirgula listaOperacoes
;

operacao: nop
| opcodeUnarioR reg
| opcodeUnarioL label
| opcodeBinarioRR reg separador reg
| opcodeBinarioNR num separador reg
| opcodeBinarioRL reg separador label
| opcodeTernarioRRR reg separador reg separador reg
| opcodeTernarioRNR reg separador num separador reg
| opcodeTernarioRRN reg separador reg separador num
| opcodeTernarioRLL reg separador label separador label
| opcodeTernarioNLL num separador label separador label
;

separador: 
| virgula
;


opcodeUnarioR: jump
;

opcodeUnarioL: jumpI
;

opcodeBinarioRR: load | cload | store | cstore 
| i2i | c2c | c2i | i2c
;

opcodeBinarioNR: loadI
;

opcodeBinarioRL: tbl
;

opcodeTernarioRRR: add | sub | mult | div1 
| lshift | rshift | and | or | xor 
| loadAO | cloadAO | storeAO | cstoreAO 
| cmp_LT | cmp_LE | cmp_EQ | cmp_GE | cmp_GT | cmp_NE
;

opcodeTernarioRNR: addI | subI | rsubI | multI | divI 
| lshiftI | rshiftI | andI | orI | xorI | loadAI | cloadAI
;

opcodeTernarioRRN: storeAI | cstoreAI | comp
;

opcodeTernarioRLL: cbr
;

opcodeTernarioNLL: cbr_LT | cbr_LE | cbr_EQ | cbr_GE | cbr_GT | cbr_NE
;

%%

main(int argc, char **argv){

	yyparse();
	printf("%s", resposta);
}

yyerror(char *s){
	strcpy(resposta, "errou otario\n");
}
