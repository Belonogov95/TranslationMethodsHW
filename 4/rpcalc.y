/* Reverse polish notation calculator. */
%{
#include <stdio.h>
#include <math.h>

#define YYSTYPE double

int yylex (void);
void yyerror (char const *);
%}

%token NUM

%% /* Grammar rules and actions follow. */

input: /* empty */
	| input line
	;

line: '\n'
	| expr '\n' { printf ("%.10g\n", $1); }
	;

expr:
	NUM { $$ = $1; }
	| expr expr '+' { $$ = $1 + $2; }
	| expr expr '-' { $$ = $1 - $2; }
	| expr expr '*' { $$ = $1 * $2; }
	| expr expr '/' { $$ = $1 / $2; }
	| expr expr '^' { $$ = pow ($1, $2); } /* exponentiation */
	| expr 'n' { $$ = -$1; } /* Unary minus */
	;
%%

/* The lexical analyzer returns a double floating point
number on the stack and the token NUM, or the numeric code
of the character read if not a number. It skips all blanks
and tabs, and returns 0 for end-of-input. */
#include <ctype.h>

int yylex (void) {
	int c;
	/* Skip white space. */
	while ((c = getchar ()) == ' ' || c == '\t')
	continue;
	/* Process numbers. */
	if (c == '.' || isdigit (c)) {
		ungetc (c, stdin);
		scanf ("%lf", &yylval);
		return NUM;
	}
	/* Return end-of-input. */
	if (c == EOF)
		return 0;
	/* Return a single char. */
	return c;
}

#include <stdio.h>
/* Called by yyparse on error. */

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main (void) {
 	return yyparse ();
}



