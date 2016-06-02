/* Mini Calculator */
/* calc.y */

%{
#include "heading.h"
int yyerror(char *s);
int yylex(void);
%}

%union{
  data int_val;
}

%start	input 

%token	<int_val>	INTEGER_LITERAL;
%token  <int_val>   F_NAME
%token  <int_val>   SIGNS 

%type	<int_val>	func
%type	<int_val>	decl;
%type	<int_val>	args;
%type	<int_val>	body;
%type	<int_val>	caseCont;
%type	<int_val>	case;
%type	<int_val>	innerArg;
%type	<int_val>   conditions;
%type	<int_val>	allCode;
%type	<int_val>   formula;

%left	PLUS
%left	MULT
%left   COL2
%left   ARROW
%left   NEW_LINE
%left   OR
%left   EQ

/*%left   EQ*/

%%

input: allCode { 
    cout << "#include <bits/stdc++.h>\n\n";
    cout << "using namespace std;\n\n";
    cout << *($1.code);
};

allCode:  { $$.code = new string(); } 
        | NEW_LINE allCode{ $$ = $2; }
        | func allCode { *($1.code) = *($1.code) + "\n" + *($2.code); }
        ;

func: decl body {
    data tmp; 
    string g = *($2.code);
    g.erase(g.begin() + 1, g.begin() + 6);
    tmp.code = new string(*($1.code) + "{\n" + g + "\n}\n"); $$ = tmp; }
    ;

body: caseCont { $$ = $1; }
   

caseCont:  NEW_LINE     {data tmp; tmp.code = new string("");  $$ = tmp; }
         | case caseCont { 
            data tmp; 
            string h;
            for (int i = 0; i < (int)($1.cond->size()); i++) {
                h += "(" + (*($1.cond))[i] + ")";
                if (i + 1 < (int)($1.cond->size()))
                    h += " && ";
            }
            if (h.empty()) h = "true";
            tmp.code = new string("\telse if (" + h + ")\n\t\treturn " + *($1.code) + ";\n" + *($2.code)); 
            $$ = tmp; 
} ;

case: F_NAME innerArg conditions EQ formula NEW_LINE {
    data tmp;
    tmp.cond = $3.cond;
    map < string, string > q;
    vector < string > arr = *($2.args);
    reverse(arr.begin(), arr.end());
    
    for (int i = 0; i < (int)arr.size(); i++) {
        string arg = arr[i];
        assert(arg.size() >= 1);
        string var = string(1, 'a' + i);
        if (isalpha(arg[0])) {
            /*cerr << "arg var: " << arg << " " << var << endl;*/
            q[arg] = var; 
        }
        else {
            tmp.cond->push_back(var + " = " + arg); 
        }
    }
    string text = *($5.code); 

    for (auto x: q) {
        int pos = 0;
        for (;;) {
            size_t g = text.find(x.first, pos);
            if (g == string::npos) {
                break;         
            }
            text.replace(g, x.first.size(), x.second);
            pos = g + x.second.size();
        }
    }
    for (int i = 0; i < (int)tmp.cond->size(); i++) {
        string text = (*(tmp.cond))[i];
        for (auto x: q) {
            int pos = 0;
            for (;;) {
                size_t g = text.find(x.first, pos);
                if (g == string::npos) {
                    break;         
                }
                text.replace(g, x.first.size(), x.second);
                pos = g + x.second.size();
            }
        }     
        (*(tmp.cond))[i] = text;
    }


    tmp.code = new string(text); 
    $$ = tmp;  

};

innerArg:  /* empty */ {data tmp; tmp.args = new vector < string >(); $$ = tmp; }
        | F_NAME innerArg { 
            $2.args->push_back(*($1.code));
            $$ = $2;
};


conditions: /* empty */ { data tmp; tmp.cond = new vector < string > (); $$ = tmp; }
        | OR formula conditions {
                ($3.cond)->push_back(*($2.code));
                $$ = $3;
            } 
        ;

formula: /* empty */ { data tmp; tmp.code = new string(); $$ = tmp; }
        | F_NAME formula { *($2.code) = *($1.code) + *($2.code); $$ = $2; }
        | SIGNS formula { *($2.code) = *($1.code) + *($2.code); $$ = $2; }
        ;

decl: F_NAME COL2 F_NAME args { 
    data tmp; 
    string ar;    
    for (int i = 0; i < $4.cntArgs; i++) {
        ar += "int ";
        ar += (char)('a' + i);
        if (i + 1 < $4.cntArgs)
            ar += ", ";
    }
    tmp.code = new string("int " + (*($1.code)) + " (" + ar + ")" );
    $$ = tmp;
};

args: NEW_LINE { data tmp; tmp.cntArgs= 0; $$ = tmp;}
    | ARROW F_NAME args { data tmp; tmp.cntArgs = $3.cntArgs + 1; $$ = tmp; }
    ;

%%

int yylex() {
	for (; cur < (int)s.size() && (s[cur] == ' ' || s[cur] == '\t'); cur++);
	


}


ttt         [0-9a-zA-Z]
word        {ttt}+

/*alf [\*\-\+\/\(\)\<\>\"\%\,\\]*/
expr        {alf}+



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


}


int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}


int main() {
	freopen("in", "r", stdin);
	getline(cin, s);
	yyparse();

}




