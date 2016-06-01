/* Mini Calculator */
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
int yyerror(char *s);
/*int yylineno = 1;*/
%}

digit		[0-9]
int_const	{digit}+
alf [0-9a-zA-Z\*\-\+\/\(\) \t] 
expr        {alf}+

%%

{expr} {
    data tmp; 
    tmp.op = new string(yytext); 
    yylval.int_val = tmp;
    ///cerr << "dddd\n";
    return LITERAL; 
}

[ \t]*		{}
[\n]*	{ return NEW_LINE;	}

.		{ std::cerr << "SCANNER " << yytext << endl; yyerror(""); exit(1);	}

