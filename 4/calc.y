/* Mini Calculator */
/* calc.y */

%{
#include <bits/stdc++.h>

#define YYSTYPE int

%}

%token NUM


%%

input: allCode { 
 

input: OR  { head = $1; db("HHHHHHHHHHH"); } ;

OR: XOR ORPrime { $$ = createNode(Node("OR", 2, $1, $2)); };


ORPrime:  /*empty*/ { $$ = createNode(Node("ORPrime", 0)); }
	   | '|' XOR ORPrime  { $$ =  createNode(Node("ORPrime", 3, createNode(Node("TOR", 0)), $2, $3)); }
	   ;


XOR: AND XORPrime { $$ = createNode(Node("XOR", 2, $1, $2)); };

XORPrime: /*empty*/ { $$ = createNode(Node("XORPrime", 0)); }
	   	| '^' AND XORPrime  { $$ = createNode(Node("XORPrime", 3, createNode(Node("TXOR", 0)), $2, $3)); }
		;

AND: TERM ANDPrime {$$ = createNode(Node("AND", 2, $1, $2)); };


ANDPrime: /*empty */  { $$ = createNode(Node("ANDPrime", 0)); }
		| '&' TERM ANDPrime { $$ = createNode(Node("ANDPrime", 3, createNode(Node("TAND", 0)), $2, $3)); }
		;	

TERM: 'a' { $$ = createNode(Node("TERM", 1, createNode(Node(string(1, $1), 0)))); }
   	| '(' OR ')' { $$ = createNode(Node("TERM", 3, createNode(Node("TOPEN", 0)), $2, createNode(Node("TCLOSE", 0)))); }
	| '!' TERM { $$ = createNode(Node("TERM", 2, createNode(Node("TNOT", 0)), $2)); }
	;

#include <ctype.h>

string s;
int cur;

int yylex (void) {
	for (; cur < (int)s.size() && (s[cur] == ' ' || s[cur] == '\t'); cur++);
	if (cur == (int)s.size()) {
		/*db("RET 0");*/
		return 0;
	}
	/*db(s[cur]);*/

	if (isalpha(s[cur])) {
		yylval = s[cur++];			
		
		return 'a';
	}
	assert(s[cur] == '(' ||
		   s[cur] == ')' ||
		   s[cur] == '&' ||
		   s[cur] == '!' ||
		   s[cur] == '|' ||
		   s[cur] == '\n' ||
		   s[cur] == '^');
	return s[cur++];
}

#include <stdio.h>

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

set < string > used;

void rec(int v, string name, int h) {
    for (auto u: data[v].ch) {
        string g = data[u].type;
        for (int i = 1; ; i++) {
            string tmp = g + to_string(i);
            if (used.count(tmp) == 0) {
                cout << "\t" + name + "->" + tmp << endl;
                cout << "\t" + tmp + "[label=" + g + "]" << endl; 
                if (islower(g[0]))
                    cout << "\t" + tmp + "[shape=box,style=filled,color=green]" << endl; 
                if (g[0] == 'T' && g != "TERM")
                    cout << "\t" + tmp + "[shape=box,style=filled,color=grey]" << endl; 
                if (g == "AND") cout << "\t" + tmp + "[style=filled,color=red]" << endl; 
                if (g == "OR") cout << "\t" + tmp + "[style=filled,color=blue]" << endl; 
                if (g == "XOR") cout << "\t" + tmp + "[style=filled,color=yellow]" << endl; 

                used.insert(tmp);
                rec(u, tmp, h + 1);
                break;
            }
        }
    }  
}


int main () {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	getline(cin, s);
	yyparse();
	db2(head, data.size());


    cout << "digraph G {\n"; 
	rec(head, data[head].type, 0);
    cout << "}\n";
}



