%{
#include <stdio.h>
#include <string.h>
char resposta[] = "                  \n";
int regs[10];
int memInt[500];
char memChar[500];
unsigned int pc;
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
%token caractere
%token label
%token num
%token abreColchete fechaColchete
%token erro
%token inputi outputi inputc outputc


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
| add 		reg separador reg separador reg		{regs[$6] = regs[$2] + regs[$4];}
| sub 		reg separador reg separador reg		{regs[$6] = regs[$2] - regs[$4];}
| mult 		reg separador reg separador reg		{regs[$6] = regs[$2] * regs[$4];}
| div1 		reg separador reg separador reg		{regs[$6] = regs[$2] / regs[$4];}
| addI 		reg separador num separador reg		{regs[$6] = regs[$2] + $4;}
| subI 		reg separador num separador reg		{regs[$6] = regs[$2] - $4;}
| rsubI 	reg separador num separador reg		{regs[$6] = $4 - regs[$2];}
| multI 	reg separador num separador reg		{regs[$6] = regs[$2] * $4;}
| divI 		reg separador num separador reg		{regs[$6] = regs[$2] / $4;}
| rdivI 	reg separador num separador reg		{regs[$6] = $4 / regs[$2];}

| lshift 	reg separador reg separador reg 	{regs[$6] = regs[$2] << regs[$4];}
| lshiftI 	reg separador num separador reg		{regs[$6] = regs[$2] << $4;}
| rshift	reg separador reg separador reg 	{regs[$6] = regs[$2] >> regs[$4];}
| rshiftI	reg separador num separador reg		{regs[$6] = regs[$2] >> $4;}

| and 		reg separador reg separador reg		{regs[$6] = regs[$2] & regs[$4];}
| andI 		reg separador num separador reg		{regs[$6] = regs[$2] & $4;}
| or 		reg separador reg separador reg		{regs[$6] = regs[$2] | regs[$4];}
| orI 		reg separador num separador reg		{regs[$6] = regs[$2] | $4;}
| xor 		reg separador reg separador reg		{regs[$6] = regs[$2] ^ regs[$4];}
| xorI 		reg separador num separador reg		{regs[$6] = regs[$2] ^ $4;}

		
| load 		reg separador reg			{regs[$4] = memInt[regs[$2]];}
| loadAI 	reg separador num separador reg		{regs[$6] = memInt[regs[$2] + $4];}
| loadAO 	reg separador reg separador reg		{regs[$6] = memInt[regs[$2] + regs[$4]];}
| cload 	reg separador reg			{regs[$4] = memChar[regs[$2]];}
| cloadAI	reg separador num separador reg		{regs[$6] = memChar[regs[$2] + $4];}
| cloadAO 	reg separador reg separador reg		{regs[$6] = memChar[regs[$2] + regs[$4]];}
| loadI		num separador reg			{regs[$4] = $2;}
	
| store 	reg separador reg			{memInt[regs[$4]] = regs[$2];}
| storeAI 	reg separador reg separador num		{memInt[regs[$4] + $6] = regs[$2];}
| storeAO 	reg separador reg separador reg		{memInt[regs[$4] + regs[$6]] = regs[$2];}
| cstore 	reg separador reg			{memChar[regs[$4]] = regs[$2];}
| cstoreAI 	reg separador reg separador num		{memChar[regs[$4] + $6] = regs[$2];}
| cstoreAO 	reg separador reg separador reg		{memChar[regs[$4] + regs[$6]] = regs[$2];}

| i2i 		reg separador reg			{regs[$4] = regs[$2];}
| c2c 		reg separador reg			{regs[$4] = regs[$2];}
| c2i 		reg separador reg			{regs[$4] = regs[$2] - 48;}
| i2c		reg separador reg			{regs[$4] = regs[$2] + 48;}

| jump		reg
| jumpI		label

| cbr		reg separador label separador label	
| tbl		reg separador label			
| cmp_LT 	reg separador reg separador reg		{regs[$6] = regs[$2] <  regs[$4];}
| cmp_LE 	reg separador reg separador reg		{regs[$6] = regs[$2] <= regs[$4];}
| cmp_EQ 	reg separador reg separador reg		{regs[$6] = regs[$2] == regs[$4];}
| cmp_GE 	reg separador reg separador reg		{regs[$6] = regs[$2] >= regs[$4];}
| cmp_GT 	reg separador reg separador reg		{regs[$6] = regs[$2] >  regs[$4];}
| cmp_NE 	reg separador reg separador reg		{regs[$6] = regs[$2] != regs[$4];}
| comp		

| cbr_LT 
| cbr_LE 
| cbr_EQ 
| cbr_GE 
| cbr_GT 
| cbr_NE

| inputi 	reg num					{regs[$2] = $3;}
| outputi 	reg					{int aux = $2; printf("%d", regs[aux]);}

| inputc 	reg caractere				{regs[$2] = $3;}
| outputc 	reg					{int aux = $2; printf("%c", regs[aux]);}
;

separador: 
| virgula
;

%%

int main(int argc, char **argv){

	yyparse();
	printf("%s", resposta);
	return 0;
}

int yyerror(char *s){
	strcpy(resposta, "\n--ERROU otario--\n");
	return 0;
}

int yyaction(){
	pc++;
	printf("pc: %d", pc);
	return 0;
}
