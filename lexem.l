%option yylineno

%{
#include <stdlib.h>
#include "int.h"
#include "parser.tab.h"
void yyerror(char *);

%}

%%
\"[^\"]*\"  {yylval.word = strpbrk(strdup(yytext), "\\<=->/'\""); return VAL_STRING;}
\'[^\']*\'  {yylval.word = strdup(yytext); return VAL_STRING;}

"long"          {yylval.dataType=0; return LON;};
"char"          {yylval.dataType=0; return CHA;};
"string"        {yylval.dataType=0; return STR;};
"double"        {yylval.dataType=0; return DOU;};
"float"         {yylval.dataType=0; return FLO;};
"short"         {yylval.dataType=0; return SHO;};
"int"           {yylval.dataType=0; return INT;};

"var"           {yylval.dataType=0; return VAR;};
">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"println"       return PRINTLN;
"print"         return PRINT;
"strCat"        return STRCAT;
"lambda"		return LAMBDA;

[a-zA-Z_][0-9a-zA-Z_]*      {
                yylval.iden = strdup(yytext);
                return ID;
            }

[0-9]+"."+[0-9]* {
                yylval.dValue = atof(yytext);
                return DOUBLE;
            }        
            

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {

                    yylval.iValue = atol(yytext);
                    return INTEGER;


            }

"("		{
	return LPAR;
}

")"			{
	return RPAR;
}

";"			{
	return SEMCOL;
}

[->=+*/{}.] {
                return *yytext;
             }


[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");


%%

int yywrap(void) {
    return 1;
}
