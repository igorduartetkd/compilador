/* just like Unix wc */
%{

#include "analisador.tab.h"
//tirar duvida: palavras coladas estão sendo detectadas
//qual o nome dos regsitradores
%}

%%

"add"		{ return add;		}	
"sub"		{ return sub;		}  
"mult"		{ return mult;		} 
"div"		{ return div1;		}
"addI"		{ return addI;		}
"subI"		{ return subI;		}
"rsubI"		{ return rsubI;		}
"multI"		{ return multI;		}
"divI"		{ return divI;		}
"rdivI"		{ return rdivI;		}
"lshift"	{ return lshift;	}
"lshiftI"	{ return lshiftI;	}
"rshift"	{ return rshift;	}
"rshiftI"	{ return rshiftI;	}
"and"		{ return and;		}
"andI"		{ return andI;		}
"or"		{ return or;		}
"orI"		{ return orI;		}
"xor"		{ return xor;		}
"xorI"		{ return xorI;		}
"loadI"		{ return loadI;		}
"load"		{ return load;		}
"loadAI"	{ return loadAI;	}
"loadAO"	{ return loadAO;	}
"cload"		{ return cload;		}
"cloadAI"	{ return cloadAI;	}
"cloadAO"	{ return cloadAO;	}
"store"		{ return store;		}
"storeAI"	{ return storeAI;	}
"storeAO"	{ return storeAO;	}
"cstore"	{ return cstore;	}
"cstoreAI"	{ return cstoreAI;	}
"cstoreAO"	{ return cstoreAO;	}
"i2i"		{ return i2i;		}
"c2c"		{ return c2c;		}
"c2i"		{ return c2i;		}
"i2c"		{ return i2c;		}
"jump"		{ return jump;		}
"jumpI"		{ return jumpI;		}
"cbr"		{ return cbr;		}
"tbl"		{ return tbl;		}
"cmp_LT"	{ return cmp_LT;	}
"cmp_LE"	{ return cmp_LE;	}
"cmp_EQ"	{ return cmp_EQ;	}
"cmp_GE"	{ return cmp_GE;	}
"cmp_GT"	{ return cmp_GT;	}
"cmp_NE"	{ return cmp_NE;	}
"comp"		{ return comp;		}
"cbr_LT"	{ return cbr_LT;	}
"cbr_LE"	{ return cbr_LE;	}
"cbr_EQ"	{ return cbr_EQ;	}
"cbr_GE"	{ return cbr_GE;	}
"cbr_GT"	{ return cbr_GT;	}
"cbr_NE"	{ return cbr_NE;	}
"nop"		{ return nop;		}
[r][0-9]	{ return reg;		}
","		{ return virgula;	}
";"		{ return pontoVirgula;	}
":"		{ return doisPontos;	}
[a-zA-Z]([a-zA-Z]|[0-9]|-)*	{ return label;		}
[0-9]+		{ return num;		}
"["		{ return abreColchete;	}
"]"		{ return fechaColchete;	}
[ \t\n]		{/*ignora tab e espaco*/}
.		{ return erro;		}

%%
