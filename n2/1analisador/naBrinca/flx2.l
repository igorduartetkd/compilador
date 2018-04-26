/* tradutor simples */
%{
%}

%%

"nos"		{ printf("nois"); }
"vamos"		{ printf("vai"); }
"no"		{ printf("gluglu");}
.		{ printf("%s", yytext); }
%%


main(int argc, char **argv)
{
yylex();
}
