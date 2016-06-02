/* Mini Calculator */
/* calc.y */

%{
#include <bits/stdc++.h>

#define YYSTYPE int

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n"; 
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"

int yylex();
void yyerror(char const *);
int curToken;
int curValue;
int yylval;
using namespace std;
const int N = 1e5;

struct Node {
    string type;
    vector < int > ch;
	Node() { }
    Node(string type, int cnt, ...): type(type) {
		/*db2(type, cnt);*/
        va_list args;  
        va_start(args, cnt); 
        for (int i = 0; i < cnt; i++)
            ch.push_back(va_arg(args, int));
        va_end(args);
    }
};

vector < Node > data;

int createNode(Node v) {
	data.push_back(v);
	return data.size() - 1;
}

int head = -1;

struct InhData {
	int h;
	InhData():h(0) { }
	void incH() {
		h++;
	}
};

%}

%token OR
%token AND
%token NOT
%token LETTER
%token XOR
%token LEFTB
%token RIGHTB
DATA_TYPE InhData 

/*__PARRENT__*/

/*//or: xor orprime { $$ = createNode(Node("OR", 2, $1, $2)); };*/

/*%left   EQ*/

%%


input: { $2 = $$; $2.incH(); } or { head = $2; } ;

or: {$2 = $$; $2.incH(); } xor  {$4 = $$; $4.incH(); } orprime { $$ = createNode(Node("OR", 2, $2, $4)); };


orprime:   { $$ = createNode(Node("ORPrime", 0)); }
	   | OR {$3 = $$; $3.incH(); } xor {$5 = $$; $5.incH(); } orprime  { $$ =  createNode(Node("ORPrime", 3, createNode(Node("TOR", 0)), $3, $5)); }
	   ;


xor: {$2 = $$; $2.incH(); } and {$4 = $$; $4.incH(); } xorprime { $$ = createNode(Node("XOR", 2, $2, $4)); };

xorprime:  { $$ = createNode(Node("XORPrime", 0)); }
	   	| XOR {$3 = $$; $3.incH(); } and {$5 = $$; $5.incH(); } xorprime  { $$ = createNode(Node("XORPrime", 3, createNode(Node("TXOR", 0)), $3, $5)); }
		;

and: {$2 = $$; $2.incH(); } term {$4 = $$; $4.incH(); } andprime {$$ = createNode(Node("AND", 2, $2, $4)); };


andprime:  { $$ = createNode(Node("ANDPrime", 0)); }
		| AND {$3 = $$; $3.incH(); } term {$5 = $$; $5.incH(); } andprime { $$ = createNode(Node("ANDPrime", 3, createNode(Node("TAND", 0)), $3, $5)); }
		;	

term: LETTER { $$ = createNode(Node("TERM", 1, createNode(Node(string(1, $1), 0)))); db2(parent.h, (char)($1)); }
   	| LEFTB {$3 = $$; $3.incH(); } or RIGHTB { $$ = createNode(Node("TERM", 3, createNode(Node("TOPEN", 0)), $3, createNode(Node("TCLOSE", 0)))); }
	| NOT {$3 = $$; $3.incH(); } term { $$ = createNode(Node("TERM", 2, createNode(Node("TNOT", 0)), $3)); }
	;
%%

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
		return LETTER;
	}
	assert(s[cur] == '(' ||
		   s[cur] == ')' ||
		   s[cur] == '&' ||
		   s[cur] == '!' ||
		   s[cur] == '|' ||
		   s[cur] == '^');
	int p = cur++;
	if (s[p] == '(') return LEFTB;
	if (s[p] == ')') return RIGHTB;
	if (s[p] == '&') return AND;
	if (s[p] == '!') return NOT;
	if (s[p] == '^') return XOR;
	if (s[p] == '|') return OR; 
	assert(false);
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



