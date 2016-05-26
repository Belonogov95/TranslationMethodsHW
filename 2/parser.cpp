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

using namespace std;

#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define epr(...) fprintf(stderr, __VA_ARGS__)
#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n"; 
#define all(a) (a).begin(), (a).end()

#define equal equalll
#define less lesss
const int N = -1;
const long long INF = 1e9 + 19;


enum Token {
    LPAREN, RPAREN, END, OR, AND, XOR, NOT, VAR
};

struct LexicalAnalyzer {
    string s;
    Token curToken;
    string var;
    int cur;
    LexicalAnalyzer(string s): s(s), cur(0) { }

    bool isletter(char ch) {
        return 'a' <= ch && ch <= 'z';
    }

    Token getToken() {
        return curToken;
    }

    string getVar() {
        return var;
    }

    void next() {
        for (; cur < (int)s.size() && isspace(s[cur]); cur++);
        if (cur == (int)s.size())  {
            curToken = END;
            return;
        }
        if (s[cur] == '(')
            curToken = LPAREN;
        else if (s[cur] == ')')
            curToken = RPAREN;
        else if (s[cur] == '&')
            curToken = AND;
        else if (s[cur] == '!')
            curToken = NOT;
        else if (s[cur] == '|')
            curToken = OR;
        else if (s[cur] == '^')
            curToken = XOR;
        else if (isletter(s[cur])) {
            curToken = VAR;
            var = s.substr(cur, 1);
        }
        else
            assert(false);
        cur++;
    }
};

struct Node {
    string type;
    Node * l, * r;
    Node(string type, Node * l, Node * r): type(type), l(l), r(r) { }
    Node(string var): type(var), l(NULL), r(NULL) { }
};

struct Parser {
    LexicalAnalyzer lex;

    Parser(string s): lex(s) {
        lex.next();
    }

    Node * parseTerm() {
        if (lex.getToken() == LPAREN) {
            lex.next();
            Node * tmp = parseOR();
            assert(lex.getToken() == RPAREN);
            lex.next();
            return tmp;
        } 
        if (lex.getToken() == NOT) {
            lex.next();
            Node * tmp = parseTerm();
            return new Node("!", tmp, NULL);
        }
        if (lex.getToken() == VAR) {
            string v = lex.getVar();
            lex.next();
            return new Node(v);
        }
        assert(false);
    }

    Node * parseAND() {
        Node * res = parseTerm();
        while (lex.getToken() == AND) {
            lex.next();
            res = new Node("&", res, parseTerm());
        } 
        return res;
    }

    Node * parseXOR() {
        Node * res = parseAND();
        while (lex.getToken() == XOR) {
            lex.next();
            res = new Node("^", res, parseAND());
        }
        return res;
    }

    Node * parseOR() {

        Node * res = parseXOR();
        while (lex.getToken() == OR) {
            lex.next();
            res = new Node("|", res, parseXOR());
        }
        return res;
    }
};

void print(Node * v, int tab) {
    if (v == NULL) return;
    print(v->r, tab + 1);
    for (int i = 0; i < tab; i++)
        cerr << "\t";
    cerr << v->type << endl;
    print(v->l, tab + 1);
}

void read() {
    string s;
    getline(cin, s);
    Parser parser(s);
    Node * head = parser.parseOR();
    print(head, 0);
}

void solve() {

}

void stress() {

}


int main(){
#ifdef DEBUG
    freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
#endif
    if (1) {
        int k = 1;
        for (int tt = 0; tt < k; tt++) {
            read();
            solve();
        }
    }
    else {
        stress();
    }

    return 0;
}


