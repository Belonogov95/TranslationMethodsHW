%{
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <stdarg.h>

#define YYSTYPE int

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n"; 
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"

int yylex();
void yyerror(char const *);
using namespace std;

%}

%token NUM
%token ABC

%% 
input: 'a' input { db("hello"); }
	 | /*empty */ 
	;
%%

int cnt = 0;

int yylex() {
	if (cnt < 5) {
		cnt++;	
		db2(NUM, ABC);
		db((int)'a');
		return 97;
	}
	return 0;
}

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main () {
	yyparse();


}



