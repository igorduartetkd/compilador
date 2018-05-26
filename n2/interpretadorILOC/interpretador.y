%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char* resposta = 0;		//utilizado em caso de erro
int regs[10];			//registradores (limitado a 10)
int memInt[500];		//memoria de inteiros
char memChar[500];		//memoria de caracteres
int linha[500];			//armazena a linha de cada label
char labelN[500][16]; 		//limitando o tamanho da label a 16 caracteres
void iniciaLinha();		//inicia o vetor linha com 0, obsoleto, substituido pela variavel qtdLinha
int buscarLabelLinha(char c[]);	//retorna a linha que está a label c[]
unsigned int pc;		//nao utilizado ainda
extern int yylineno;		//armazena a linha atual do flex
extern int yylex();		
extern void yyrestart(FILE *f);	//utilizado para reiniciar a leitura do arquivo
extern short int executar;	//flag de execução: 0- nao executar | 1- executar
extern int linhaPular;		//armazena a linha que o jump deve ir
short int modoIdLabel;		//utilizado para mapear as linhas das labels no inicio do codigo
char *nomeLabel = 0;		//retorno da label pelo flex
int yyerror(char *s);		//funçao que entra em caso de erro
FILE *yyin;			//arquivo de entrada
int qtdLinha = 0;		//utilizado para armazenar as linhas nas posicoes corretas do vetor linha e labelN
void pular(int linha);
int aux;			//se precisar é so chamar
short int testarBit(int reg, short int nbit);  //se o registrador em binario for 1 no bit nbit retorna 1 caso contrario retorna 0
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
| label {if(modoIdLabel){/*armazenar a linha de cada label*/ 
						if(nomeLabel){ linha[qtdLinha] = yylineno;
							strcpy(labelN[qtdLinha], nomeLabel);
							qtdLinha++;
							free(nomeLabel); nomeLabel = 0;}} }  doisPontos listaInstrucoes 	
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

| jump		reg					{if(!modoIdLabel){pular(regs[$2]);}} //it's too easy
| jumpI		label					{if(!modoIdLabel){pular(buscarLabelLinha(nomeLabel));
								free(nomeLabel); nomeLabel = 0;}}

| cbr		reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label	{if(!modoIdLabel){ if(regs[$2]){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}
| tbl		reg separador label//nao é necessário no meu codigo pois isto é para loosers
| cmp_LT 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] <  regs[$4];}}
| cmp_LE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] <= regs[$4];}}
| cmp_EQ 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] == regs[$4];}}
| cmp_GE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] >= regs[$4];}}
| cmp_GT 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] >  regs[$4];}}
| cmp_NE 	reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = regs[$2] != regs[$4];}} //proximo passo: composicao do $6
| comp		reg separador reg separador reg		{if(!modoIdLabel){regs[$6] = 0;
									  if(regs[$2] <  regs[$4]) regs[$6] += 1; //caso cmp = LT
									  if(regs[$2] <= regs[$4]) regs[$6] += 2; //caso cmp = LE
									  if(regs[$2] == regs[$4]) regs[$6] += 4; //caso cmp = EQ
									  if(regs[$2] >= regs[$4]) regs[$6] += 8; //caso cmp = GE
									  if(regs[$2] >  regs[$4]) regs[$6] += 16; //caso cmp = GT
									  if(regs[$2] != regs[$4]) regs[$6] += 32; //caso cmp = NE
									}}
| cbr_LT 	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label  {if(!modoIdLabel){ if(testarBit($2, 0)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}
| cbr_LE 	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label {if(!modoIdLabel){ if(testarBit($2, 1)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}	
| cbr_EQ 	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label {if(!modoIdLabel){ if(testarBit($2, 2)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}
| cbr_GE 	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label {if(!modoIdLabel){ if(testarBit($2, 3)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}
| cbr_GT 	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label {if(!modoIdLabel){ if(testarBit($2, 4)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}
| cbr_NE	reg separador label {if(!modoIdLabel){aux = buscarLabelLinha(nomeLabel); free(nomeLabel); nomeLabel = 0;}} 
				    separador label {if(!modoIdLabel){ if(testarBit($2, 5)){
										pular(aux);
									}else{		
										pular(buscarLabelLinha(nomeLabel));
										free(nomeLabel); nomeLabel = 0;
									     }
									}
							}

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

//funçao para mapear em qual linha está cada label
int buscarLabelLinha(char c[]){
	for(int i=0; i< qtdLinha; i++){
		if(strcmp(labelN[i], c) == 0){
			return linha[i];
		}
	}
}

/*
* ele le do inicio, poderia melhorar fazendo executar a partir 
* no numero da linha mas estou sem tempo para pesquisar como 
* continuar a partir de uma linha específica
*/
void pular(int linha){
	fclose(yyin);  //no reg deve conter a linha para saltar
	yyin = fopen("teste.txt", "r"); 
	yylineno = 1;
	executar = 0;
	linhaPular = linha;
	yyrestart(yyin);	
}

short int testarBit(int reg, short int nbit){
	int saida = 0;
	int aux2;
	for(int i = 0; i<6; i++){
		aux2 = 5-i;
		if(regs[reg] / pow (2, aux2)){
			regs[reg] -= pow (2, aux2);
			if(nbit == aux2){
				saida = 1;
			}
		}
	}
	return saida;
}
