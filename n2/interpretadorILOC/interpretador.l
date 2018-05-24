%option yylineno 
%{
#include <stdlib.h>
#include "interpretador.tab.h"
short int executar = 1;
int linhaPular;
extern char *c;
#define inicio if(!executar && yylineno == linhaPular)executar = 1;
%}


%%

"add"		{inicio if(executar){ return add;}		}	
"sub"		{inicio if(executar){ return sub;}		}  
"mult"		{inicio if(executar){ return mult;}		} 
"div"		{inicio if(executar){ return div1;}		}
"addI"		{inicio if(executar){ return addI;}		}
"subI"		{inicio if(executar){ return subI;}		}
"rsubI"		{inicio if(executar){ return rsubI;	}	}
"multI"		{inicio if(executar){ return multI;	}	}
"divI"		{inicio if(executar){ return divI;}		}
"rdivI"		{inicio if(executar){ return rdivI;}		}
"lshift"	{inicio if(executar){ return lshift;}	}
"lshiftI"	{inicio if(executar){ return lshiftI;}	}
"rshift"	{inicio if(executar){ return rshift;}	}
"rshiftI"	{inicio if(executar){ return rshiftI;}	}
"and"		{inicio if(executar){ return and;}		}
"andI"		{inicio if(executar){ return andI;}		}
"or"		{inicio if(executar){ return or;}		}
"orI"		{inicio if(executar){ return orI;}		}
"xor"		{inicio if(executar){ return xor;}		}
"xorI"		{inicio if(executar){ return xorI;}		}
"loadI"		{inicio if(executar){ return loadI;}		}
"load"		{inicio if(executar){ return load;}		}
"loadAI"	{inicio if(executar) {return loadAI;}	}
"loadAO"	{inicio if(executar) {return loadAO;}	}
"cload"		{inicio if(executar) {return cload;	}	}
"cloadAI"	{inicio if(executar) {return cloadAI;}	}
"cloadAO"	{inicio if(executar) {return cloadAO;}	}
"store"		{inicio if(executar) {return store;}		}
"storeAI"	{inicio if(executar) {return storeAI;}	}
"storeAO"	{inicio if(executar) {return storeAO;	}}
"cstore"	{inicio if(executar) {return cstore;	}}
"cstoreAI"	{inicio if(executar) {return cstoreAI;}	}
"cstoreAO"	{inicio if(executar) {return cstoreAO;}	}
"i2i"		{inicio if(executar) {return i2i;}		}
"c2c"		{inicio if(executar) {return c2c;}		}
"c2i"		{inicio if(executar) {return c2i;}		}
"i2c"		{inicio if(executar) {return i2c;}		}
"jump"		{inicio if(executar) {return jump;}		}
"jumpI"		{inicio if(executar) {return jumpI;}		}
"cbr"		{inicio if(executar) {return cbr;	}	}
"tbl"		{inicio if(executar) {return tbl;	}	}
"cmp_LT"	{inicio if(executar) {return cmp_LT;}	}
"cmp_LE"	{inicio if(executar) {return cmp_LE;}	}
"cmp_EQ"	{inicio if(executar) {return cmp_EQ;}	}
"cmp_GE"	{inicio if(executar) {return cmp_GE;}	}
"cmp_GT"	{inicio if(executar) {return cmp_GT;}	}
"cmp_NE"	{inicio if(executar) {return cmp_NE;}	}
"comp"		{inicio if(executar) {return comp;}		}
"cbr_LT"	{inicio if(executar) {return cbr_LT;}	}
"cbr_LE"	{inicio if(executar) {return cbr_LE;}	}
"cbr_EQ"	{inicio if(executar) {return cbr_EQ;}	}
"cbr_GE"	{inicio if(executar) {return cbr_GE;}	}
"cbr_GT"	{inicio if(executar) {return cbr_GT;}	}
"cbr_NE"	{inicio if(executar) {return cbr_NE;}	}
"nop"		{inicio if(executar) {return nop;}		}
"input"		{inicio if(executar) {return inputi;}	}
"output"	{inicio if(executar) {return outputi;}	}
"inputC"	{inicio if(executar) {return inputc;}	}
"outputC"	{inicio if(executar) {return outputc;}	}
[r][0-9]	{inicio if(executar){ char num [1]; 
				num[0] = yytext[1];
				yylval = atoi(num); 
				return reg;}	}
","		{inicio if(executar) {return virgula;}	}
";"		{inicio if(executar) {return pontoVirgula;}	}
":"		{inicio if(executar) {return doisPontos;}	}
[a-zA-Z]	{inicio if(executar){ yylval = yytext[0]; return caractere;}}
[a-zA-Z]([a-zA-Z]|[0-9]|-)*	{inicio if(executar){
					c = malloc(sizeof(yytext)); 
					strcpy(c, yytext); 
					return label;
				}}
[0-9]+		{inicio if(executar){ yylval = atoi(yytext);	return num;		}}
"["		{inicio if(executar) {return abreColchete;}	}
"]"		{inicio if(executar) {return fechaColchete;}	}
[ \t\n]		{/*ignora tab e espaco*/}
.		{inicio if(executar) {return erro;}		}

%%
