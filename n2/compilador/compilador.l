%option yylineno 
%{
#include <stdlib.h>
#include "compilador.tab.h"
#define tamVar 16
#define inicio if(1)
extern char *nomeLabel;
short int executar = 1;
%}


%%

"+"		{inicio if(executar){ return add;}		}	
"-"		{inicio if(executar){ return sub;}		}  
"*"		{inicio if(executar){ return mult;}		} 
"/"		{inicio if(executar){ return div1;}		}
"<<"		{inicio if(executar){ return shiftLeft;}	}
">>"		{inicio if(executar){ return shiftRight;}	}
"&"		{inicio if(executar){ return and;}		}
"|"		{inicio if(executar){ return or;}		}
"^"		{inicio if(executar){ return xor;}		}
"!"		{inicio if(executar){ return not;}		}
"input"		{inicio if(executar){return input1;}		}
"output"	{inicio if(executar){return output1;}		}
"int"		{inicio if(executar) { return inteiro;}		}
"char"		{inicio if(executar) { return caracter;}	}
"string"	{inicio if(executar) { return string;}		}
"enquanto"	{inicio if(executar) { return enquanto;}	}
"se"		{inicio if(executar) { return se;}		}
"senao"		{inicio if(executar) { return senao;}		}
"fim"		{inicio if(executar) { return end;}		}
[a-zA-Z]([a-zA-Z]|[0-9])*	{inicio if(executar){
					nomeLabel = malloc(sizeof(char)*tamVar);
					strcpy(nomeLabel, yytext); 
					return label;
				}}
"<"		{inicio if(executar) { return menor;}		}
"="		{inicio if(executar) { return igual;}		}
">"		{inicio if(executar) { return maior;}		}
[0-9]+		{inicio if(executar) { yylval = atoi(yytext);	return num;		}}
[ \t\n]		{/*ignora tab e espaco*/}
"{"		{inicio if(executar) { return abreChave;}	}
"}"		{inicio if(executar) { return fechaChave;}	}
"("		{inicio if(executar) { return abreParentese;}	}
")"		{inicio if(executar) { return fechaParentese;}	}

";"		{inicio if(executar) { return pontoVirgula;}	}
","		{inicio if(executar) { return virgula;}		}
.		{inicio if(executar) { return erro;}		}
%%
