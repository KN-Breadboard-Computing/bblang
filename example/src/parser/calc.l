%{
#define NO_YY_WRAP
#define YY_NO_UNPUT
#define YY_NO_INPUT

#include "calc_parser.hpp"

#include <iostream>
#include <string>

size_t linesCounter = 1;
%}

%%

"//".*  { linesCounter++; }        


"result is"  { return LITERAL_RESULT_IS; }
"-"  { return TOKEN_MINUS; }
"+"  { return TOKEN_PLUS; }
"*"  { return TOKEN_MULTIPLY; }

[0-9]+  { yylval.token.numericValue = strtoull(yytext, nullptr, 10); return INTEGER; }


[ \t\f]  { }

"\n"  { linesCounter++; }

.  { std::cerr << "Error:  illegal character " << yytext[0] << " at line " << linesCounter << std::endl; }

%%

int yywrap(void) {
    return 1;
}
