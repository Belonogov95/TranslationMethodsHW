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

//////////////////////////////////
const int OR = 1900;
const int AND = 1901;
const int NOT = 1902;
const int LETTER = 1903;
const int XOR = 1904;
const int LEFTB = 1905;
const int RIGHTB = 1906;
const int DOLLAR = 0;

void shiftCur() {
	curToken = yylex();
	curValue = yylval;
}

int vv_and(InhData parent);

int vv_andprime(InhData parent);

int vv_input(InhData parent);

int vv_or(InhData parent);

int vv_orprime(InhData parent);

int vv_term(InhData parent);

int vv_xor(InhData parent);

int vv_xorprime(InhData parent);

int vv_and(InhData parent) {
	assert(curToken != AND);
	assert(curToken != DOLLAR);
	if (curToken == LEFTB) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_term(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_andprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("AND", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == LETTER) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_term(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_andprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("AND", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == NOT) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_term(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_andprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("AND", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	assert(curToken != OR);
	assert(curToken != RIGHTB);
	assert(curToken != XOR);
	assert(false);
}

int vv_andprime(InhData parent) {
	if (curToken == AND) {
		InhData vv_var_inh_3;
		InhData vv_var_inh_5;
		assert(curToken == AND);
		shiftCur();
		vv_var_inh_3 = parent; vv_var_inh_3.incH();
		int vv_var_3 = vv_term(vv_var_inh_3);
		vv_var_inh_5 = parent; vv_var_inh_5.incH();
		int vv_var_5 = vv_andprime(vv_var_inh_5);
		int vv_ret = 0;
		vv_ret = createNode(Node("ANDPrime", 3, createNode(Node("TAND", 0)), vv_var_3, vv_var_5));
		return vv_ret;
	}
	if (curToken == DOLLAR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ANDPrime", 0));
		return vv_ret;
	}
	assert(curToken != LEFTB);
	assert(curToken != LETTER);
	assert(curToken != NOT);
	if (curToken == OR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ANDPrime", 0));
		return vv_ret;
	}
	if (curToken == RIGHTB) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ANDPrime", 0));
		return vv_ret;
	}
	if (curToken == XOR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ANDPrime", 0));
		return vv_ret;
	}
	assert(false);
}

int vv_input(InhData parent) {
	assert(curToken != AND);
	assert(curToken != DOLLAR);
	if (curToken == LEFTB) {
		InhData vv_var_inh_2;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_or(vv_var_inh_2);
		int vv_ret = 0;
		head = vv_var_2;
		return vv_ret;
	}
	if (curToken == LETTER) {
		InhData vv_var_inh_2;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_or(vv_var_inh_2);
		int vv_ret = 0;
		head = vv_var_2;
		return vv_ret;
	}
	if (curToken == NOT) {
		InhData vv_var_inh_2;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_or(vv_var_inh_2);
		int vv_ret = 0;
		head = vv_var_2;
		return vv_ret;
	}
	assert(curToken != OR);
	assert(curToken != RIGHTB);
	assert(curToken != XOR);
	assert(false);
}

int vv_or(InhData parent) {
	assert(curToken != AND);
	assert(curToken != DOLLAR);
	if (curToken == LEFTB) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_xor(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_orprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("OR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == LETTER) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_xor(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_orprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("OR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == NOT) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_xor(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_orprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("OR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	assert(curToken != OR);
	assert(curToken != RIGHTB);
	assert(curToken != XOR);
	assert(false);
}

int vv_orprime(InhData parent) {
	assert(curToken != AND);
	if (curToken == DOLLAR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ORPrime", 0));
		return vv_ret;
	}
	assert(curToken != LEFTB);
	assert(curToken != LETTER);
	assert(curToken != NOT);
	if (curToken == OR) {
		InhData vv_var_inh_3;
		InhData vv_var_inh_5;
		assert(curToken == OR);
		shiftCur();
		vv_var_inh_3 = parent; vv_var_inh_3.incH();
		int vv_var_3 = vv_xor(vv_var_inh_3);
		vv_var_inh_5 = parent; vv_var_inh_5.incH();
		int vv_var_5 = vv_orprime(vv_var_inh_5);
		int vv_ret = 0;
		vv_ret =  createNode(Node("ORPrime", 3, createNode(Node("TOR", 0)), vv_var_3, vv_var_5));
		return vv_ret;
	}
	if (curToken == RIGHTB) {
		int vv_ret = 0;
		vv_ret = createNode(Node("ORPrime", 0));
		return vv_ret;
	}
	assert(curToken != XOR);
	assert(false);
}

int vv_term(InhData parent) {
	assert(curToken != AND);
	assert(curToken != DOLLAR);
	if (curToken == LEFTB) {
		InhData vv_var_inh_3;
		assert(curToken == LEFTB);
		shiftCur();
		vv_var_inh_3 = parent; vv_var_inh_3.incH();
		int vv_var_3 = vv_or(vv_var_inh_3);
		assert(curToken == RIGHTB);
		shiftCur();
		int vv_ret = 0;
		vv_ret = createNode(Node("TERM", 3, createNode(Node("TOPEN", 0)), vv_var_3, createNode(Node("TCLOSE", 0))));
		return vv_ret;
	}
	if (curToken == LETTER) {
		assert(curToken == LETTER);
		int vv_var_1 = curValue;
		shiftCur();
		int vv_ret = 0;
		vv_ret = createNode(Node("TERM", 1, createNode(Node(string(1, vv_var_1), 0)))); db2(parent.h, (char)(vv_var_1));
		return vv_ret;
	}
	if (curToken == NOT) {
		InhData vv_var_inh_3;
		assert(curToken == NOT);
		shiftCur();
		vv_var_inh_3 = parent; vv_var_inh_3.incH();
		int vv_var_3 = vv_term(vv_var_inh_3);
		int vv_ret = 0;
		vv_ret = createNode(Node("TERM", 2, createNode(Node("TNOT", 0)), vv_var_3));
		return vv_ret;
	}
	assert(curToken != OR);
	assert(curToken != RIGHTB);
	assert(curToken != XOR);
	assert(false);
}

int vv_xor(InhData parent) {
	assert(curToken != AND);
	assert(curToken != DOLLAR);
	if (curToken == LEFTB) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_and(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_xorprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("XOR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == LETTER) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_and(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_xorprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("XOR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	if (curToken == NOT) {
		InhData vv_var_inh_2;
		InhData vv_var_inh_4;
		vv_var_inh_2 = parent; vv_var_inh_2.incH();
		int vv_var_2 = vv_and(vv_var_inh_2);
		vv_var_inh_4 = parent; vv_var_inh_4.incH();
		int vv_var_4 = vv_xorprime(vv_var_inh_4);
		int vv_ret = 0;
		vv_ret = createNode(Node("XOR", 2, vv_var_2, vv_var_4));
		return vv_ret;
	}
	assert(curToken != OR);
	assert(curToken != RIGHTB);
	assert(curToken != XOR);
	assert(false);
}

int vv_xorprime(InhData parent) {
	assert(curToken != AND);
	if (curToken == DOLLAR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("XORPrime", 0));
		return vv_ret;
	}
	assert(curToken != LEFTB);
	assert(curToken != LETTER);
	assert(curToken != NOT);
	if (curToken == OR) {
		int vv_ret = 0;
		vv_ret = createNode(Node("XORPrime", 0));
		return vv_ret;
	}
	if (curToken == RIGHTB) {
		int vv_ret = 0;
		vv_ret = createNode(Node("XORPrime", 0));
		return vv_ret;
	}
	if (curToken == XOR) {
		InhData vv_var_inh_3;
		InhData vv_var_inh_5;
		assert(curToken == XOR);
		shiftCur();
		vv_var_inh_3 = parent; vv_var_inh_3.incH();
		int vv_var_3 = vv_and(vv_var_inh_3);
		vv_var_inh_5 = parent; vv_var_inh_5.incH();
		int vv_var_5 = vv_xorprime(vv_var_inh_5);
		int vv_ret = 0;
		vv_ret = createNode(Node("XORPrime", 3, createNode(Node("TXOR", 0)), vv_var_3, vv_var_5));
		return vv_ret;
	}
	assert(false);
}

int yyparse() {
	curToken = yylex();
	curValue = yylval;
	vv_input(InhData());
	return 0;
}

//////////////////////////////////

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



