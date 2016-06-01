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
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define all(a) (a).begin(), (a).end()

#define equal equalll
#define less lesss
const int N = -1;
const long long INF = 1e9 + 19;
const string EPS = "EPS";
const string DOLLAR = "DOLLAR";

struct Rule {
	string name;
	string code;
	vector < string > ch;
	Rule(string name, string code, vector < string > ch): name(name), code(code), ch(ch) { }
};



vector < string > part1;
vector < string > part2;
vector < string > part3;
vector < string > part4;
map < string, set < string > > first;
map < string, set < string > > follow;


void read() {
	vector < string > data;
	string s;
	while (getline(cin, s)) {
		data.pb(s);
	}		
	int p1 = -1;
	int p2 = -1;
	int p3 = -1;
	int p4 = -1;
	for (int i = 0; i < (int)data.size(); i++) {
		if (data[i].find("%{") != string::npos) p1 = i;
		if (data[i].find("%}") != string::npos) p2 = i;
		if (p3 == -1 && data[i].find("%%") != string::npos) p3 = i;
		if (p3 != -1) {
			if (data[i].find("%%") != string::npos) p4 = i;
		}
	}

	db2(p1, p2);
	db2(p3, p4);

	for (int i = p1 + 1; i < p2; i++) part1.pb(data[i]);
	for (int i = p2 + 1; i < p3; i++) part2.pb(data[i]);
	for (int i = p3 + 1; i < p4; i++) part3.pb(data[i]);
	for (int i = p4 + 1; i < (int)data.size(); i++) part4.pb(data[i]);
}

string trim(string s) {
	int l = 0;
	for (; l < (int)s.size() && isspace(s[l]); l++);
	int r = s.size() - 1;
	for (; r >= 0 && isspace(s[r]); l--);
	assert(l <= r);
	r++;
	return s.substr(l, r - l);
}

vector < string > split(string s, int (*f)(int)) {
	vector < string > res;
	for (int i = 0; i < (int)s.size(); ) {
		for (; i < (int)s.size() && f(s[i]); i++);
		if (i == (int)s.size()) break;
		//assert(isalpha(s[i]));
		int j = i;
		for (; i < (int)s.size() && (f(s[i]) == 0); i++);
		res.pb(s.substr(j, i - j));
	}
	return res;
}

vector < Rule > makeRule(string s) {
	int p = s.find(":");
	string name = trim(s.substr(0, p));
	s.erase(s.begin(), s.begin() + p + 1);
	vector < Rule > res;
	
	auto tmp = split(s, [](int ch) {return (int)(ch == '|');});
	for (auto h: tmp) {
		int l = h.find("{");
		int r = h.find("}");
		string code = h.substr(l, r - l + 1);
		auto ch = split(h.substr(0, l), isspace);
		res.pb(Rule(name, code, ch));
	}	
	return res;
}

vector < Rule > rules;
string start;


bool isTerm(string s) {
	bool flagU = 1;
	bool flagL = 1;
	for (auto ch: s)
		flagU &= (isupper(ch) > 0);
	for (auto ch: s)
		flagL &= (islower(ch) > 0);

	assert(flagL != flagU);
	return flagU;
}

set < string > createFirst(vector < string > ch) {
	set < string > res;
	bool flag = 1;
	for (auto s: ch) {
		if (isTerm(s))  {
			flag = 0;
			break;
		}
		flag &= first[s].count(EPS);
	}
	for (int i = 0; i < (int)ch.size(); i++) {
		if (isTerm(ch[i])) {
			res.insert(ch[i]);
			break;
		}
		else {
			for (auto s: first[ch[i]])
				res.insert(s);
			if (first[ch[i]].count(EPS) == 0)
				break;
		}
	}
	if (flag)
		res.insert(EPS);
	return res;
}

void genFirst() {
	bool changed = 1;
	while (changed) {
		changed = 0;
		for (auto rule: rules) {
			set < string > tmp = createFirst(rule.ch);
			for (auto s: tmp)
				if (first[rule.name].count(s) == 0) {
					changed = 1;
					first[rule.name].insert(s);
				}
		}	
	}	
}

void genFollow() {
	bool changed = 1;
	follow[start].insert(DOLLAR);
	while (changed) {
		changed = 0;
		for (auto rule: rules) {
			for (int i = 0; i < (int)rule.ch.size(); i++) {
				if (isTerm(rule.ch[i])) continue;
				vector < string > tmp;
				for (int j = i + 1; j < (int)rule.ch.size(); j++)
					tmp.pb(rule.ch[j]);
				auto g = createFirst(tmp);
				for (auto h: g)
					if (h != EPS) {
						if (follow[rule.ch[i]].count(h) == 0) {
							follow[rule.ch[i]].insert(h);
							changed = 1;
						}
					}
				if (g.count(EPS)) {
					for (auto s: follow[rule.name]) {
						if (follow[rule.ch[i]].count(s) == 0){
							changed = 1;
							follow[rule.ch[i]].insert(s);
						}
					}	
				}
			}	
		}
	}
}

void solve() {

	for (auto s: part1)
		cout << s << endl;
	cout << "//////////////////////////////////" << endl;


	string g;
	for (auto s: part3)
		g += s + "\n";

	for (;;) {
		size_t pos = g.find(":");
		if (pos == string::npos) break;

		int l = pos;
		for (; l > 0 && isspace(g[l - 1]); l--);
		for (; l > 0 && isalpha(g[l - 1]); l--);
		int r = pos;
		int bal = 0;
		for (; r < (int)g.size(); r++) {
			if (g[r] == '{') bal++;
			if (g[r] == '}') bal--;
			assert(bal >= 0);
			if (g[r] == ';' && bal == 0) {
				break;
			}
		}	
		string tmp = g.substr(l, r - l);
		g.erase(g.begin() + l, g.begin() + r);
		auto retVal = makeRule(tmp);
		rules.insert(rules.end(), retVal.begin(), retVal.end());
	}
	start = rules[0].name;


	for (auto x: rules) {
		db3(x.name, x.code, x.ch.size());
		//for (auto y: x.ch)
			//cerr << y << " ";
		//cerr << endl;
	}

	genFirst();
	
	for (auto x: first) {
		cerr << x.fr << " <-> ";
		for (auto y: x.sc)
			cerr << y << " ";
		cerr << endl;
	}


	cerr << endl;
	genFollow();

	for (auto x: follow) {
		cerr << x.fr << " <-> ";
		for (auto y: x.sc)
			cerr << y << " ";
		cerr << endl;
	}



	cout << "//////////////////////////////////" << endl;
	for (auto s: part4)
		cout << s << endl;
}

void stress() {

}

int main(){
#ifdef MY_DEBUG
    freopen("hw2.y", "r", stdin);
	freopen("answer.cpp", "w", stdout);
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


