%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *nomeLabel;
int yyerror(char *s);		//funçao que entra em caso de erro
char *nomeLabel = 0;		//retorno da label pelo flex
char* resposta = 0;		//utilizado em caso de erro
/*o vetor de string variavel armazena as variaveis que serao mapeadas em posições de memoria para ser armazenada no ILOC de acordo com
o indice do vetor em que ela está armazenada*/
char variavel[100][16];		//limitando o tamanho da variavel para 16 bytes e no maximo 100 variaveis
FILE *yyin;			//arquivo de entrada
FILE *yyout;			//arquivo de saida
unsigned int sp = 0;		//stack pointer indica a posicao da pilha;
unsigned int qtdVariavel = 0; 	//armazena a quantidade de variaveis que tem no programa
int buscarIdVariavel(char c[]);	//retorna o indice correspondente a variavel c
unsigned int auxAtribuicao;
unsigned int auxCondicional;
unsigned int contadorIf = 0;
unsigned int contadorWhile = 0;
unsigned int stackIf[500]; 	//pilha para armazenar os contadores de if
unsigned int spStackIf = 0;	//stack point para o stackIf
%}


/* --- TOKENS TERMINAIS ---*/

//aritmética
%token add sub mult div1

//deslocamento
%token shiftLeft shiftRight

//operadores binarios
%token and or xor not

/* --- entrada e saida  ---*/
%token input1 output1

%token label erro

/* --- delimitadores de escopo  ---*/
%token abreChave fechaChave abreParentese fechaParentese 

/* --- TOKENS ADICIONAIS  ---*/
%token inteiro caracter string end
%token menor igual maior num enquanto se senao igorGostoso
%token virgula pontoVirgula

%%

programa: sequenciaComandos end
;

sequenciaComandos: comando 
| sequenciaComandos pontoVirgula comando
;

comando: 
| declaracao
| atribuicao
| expressao
| leitura
| impressao
| decisao
| repeticao
;

declaracao: inteiro label 		{
						strcpy(variavel[qtdVariavel++], nomeLabel);
						free(nomeLabel); nomeLabel = 0;
						}
;


atribuicao: label { auxAtribuicao = buscarIdVariavel(nomeLabel); free(nomeLabel); nomeLabel = 0;}
		 menor igual expressao {
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r3\n", auxAtribuicao);
						fprintf(yyout, "store r2, r3\n");
						}
;

expressao: expressao add termo		{	
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "add r2, r3, r1\n");
						fprintf(yyout, "loadI %d, r2\n", ++sp);
						fprintf(yyout, "store r1, r2\n");
						}
| expressao sub termo			{	
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "sub r3, r2, r1\n");
						fprintf(yyout, "loadI %d, r2\n", ++sp);
						fprintf(yyout, "store r1, r2\n");
						}
| termo
;

termo: termo mult fator			{	
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "mult r2, r3, r1\n");
						fprintf(yyout, "loadI %d, r2\n", ++sp);
						fprintf(yyout, "store r1, r2\n");
						}
| termo div1 fator			{	
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "div r2, r3, r1\n");
						fprintf(yyout, "loadI %d, r2\n", ++sp);
						fprintf(yyout, "store r1, r2\n");
						}
| fator
;

fator: label	 			{
						auxAtribuicao = buscarIdVariavel(nomeLabel); free(nomeLabel); nomeLabel = 0;
						fprintf(yyout, "loadI %d, r2\n", auxAtribuicao);
						fprintf(yyout, "load r2, r3\n", auxAtribuicao);
						fprintf(yyout, "loadI %d, r1\n", ++sp);
						fprintf(yyout, "store r3, r1\n");
						}
| num				 	{
						fprintf(yyout, "loadI %d, r1\n", ++sp);						
						fprintf(yyout, "loadI %d, r2\n", $1);
						fprintf(yyout, "store r2, r1\n");
						}
| abreParentese expressao fechaParentese
;

leitura: input1 listaIdentificadores
;

listaIdentificadores:
| label
| label virgula listaIdentificadores
;

impressao:
output1 listaExpressoes			{
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "output r2\n");
						}
;

listaExpressoes: 
| expressao
| expressao virgula listaExpressoes
;

decisao: se comparacao abreChave		{
						fprintf(yyout, "inicioIf%d:\n", contadorIf);
						stackIf[spStackIf++] = contadorIf++;
						}
				 sequenciaComandos fechaChave 	{
							auxCondicional = stackIf[--spStackIf];
							fprintf(yyout, "jumpI fimElse%d\n", auxCondicional);
							}
						senao abreChave 	{
									fprintf(yyout, "inicioElse%d:\n", auxCondicional);
									stackIf[spStackIf++] = auxCondicional;
									} 
								sequenciaComandos fechaChave 	{
											auxCondicional = stackIf[--spStackIf];
											fprintf(yyout, "fimElse%d:\n", auxCondicional);
											}
													
;

comparacao: 
  expressao maior expressao		{
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "comp r3, r2, r9\n");
						fprintf(yyout, "cbr_GT r9, inicioIf%d, inicioElse%d\n", contadorIf, contadorIf);
						}
| expressao igual expressao		{
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "comp r3, r2, r9\n");
						fprintf(yyout, "cbr_EQ r9, inicioIf%d, inicioElse%d\n", contadorIf, contadorIf);
						}
| expressao menor expressao		{
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r3\n");
						fprintf(yyout, "comp r3, r2, r9\n");
						fprintf(yyout, "cbr_LT r9, inicioIf%d, inicioElse%d\n", contadorIf, contadorIf);
						}
| expressao				{
						fprintf(yyout, "loadI %d, r1\n", sp--);
						fprintf(yyout, "load r1, r2\n");
						fprintf(yyout, "cbr r2, inicioIf%d, inicioElse%d\n", contadorIf, contadorIf);
						}
;


repeticao: enquanto  {
				fprintf(yyout, "inicioWhile%d:\n", auxCondicional);
				}
		 comparacao abreChave sequenciaComandos fechaChave
;

%%

int main(int argc, char **argv){
	
	yyin = fopen("entrada.txt", "r");
	yyout = fopen("saida.txt", "w");
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


int buscarIdVariavel(char c[]){
	for(int i=0; i< qtdVariavel; i++){
		if(strcmp(variavel[i], c) == 0){
			return i+400;	//para utilizar apenas os 400 ultimos enderecos de memoria do ILOC
		}
	}
}

