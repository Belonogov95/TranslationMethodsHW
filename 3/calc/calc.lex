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


%%

{int_const}	{ 
    data tmp; 
    tmp.x = atoi(yytext); 
    yylval.int_val = tmp; 
    return INTEGER_LITERAL; 
}

"+"		{ 
    //yylval.int_val.op = new std::string(yytext); 
    return PLUS; 
}

"*"		{ 
    //yylval.int_val.op = new std::string(yytext); 
    return MULT; 
}

[ \t]*		{}
[\n]		{ yylineno++;	}

.		{ std::cerr << "SCANNER " << yytext << endl; yyerror(""); exit(1);	}

