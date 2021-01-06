

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "int.h"

FILE *yyin;
/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *intV(long i);
nodeType *douV(double i);
nodeType *ide(char *name);
nodeType *strV(char *i);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);

%}

%union {
    double dValue;
    char *word;
    short sValue;
    long iValue;                 /* integer value */
	char *iden;
    nodeType *nPtr;             /* node pointer */
    int dataType;               /* data type */
};

%token VAR INT BYT STR FLO SHO LON DOU INTDEFNO CHA VARDEF FLODEF INTDEF LONDEF CHADEF DOUDEF STRDEF SEMCOL RPAR LPAR SHODEF LAMBDA 
%token <iValue> INTEGER
%token <sValue> SHORT
%token <dValue> DOUBLE
%token <iden> ID
%token <word> VAL_STRING
%token WHILE IF PRINTLN PRINT STRCAT
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list vardefine kosul dortislem karsilastir karaktergirdisi lambda_function_call parameter_list

%%

program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          SEMCOL                            { $$ = opr(SEMCOL, 2, NULL, NULL); }
        | expr SEMCOL                       { $$ = $1; }
        | PRINT LPAR expr RPAR SEMCOL                 { $$ = opr(PRINT, 1, $3); }
        | PRINTLN expr SEMCOL               { $$ = opr(PRINTLN, 1, $2); }
        | vardefine
        | WHILE LPAR expr RPAR stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | kosul
        | '{' stmt_list '}'              { $$ = $2; }
		| lambda_function_call
        ;

function_call:
		 ID LPAR identifier_list RPAR ';'
		 |ID LPAR RPAR ';'
		;
		
lambda_function_call:
		  LAMBDA LPAR parameter_list RPAR ';'
		;
	
parameter_list:
		  parameter_list ',' 
		 |expr;
		 |ID;
		;
	
identifier_list:
		  ID ',' identifier_list
		 | ID	 
		;


kosul:
          IF LPAR expr RPAR stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF LPAR expr RPAR stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        ;

vardefine:   
         INT ID '=' expr SEMCOL            {$$ = opr(INTDEF, 2, ide($2), $4);}  
        | STR ID '=' expr SEMCOL            {$$ = opr(STRDEF, 2, ide($2), $4);}
        | SHO ID '=' expr SEMCOL            {$$ = opr(SHODEF, 2, ide($2), $4);}
        | CHA ID '=' expr SEMCOL            {$$ = opr(CHADEF, 2, ide($2), $4);}
        | FLO ID '=' expr SEMCOL            {$$ = opr(FLODEF, 2, ide($2), $4);}
        | ID '=' expr SEMCOL            {$$ = opr(INTDEFNO, 2, ide($1), $3);}  
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(SEMCOL, 2, $1, $2); }
        ;

expr:
          INTEGER               { $$ = intV($1); }
		| DOUBLE              	{ $$ = douV($1); }
        | ID              		{ $$ = ide($1); }
        | expr '.' STRCAT LPAR expr RPAR         { $$ = opr(STRCAT, 2, $1, $5); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | dortislem
        | karsilastir
        | karaktergirdisi
        | LPAR expr RPAR          { $$ = $2; }
        ;

karaktergirdisi:
         VAL_STRING             { $$ = strV($1); }
        ;


dortislem:
          expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        ;

karsilastir:
          expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        ;


%%

nodeType *ide(char *name) {
    nodeType *p;
    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIdentifierNode;
	
    p->ide.name=name;
	
    return p;
}

nodeType *intV(long i) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIntegerValue;
    p->intV.value = i;
    return p;
}

nodeType *douV(double i) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeDoubleValue;
    p->douV.value = i;

    return p;
}


nodeType *strV(char *i){
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeStringValue;
    p->strV.value = i;

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}


int main(int argc, char **argv) {
    yyin = fopen(argv[1] , "r");
    globalSymbolTable = initialize(globalSymbolTable);
    globalRunTimeValue = (runTimeValue *) malloc(sizeof(runTimeValue));
    yyparse();
    fclose(yyin);
    return 0;
}
