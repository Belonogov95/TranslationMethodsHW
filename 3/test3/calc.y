/* Mini Calculator */
/* calc.y */

%{
#include "heading.h"
int yyerror(char *s);
int yylex(void);
%}

%union{
  data int_val;
  /*string*	op_val;*/
}

%start	input 

%token	<int_val>	LITERAL
%left	PLUS
%left	MULT
%left   NEW_LINE 

%%

input: LITERAL NEW_LINE{
        cout << *($1.op) << endl;
    } ;


%%

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}


