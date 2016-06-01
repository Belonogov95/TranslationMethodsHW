/* Mini Calculator */
/* calc.y */

%{
#include "heading.h"
int yyerror(char *s);
int yylex(void);
%}

%union{
  data int_val;
}

%start	input 

%token	<int_val>	INTEGER_LITERAL
%token  <int_val>   F_NAME

%type	<int_val>	func;
%type	<int_val>	decl;
%type	<int_val>	body;
%type	<int_val>	case;
%type	<int_val>	caseCont;
%type	<int_val>	args;

%left	PLUS
%left	MULT
%left   COL2
%left   INT
%left   ARROW
%left   NEW_LINE
%left   GGG

/*%left   EQ*/

%%

input:  /* empty */
        | func input { cout << (*($1.code)); }
        ;

func: decl body {data tmp; tmp.code = new string(*($1.code) + "{\n" + (*($2.code)) + "\n}\n"); $$ = tmp; }
    ;

decl: F_NAME COL2 INT args { 
    data tmp; 
    string ar;    
    for (int i = 0; i < $4.cntArgs; i++) {
        ar += "int " + (char)('a' + i);
        if (i + 1 < $4.cntArgs)
            ar += ", ";
    }
    tmp.code = new string("int " + (*($1.code)) + " (" + ar + ")" );
    $$ = tmp;
};

args: NEW_LINE { data tmp; tmp.cntArgs= 0; $$ = tmp;}
    | ARROW INT args { data tmp; tmp.cntArgs = $3.cntArgs + 1; $$ = tmp; }
    ;

body: caseCont { data tmp; $$ = tmp;} ;



caseCont:  NEW_LINE     {data tmp; $$ = tmp; }
         | case caseCont { data tmp; $$ = tmp; }
         ;

case: GGG { data tmp; tmp.code = new string("while empty"); $$ = tmp; }; 


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



