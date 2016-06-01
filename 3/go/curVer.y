
input: allCode { cout << (*($1.code)); };

allCode: func allCode { *($2.code) = *($1.code) + *($2.code); }
         |  NEW_LINE {data tmp; tmp.code = new string(); $$ = tmp; }
        ;

