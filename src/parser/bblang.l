%{
#define NO_YY_WRAP

#include "bblang_parser.hpp"

#include <iostream>
#include <string>

size_t linesCounter = 1;
void eatComment();

%}
%%

"//".*  { linesCounter++; }        
"/*"  { eatComment(); }

"~"  { return BITWISE_NOT; }
"||"  { return OR; }
"|"  { return BITWISE_OR; }
"true"  { return TRUE; }
"false"  { return FALSE; }
"^^"  { return XOR; }
"^"  { return BITWISE_XOR; }
">>"  { return SHIFT_RIGHT; }
">="  { return GREATER_THAN_EQUAL; }
">"  { return GREATER_THAN; }
"=="  { return EQUAL; }
"<="  { return LESS_THAN_EQUAL; }
"<<"  { return SHIFT_LEFT; }
"<"  { return LESS_THAN; }
"/"  { return DIVIDE; }
"-"  { return MINUS; }
"+"  { return PLUS; }
"*"  { return MULTIPLY; }
")"  { return LITERAL_RIGHT_PARENT; }
"("  { return LITERAL_LEFT_PARENT; }
"&&"  { return AND; }
"&"  { return BITWISE_AND; }
"%"  { return MOD; }
"!="  { return NOT_EQUAL; }
"!"  { return NOT; }

[0-9]+\.[0-9]+  { yylval.token.realValue = strtod(yytext, nullptr); return REAL; }
[0-9]+  { yylval.token.intValue = strtoull(yytext, nullptr, 10); return INTEGER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.token.stringValue = new std::string(yytext); return IDENTIFIER; }


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
