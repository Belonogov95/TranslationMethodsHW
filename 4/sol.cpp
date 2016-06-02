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
const string pref = "vv_";
const string var = "var_";

struct Rule {
	string name;
	string code;
	vector < pair < int, string > > allch;
	vector < string > ch;
	Rule(string name, string code, vector < pair < int, string > > allch): name(name), code(code), allch(allch) {
  		for (auto x: allch) 
			if (x.fr == 1)
				ch.pb(x.sc);
	}
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
	for (; r >= 0 && isspace(s[r]); r--);
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

vector < pair < int, string > > splitRule(string s) {
	size_t l = s.find("{");
	size_t r = s.find("}");
	//db2(l, r);
	if (l == string::npos) {
		auto tmp = split(s, isspace);	
		vector < pair < int, string > > res;
		for (auto x: tmp)
			res.pb(mp(1, x));
		return res;
	}
	assert(l < r);
	string code = trim(s.substr(l + 1, r - l - 1));
	auto r1 = splitRule(s.substr(0, l));
	auto r2 = splitRule(s.substr(r + 1, (int)s.size() - (r + 1)));
	r1.pb(mp(2, code));
	r1.insert(r1.end(), r2.begin(), r2.end());
	return r1;

}

vector < Rule > makeRule(string s) {
	int p = s.find(":");
	string name = trim(s.substr(0, p));
	s.erase(s.begin(), s.begin() + p + 1);
	vector < Rule > res;
	
	auto tmp = split(s, [](int ch) {return (int)(ch == '|');});
	for (auto h: tmp) {
		//int l = h.find("{");
		//int r = h.find("}");
		//string code = h.substr(l + 1, r - l - 1);
		//db("before");
		//code = trim(code);
		//db(code);
		//auto ch = split(h.substr(0, l), isspace);
		auto g = splitRule(h);
		//for (auto x: g)
		//db2(x.fr, x.sc);

		assert(g.back().fr == 2);
		string code = g.back().sc;
		g.pop_back();
		res.pb(Rule(name, code, g));
	}	
	return res;
}

vector < Rule > rules;
string start;


bool isTerm(string s) { bool flagU = 1;
	bool flagL = 1;
	for (auto ch: s)
		flagU &= (isupper(ch) > 0);
	for (auto ch: s)
		flagL &= (islower(ch) > 0);

	//db(s);
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


string myReplace(string s, string a, string b) {
	size_t pos = s.find(a);
	if (pos != string::npos) {
		s = s.replace(pos, a.size(), b);	
	}
	return s;
}

string myReplaceMul(string s, string a, string b) {
	while (true) {
		size_t pos = s.find(a);
		if (pos != string::npos) {
			s = s.replace(pos, a.size(), b);	
		}
		else
			break;
	}
	return s;
}

bool startsWith(string s, string t) {
	if (t.size() > s.size()) return 0;
	return s.substr(0, t.size()) == t;
}

void solve() {

	for (auto s: part1)
		cout << s << endl;
	cout << "//////////////////////////////////" << endl;

	string tk = "%token";
	//db2(tk, tk.size());
	//return ;
	int shiftId = 1900;
	string inher_data_type;
	const string inh_name = "parent";
	const string inh = "inh_";
	for (auto s: part2) {
		if (startsWith(s, "%token")) {
			//db(s);
			auto g = split(s, isspace);
			//db(g[0]);
			//db(g[1]);
			assert(g.size() == 2);
			cout << "const int " << g[1] << " = " << shiftId << ";\n";
			shiftId++;
		}
		if (startsWith(s, "DATA_TYPE")) {
			auto g = split(s, isspace);
			inher_data_type = g[1];
		}
	}
	cout << "const int DOLLAR = 0;\n";

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
	set < string > notTerm;
	set < string > term;

	for (auto rule: rules) {
		notTerm.insert(rule.name);
		assert(!isTerm(rule.name));
		for (auto s: rule.ch)
			if (isTerm(s))
				term.insert(s);
			else
				notTerm.insert(s);
	}
	term.insert(DOLLAR);


	//cerr << "XXXXXXXXXXXXXXXX\n";
	//for (auto x: rules) {
		//db3(x.name, x.code, x.ch.size());
		//for (auto y: x.allch)
			//cerr << "[" << y.fr << ", " << y.sc << "]" << " ";
		//cerr << endl;
		////for (auto y: x.ch)
			////cerr << "[" << y << "]" << " ";
		////cerr << endl;
	//}
	//cerr << "XXXXXXXXXXXXXXXX\n";

	genFirst();
	
	//for (auto x: first) {
		//cerr << x.fr << " <-> ";
		//for (auto y: x.sc)
			//cerr << y << " ";
		//cerr << endl;
	//}


	//cerr << endl;
	genFollow();

	//for (auto x: follow) {
		//cerr << x.fr << " <-> ";
		//for (auto y: x.sc)
			//cerr << y << " ";
		//cerr << endl;
	//}


	cout << endl;
	cout << "void shiftCur() {\n";
	cout << "\tcurToken = yylex();\n";
	cout << "\tcurValue = yylval;\n";
	cout << "}\n\n";

	for (auto x: notTerm)
		cout << "int " << pref + x << "(" + inher_data_type + " " + inh_name + ");\n\n";


	for (auto nterm: notTerm) {
		cout << "int " << pref + nterm << "(" + inher_data_type + " " + inh_name + ") {\n";
		for (auto y: term) {
			vector < int > id;	
			for (int i = 0; i < (int)rules.size(); i++) {
				auto rule = rules[i];
				if (rule.name != nterm) continue;
				auto tmp = createFirst(rule.ch);
				if (tmp.count(EPS))
					tmp.insert(follow[nterm].begin(), follow[nterm].end());
				if (tmp.count(y)) {
					id.pb(i);
				}
			}

			if (id.empty()) {
				cout << "\tassert(curToken != " << y << ");\n";
			}
			if ((int)id.size() == 1) {
				cout << "\tif (curToken == " << y << ") {\n";
				int iter = 0;
				string tmp = rules[id[0]].code;
				int pos = 0;
				for (auto t: rules[id[0]].allch) {
					if (t.fr == 1 && !isTerm(t.sc)) {
						cout << "\t\t" + inher_data_type + " " + pref + var + inh + to_string(pos + 1) + ";\n";
					}
					pos++;
				}

				for (auto t: rules[id[0]].allch) {
					if (t.fr == 1) {
						if (isTerm(t.sc)) {
							cout << "\t\tassert(curToken == " << t.sc << ");\n";
							if (tmp.find("$" + to_string(iter + 1)) != string::npos)
								cout << "\t\tint " + pref + var + to_string(iter + 1) << " = curValue;\n";
							cout << "\t\tshiftCur();\n";
						}
						else {
							cout << "\t\tint " + pref + var + to_string(iter + 1) << " = "; 
							cout << pref + t.sc;
							cout << "(" + pref + var + inh;
							cout << to_string(iter + 1) + ");\n";
						}
					}
					else {
						string tmp = t.sc;
						tmp = myReplaceMul(tmp, "$$", inh_name);
						for (int i = 0; i < (int)rules[id[0]].allch.size(); i++) {
							tmp = myReplaceMul(tmp, "$" + to_string(i + 1), pref + var + inh + to_string(i + 1));
						}		
						cout << "\t\t" + tmp << "\n";
					}
					iter++;
				}
				for (int i = 0; i < (int)rules[id[0]].allch.size(); i++) {
					tmp = myReplaceMul(tmp, "$" + to_string(i + 1), pref + var + to_string(i + 1));
				}
				const string ret = "ret";
				tmp = myReplace(tmp, "$$", pref + ret);


				cout << "\t\tint " << pref + ret << " = 0;\n";
				cout << "\t\t" << tmp << endl; 	
				cout << "\t\treturn " << pref + ret + ";" << endl;

				cout << "\t}\n";
			}
			//db3(nterm, y, id.size());
			assert(id.size() <= 1);

		}	

		cout << "\tassert(false);\n";

		cout << "}\n\n";
	}

	cout << "int yyparse() {\n";
	cout << "\tcurToken = yylex();\n";
	cout << "\tcurValue = yylval;\n";
	cout << "\t" + pref + start + "(" + inher_data_type + "());\n";
	cout << "\treturn 0;\n";
	cout << "}\n\n";
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


