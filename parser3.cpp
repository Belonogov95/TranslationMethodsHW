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
    vector < Node * > ch;
    Node(string type, int cnt, ...): type(type) {
        va_list args;  
        va_start(args, cnt); 
        for (int i = 0; i < cnt; i++)
            ch.push_back(va_arg(args, Node *));
        va_end(args);
    }
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
            return new Node("TERM", 3, new Node("TOPEN", 0), tmp, new Node("TCLOSE", 0));
        } 
        if (lex.getToken() == NOT) {
            lex.next();
            Node * tmp = parseTerm();
            return new Node("TERM", 2, new Node("TNOT", 0), tmp);
        }
        if (lex.getToken() == VAR) {
            string v = lex.getVar();
            lex.next();
            return new Node("TERM", 1, new Node(v, 0));
        }
        //db(lex.getToken());
        assert(false);
    }

    Node * parseCPrime() {
        if (lex.getToken() == AND) {
            lex.next();
            Node * v = parseTerm();
            Node * u = parseCPrime();
            return new Node("CPrime", 3, new Node("TAND", 0), v, u);
        }
        else {
            auto t = lex.getToken();
            assert(t == XOR || t == OR || t == RPAREN || t == END);
            return new Node("Bprime", 0);
        }
    }

    Node * parseAND() {
        Node * v = parseTerm();
        Node * u = parseCPrime();
        return new Node("AND", 2, v, u);
    }

    Node * parseBPrime() {
        if (lex.getToken() == XOR) {
            lex.next();
            Node * v = parseAND();
            Node * u = parseBPrime();
            return new Node("BPrime", 3, new Node("TXOR", 0), v, u);
        }
        else {
            auto t = lex.getToken();
            assert(t == OR || t == RPAREN || t == END);
            return new Node("BPrime", 0);
        }
    }

    Node * parseXOR() {
        Node * v = parseAND();
        Node * u = parseBPrime();
        return new Node("XOR", 2, v, u);
    }

    Node * parseAPrime() {
        if (lex.getToken() == OR) {
            lex.next();
            Node * v = parseXOR();
            Node * u = parseAPrime();
            return new Node("APrime", 3, new Node("TOR", 0), v, u);
        }
        else {
            assert(lex.getToken() == RPAREN || lex.getToken() == END);
            return new Node("APrime", 0);
        }
    }

    Node * parseOR() {
        Node * v = parseXOR();
        Node * u = parseAPrime();
        return new Node("OR", 2, v, u);
    }
};

//void print(Node * v, int tab) {
    //if (v == NULL) return;
    //print(v->r, tab + 1);
    //for (int i = 0; i < tab; i++)
        //cerr << "\t";
    //cerr << v->type << endl;
    //print(v->l, tab + 1);
//}


set < string > used;


void rec(Node * v, string name, int h) {
    //db(h);
    //assert(h < 100);
    //db(v->ch.size());
    for (auto u: v->ch) {
        string g = u->type;
        //if (u->ch.empty()) continue;
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

void read() {
    string s;
    getline(cin, s);
    Parser parser(s);
    Node * head = parser.parseOR();
    cout << "digraph G {\n"; 
    rec(head, head->type, 0);
    cout << "}\n";

    //Node * head = parser.parseOR();
    //print(head, 0);
}

void solve() {

}

void stress() {

}


int main(){
#ifdef DEBUG
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
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





