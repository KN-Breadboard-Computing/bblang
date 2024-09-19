/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_KAROLJANIC_DOCUMENTS_BBLANG_SRC_PARSER_BUILD_BBLANG_PARSER_HPP_INCLUDED
# define YY_YY_HOME_KAROLJANIC_DOCUMENTS_BBLANG_SRC_PARSER_BUILD_BBLANG_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 37 "/home/karoljanic/Documents/bblang/src/parser/bblang.y"

    #include <iostream>
    
    #include "../../include/ast/program_node.hpp"
    #include "../../include/ast/arithmetic_expression_node.hpp"
    #include "../../include/ast/logic_expression_node.hpp"
    #include "../../include/ast/arithmetic_expr_lvl1_node.hpp"
    #include "../../include/ast/arithmetic_expr_lvl2_node.hpp"
    #include "../../include/ast/arithmetic_expr_lvl3_node.hpp"
    #include "../../include/ast/arithmetic_expr_lvl4_node.hpp"
    #include "../../include/ast/arithmetic_expr_lvl5_node.hpp"
    #include "../../include/ast/arithmetic_term_node.hpp"
    #include "../../include/ast/l_value_node.hpp"
    #include "../../include/ast/r_value_node.hpp"
    #include "../../include/ast/logic_expr_lvl1_node.hpp"
    #include "../../include/ast/logic_expr_lvl2_node.hpp"
    #include "../../include/ast/logic_term_node.hpp"
    #include "../../include/ast/arithmetic_expressions_comparison_node.hpp"
    #include "../../include/ast/arithmetic_constant_node.hpp"
    #include "../../include/ast/logic_constant_node.hpp"
    #include "../../include/ast/real_node.hpp"
    #include "../../include/ast/integer_node.hpp"
    #include "../../include/ast/identifier_node.hpp"

    typedef struct Token {
        std::string* stringValue;
        int intValue;
        double realValue;
    } Token;

#line 80 "/home/karoljanic/Documents/bblang/src/parser/build/../bblang_parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PLUS = 258,                    /* PLUS  */
    MINUS = 259,                   /* MINUS  */
    MULTIPLY = 260,                /* MULTIPLY  */
    DIVIDE = 261,                  /* DIVIDE  */
    MOD = 262,                     /* MOD  */
    SHIFT_LEFT = 263,              /* SHIFT_LEFT  */
    SHIFT_RIGHT = 264,             /* SHIFT_RIGHT  */
    BITWISE_AND = 265,             /* BITWISE_AND  */
    BITWISE_OR = 266,              /* BITWISE_OR  */
    BITWISE_XOR = 267,             /* BITWISE_XOR  */
    BITWISE_NOT = 268,             /* BITWISE_NOT  */
    AND = 269,                     /* AND  */
    OR = 270,                      /* OR  */
    XOR = 271,                     /* XOR  */
    NOT = 272,                     /* NOT  */
    LESS_THAN = 273,               /* LESS_THAN  */
    LESS_THAN_EQUAL = 274,         /* LESS_THAN_EQUAL  */
    GREATER_THAN = 275,            /* GREATER_THAN  */
    GREATER_THAN_EQUAL = 276,      /* GREATER_THAN_EQUAL  */
    EQUAL = 277,                   /* EQUAL  */
    NOT_EQUAL = 278,               /* NOT_EQUAL  */
    TRUE = 279,                    /* TRUE  */
    FALSE = 280,                   /* FALSE  */
    LITERAL_LEFT_PARENT = 281,     /* LITERAL_LEFT_PARENT  */
    LITERAL_RIGHT_PARENT = 282,    /* LITERAL_RIGHT_PARENT  */
    REAL = 283,                    /* REAL  */
    INTEGER = 284,                 /* INTEGER  */
    IDENTIFIER = 285               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "/home/karoljanic/Documents/bblang/src/parser/bblang.y"

    Token token;
    
	ast::ProgramNode* programNode;
	ast::ArithmeticExpressionNode* arithmeticExpressionNode;
	ast::LogicExpressionNode* logicExpressionNode;
	ast::ArithmeticExprLvl1Node* arithmeticExprLvl1Node;
	ast::ArithmeticExprLvl2Node* arithmeticExprLvl2Node;
	ast::ArithmeticExprLvl3Node* arithmeticExprLvl3Node;
	ast::ArithmeticExprLvl4Node* arithmeticExprLvl4Node;
	ast::ArithmeticExprLvl5Node* arithmeticExprLvl5Node;
	ast::ArithmeticTermNode* arithmeticTermNode;
	ast::LValueNode* lValueNode;
	ast::RValueNode* rValueNode;
	ast::LogicExprLvl1Node* logicExprLvl1Node;
	ast::LogicExprLvl2Node* logicExprLvl2Node;
	ast::LogicTermNode* logicTermNode;
	ast::ArithmeticExpressionsComparisonNode* arithmeticExpressionsComparisonNode;
	ast::ArithmeticConstantNode* arithmeticConstantNode;
	ast::LogicConstantNode* logicConstantNode;

#line 149 "/home/karoljanic/Documents/bblang/src/parser/build/../bblang_parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_KAROLJANIC_DOCUMENTS_BBLANG_SRC_PARSER_BUILD_BBLANG_PARSER_HPP_INCLUDED  */
