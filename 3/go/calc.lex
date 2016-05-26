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

ttt         [0-9a-zA-Z]
word        {ttt}+

alf [\*\-\+\/\(\)\<\>\"\%\,\\]
expr        {alf}+


%%


{word} {
    /*cerr << "word Parsed\n";*/
    data tmp;
    tmp.code = new string(yytext); 
    yylval.int_val = tmp;
    return F_NAME;
}

"::"   {
    /*cerr << "COL2 Parsed\n";*/
    return COL2;
}

"|" {
    return OR;
}

"="  {
    /*cerr << "= Parsed\n";*/
    return EQ;
}


"->" {
    /*cerr << "ARROW Parsed\n";*/
    return ARROW;
}

[ \t]*		{}


{expr} {
    data tmp;
    tmp.code = new string(yytext); 
    yylval.int_val = tmp;
    return SIGNS;
}


[\n]		{ 
    return NEW_LINE;
}

.		{ std::cerr << "SCANNER "; exit(1);	}

