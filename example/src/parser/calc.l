%{
#define NO_YY_WRAP

#include "calc_parser.hpp"

#include <iostream>
#include <string>

size_t linesCounter = 1;
void eatComment();

%}
%%

"//".*  { linesCounter++; }        
"/*"  { eatComment(); }

"result is"  { return LITERAL_RESULT_IS; }
"-"  { return TOKEN_MINUS; }
"+"  { return TOKEN_PLUS; }
"*"  { return TOKEN_MULTIPLY; }

[0-9]+  { yylval.token.numericValue = strtoull(yytext, nullptr, 10); return INTEGER; }


[ \t\f]  { }

"\n"  { linesCounter++; }

.  { std::cerr << "Error:  illegal character " << yytext[0] << " at line " << linesCounter << std::endl; }

%%
void eatComment() {
  int c;
  while ((c = yyinput()) != 0) {
    if (c == '\n') {
      ++linesCounter;
    }
    else if (c == '*') {
      if ((c = yyinput()) == '/') {
        break;
      }
      unput(c);
    }
  }
}

int yywrap(void) {
    return 1;
}
