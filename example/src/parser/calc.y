%{
    #include <iostream>
    #include <cstdlib>
    #include <cstdio>

    #include "../../include/ast/program_node.hpp"
    #include "../../include/ast/expression_side_node.hpp"
    #include "../../include/ast/term_node.hpp"
    #include "../../include/ast/factor_node.hpp"
    #include "../../include/ast/integer_node.hpp"

    static void yyerror(const char *msg);
    static int yyparse(void);

    int yylex(void);
    
    extern FILE* yyin;
    extern size_t linesCounter;
    std::unique_ptr<ast::ProgramNode> result = nullptr;
%}

%code requires {
    #include <iostream>
    
    #include "../../include/ast/program_node.hpp"
    #include "../../include/ast/expression_side_node.hpp"
    #include "../../include/ast/term_node.hpp"
    #include "../../include/ast/factor_node.hpp"
    #include "../../include/ast/integer_node.hpp"

    typedef struct Token {
        std::string* stringValue;
        int numericValue;
    } Token;
}

%union
{
    Token token;
    
	ast::ProgramNode* programNode;
	ast::ExpressionSideNode* expressionSideNode;
	ast::TermNode* termNode;
	ast::FactorNode* factorNode;
}


%token TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY
%token LITERAL_RESULT_IS
%token INTEGER

%type <token> TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY
%type <token> LITERAL_RESULT_IS
%type <token> INTEGER

%type <programNode> program
%type <expressionSideNode> expression_side
%type <termNode> term
%type <factorNode> factor

%%

program:
	LITERAL_RESULT_IS expression_side {
		$$ = new ast::ProgramNode($2);
		result = std::unique_ptr<ast::ProgramNode>($$);
	}
|
	%empty {
		$$ = new ast::ProgramNode();
		result = std::unique_ptr<ast::ProgramNode>($$);
	}
;

expression_side:
	expression_side TOKEN_PLUS term {
		$$ = new ast::ExpressionSideNode($1, ast::ExpressionSideNode::ExpressionSideNodeOperation::PLUS, $3);
	}
|
	expression_side TOKEN_MINUS term {
		$$ = new ast::ExpressionSideNode($1, ast::ExpressionSideNode::ExpressionSideNodeOperation::MINUS, $3);
	}
|
	term {
		$$ = new ast::ExpressionSideNode($1);
	}
;

term:
	term TOKEN_MULTIPLY factor {
		$$ = new ast::TermNode($1, ast::TermNode::TermNodeOperation::MULTIPLY, $3);
	}
|
	factor {
		$$ = new ast::TermNode($1);
	}
;

factor:
	TOKEN_MINUS factor {
		$$ = new ast::FactorNode(ast::FactorNode::FactorNodeOperation::MINUS, $2);
	}
|
	INTEGER {
		$$ = new ast::FactorNode(new ast::IntegerNode($1.numericValue));
	}
;


%%

void yyerror(const char *s) {
    std::cerr << "Error: " << s << std::endl;
}

std::unique_ptr<ast::ProgramNode> parse(const char* file_path) {
    yyin = fopen(file_path, "r");
    if (!yyin) {
        std::cerr << "Cannot open file: " << file_path << std::endl;
        return nullptr;
    }

    yyparse();
    fclose(yyin);
    
    return std::move(result);
}
