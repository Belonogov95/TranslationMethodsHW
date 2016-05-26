/* main.cc */

#include "heading.h"
#include <cstdlib>

// prototype of bison-generated parser function
int yyparse();

int main() {
  yyparse();

  return 0;
}

