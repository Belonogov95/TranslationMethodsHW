/* heading.h */

#define YY_NO_UNPUT
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

using namespace std;



struct data {
    string * code;
    vector < string > * args;
    vector < string > * cond;
    int cntArgs;
};
