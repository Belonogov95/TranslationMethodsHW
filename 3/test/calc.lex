/* Mini Calculator */
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
int yyerror(char *s);
/*int yylineno = 1;*/
%}

digit [0-9]
int_const {digit}

%%

{int_const} {

}

