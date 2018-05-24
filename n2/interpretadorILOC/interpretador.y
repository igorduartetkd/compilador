%{
#include <stdio.h>
#include <string.h>
char* resposta = 0;
int regs[10];
int memInt[500];
char memChar[500];
int linha[500];
char labelN[500][16]; //limitando o tamanho da label a 16 caracteres
void iniciaLinha();
int buscaLabelLinha(char c[]);
unsigned int pc;
extern int yylineno;
extern int yylex();
extern void yyrestart(FILE *f);
extern short int executar;
extern int linhaPular;
short int modoIdLabel;
char *c = 0;
int yyerror(char *s);
FILE *yyin;
int qtdLinha = 0;
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
| label {if(modoIdLabel){/*armazenar a linha e a label*/ 
						if(c){ linha[qtdLinha] = yylineno;
							strcpy(labelN[qtdLinha], c);
							qtdLinha++;
							free(c); c = 0;}} }  doisPontos listaInstrucoes 	
| instrucao listaInstrucoes
;

instrucao: operacao
| abreColchete listaOperacoes fechaColchete
;

listaOperacoes: operacao
| operacao pontoVirgula listaOperacoes
;

operacao: nop
| add 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] + regs[$4];}}
| sub 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] - regs[$4];}}
| mult 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] * regs[$4];}}
| div1 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] / regs[$4];}}
| addI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] + $4;}}
| subI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] - $4;}}
| rsubI 	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = $4 - regs[$2];}}
| multI 	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] * $4;}}
| divI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] / $4;}}
| rdivI 	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = $4 / regs[$2];}}

| lshift 	reg separador reg separador reg 	{if(!modoIdLabel){regs[$6] = regs[$2] << regs[$4];}}
| lshiftI 	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] << $4;}}
| rshift	reg separador reg separador reg 	{if(!modoIdLabel){regs[$6] = regs[$2] >> regs[$4];}}
| rshiftI	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] >> $4;}}

| and 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] & regs[$4];}}
| andI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] & $4;}}
| or 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] | regs[$4];}}
| orI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] | $4;}}
| xor 		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] ^ regs[$4];}}
| xorI 		reg separador num separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] ^ $4;}}

		
| load 		reg separador reg			{if(!modoIdLabel){regs[$4] = memInt[regs[$2]];}}
| loadAI 	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = memInt[regs[$2] + $4];}}
| loadAO 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = memInt[regs[$2] + regs[$4]];}}
| cload 	reg separador reg			{if(!modoIdLabel){regs[$4] = memChar[regs[$2]];}}
| cloadAI	reg separador num separador reg		{if(!modoIdLabel){regs[$6] = memChar[regs[$2] + $4];}}
| cloadAO 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = memChar[regs[$2] + regs[$4]];}}
| loadI		num separador reg			{if(!modoIdLabel){regs[$4] = $2;}}
	
| store 	reg separador reg			{if(!modoIdLabel){memInt[regs[$4]] = regs[$2];}}
| storeAI 	reg separador reg separador num		{if(!modoIdLabel){memInt[regs[$4] + $6] = regs[$2];}}
| storeAO 	reg separador reg separador reg		{if(!modoIdLabel){memInt[regs[$4] + regs[$6]] = regs[$2];}}
| cstore 	reg separador reg			{if(!modoIdLabel){memChar[regs[$4]] = regs[$2];}}
| cstoreAI 	reg separador reg separador num		{if(!modoIdLabel){memChar[regs[$4] + $6] = regs[$2];}}
| cstoreAO 	reg separador reg separador reg		{if(!modoIdLabel){memChar[regs[$4] + regs[$6]] = regs[$2];}}

| i2i 		reg separador reg			{if(!modoIdLabel){regs[$4] = regs[$2];}}
| c2c 		reg separador reg			{if(!modoIdLabel){regs[$4] = regs[$2];}}
| c2i 		reg separador reg			{if(!modoIdLabel){regs[$4] = regs[$2] - 48;}}
| i2c		reg separador reg			{if(!modoIdLabel){regs[$4] = regs[$2] + 48;}}

| jump		reg					{if(!modoIdLabel){	fclose(yyin); 
								yyin = fopen("teste.txt", "r"); 
								yylineno = 1;
								executar = 0;
								linhaPular = regs[$2];
								yyrestart(yyin);}}
| jumpI		label					{if(!modoIdLabel){	fclose(yyin); 
								yyin = fopen("teste.txt", "r"); 
								yylineno = 1;
								executar = 0;
								linhaPular = buscaLabelLinha(c);
								free(c); c = 0;
								yyrestart(yyin);}}

| cbr		reg separador label separador label	
| tbl		reg separador label			
| cmp_LT 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] <  regs[$4];}}
| cmp_LE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] <= regs[$4];}}
| cmp_EQ 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] == regs[$4];}}
| cmp_GE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] >= regs[$4];}}
| cmp_GT 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] >  regs[$4];}}
| cmp_NE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] != regs[$4];}}
| comp		

| cbr_LT 
| cbr_LE 
| cbr_EQ 
| cbr_GE 
| cbr_GT 
| cbr_NE

| inputi 	reg num					{if(!modoIdLabel){regs[$2] = $3;}}
| outputi 	reg					{if(!modoIdLabel){int aux = $2; printf("%d", regs[aux]);}}

| inputc 	reg caractere				{if(!modoIdLabel){regs[$2] = $3;}}
| outputc 	reg					{if(!modoIdLabel){int aux = $2; printf("%c", regs[aux]);}}
;

separador: 
| virgula
;

%%

int main(int argc, char **argv){
	iniciaLinha();
	//roda uma vez para identificar as linhas das labels
	modoIdLabel = 1;
	yylineno = 1;
	yyin = fopen("teste.txt", "r");
	yyparse();
	modoIdLabel = 0;

	//roda a segunda vez na verba
	
	yyin = fopen("teste.txt", "r");
	yylineno = 1;
	yyparse();
	if(resposta){
		printf("%s\n", resposta);
		free(resposta);
		resposta = 0;
	}
	return 0;
}

int yyerror(char *s){
	resposta = malloc(sizeof("--ERROU otario--"));
	strcpy(resposta, "--ERROU otario--");
	return 0;
}

void iniciaLinha(){
	for(int i=0; i<500; i++){
		linha[i] = 0;
	}
}

int buscaLabelLinha(char c[]){
	for(int i=0; i< qtdLinha; i++){
		if(strcmp(labelN[i], c) == 0){
			return linha[i];
		}
	}
}
