%{
    #include <iostream>
    #include <cstdlib>
    #include <cstdio>

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
}

%union
{
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
}


%token PLUS MINUS MULTIPLY DIVIDE MOD SHIFT_LEFT SHIFT_RIGHT BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_NOT AND OR XOR NOT LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL EQUAL NOT_EQUAL TRUE FALSE
%token LITERAL_LEFT_PARENT LITERAL_RIGHT_PARENT
%token REAL INTEGER IDENTIFIER

%type <token> PLUS MINUS MULTIPLY DIVIDE MOD SHIFT_LEFT SHIFT_RIGHT BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_NOT AND OR XOR NOT LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL EQUAL NOT_EQUAL TRUE FALSE
%type <token> LITERAL_LEFT_PARENT LITERAL_RIGHT_PARENT
%type <token> REAL INTEGER IDENTIFIER

%type <programNode> program
%type <arithmeticExpressionNode> arithmetic_expression
%type <logicExpressionNode> logic_expression
%type <arithmeticExprLvl1Node> arithmetic_expr_lvl_1
%type <arithmeticExprLvl2Node> arithmetic_expr_lvl_2
%type <arithmeticExprLvl3Node> arithmetic_expr_lvl_3
%type <arithmeticExprLvl4Node> arithmetic_expr_lvl_4
%type <arithmeticExprLvl5Node> arithmetic_expr_lvl_5
%type <arithmeticTermNode> arithmetic_term
%type <lValueNode> l_value
%type <rValueNode> r_value
%type <logicExprLvl1Node> logic_expr_lvl_1
%type <logicExprLvl2Node> logic_expr_lvl_2
%type <logicTermNode> logic_term
%type <arithmeticExpressionsComparisonNode> arithmetic_expressions_comparison
%type <arithmeticConstantNode> arithmetic_constant
%type <logicConstantNode> logic_constant

%%

program:
	arithmetic_expression {
		$$ = new ast::ProgramNode(linesCounter, $1);
		result = std::unique_ptr<ast::ProgramNode>($$);
	}
|
	logic_expression {
		$$ = new ast::ProgramNode(linesCounter, $1);
		result = std::unique_ptr<ast::ProgramNode>($$);
	}
;

arithmetic_expression:
	arithmetic_expression BITWISE_OR arithmetic_expr_lvl_1 {
		$$ = new ast::ArithmeticExpressionNode(linesCounter, $1, ast::ArithmeticExpressionNode::ArithmeticExpressionNodeOperation::BITWISE_OR, $3);
	}
|
	arithmetic_expr_lvl_1 {
		$$ = new ast::ArithmeticExpressionNode(linesCounter, $1);
	}
;

arithmetic_expr_lvl_1:
	arithmetic_expr_lvl_1 BITWISE_XOR arithmetic_expr_lvl_2 {
		$$ = new ast::ArithmeticExprLvl1Node(linesCounter, $1, ast::ArithmeticExprLvl1Node::ArithmeticExprLvl1NodeOperation::BITWISE_XOR, $3);
	}
|
	arithmetic_expr_lvl_2 {
		$$ = new ast::ArithmeticExprLvl1Node(linesCounter, $1);
	}
;

arithmetic_expr_lvl_2:
	arithmetic_expr_lvl_2 BITWISE_AND arithmetic_expr_lvl_3 {
		$$ = new ast::ArithmeticExprLvl2Node(linesCounter, $1, ast::ArithmeticExprLvl2Node::ArithmeticExprLvl2NodeOperation::BITWISE_AND, $3);
	}
|
	arithmetic_expr_lvl_3 {
		$$ = new ast::ArithmeticExprLvl2Node(linesCounter, $1);
	}
;

arithmetic_expr_lvl_3:
	arithmetic_expr_lvl_3 SHIFT_LEFT arithmetic_expr_lvl_4 {
		$$ = new ast::ArithmeticExprLvl3Node(linesCounter, $1, ast::ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::SHIFT_LEFT, $3);
	}
|
	arithmetic_expr_lvl_3 SHIFT_RIGHT arithmetic_expr_lvl_4 {
		$$ = new ast::ArithmeticExprLvl3Node(linesCounter, $1, ast::ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::SHIFT_RIGHT, $3);
	}
|
	arithmetic_expr_lvl_4 {
		$$ = new ast::ArithmeticExprLvl3Node(linesCounter, $1);
	}
;

arithmetic_expr_lvl_4:
	arithmetic_expr_lvl_4 PLUS arithmetic_expr_lvl_5 {
		$$ = new ast::ArithmeticExprLvl4Node(linesCounter, $1, ast::ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::PLUS, $3);
	}
|
	arithmetic_expr_lvl_4 MINUS arithmetic_expr_lvl_5 {
		$$ = new ast::ArithmeticExprLvl4Node(linesCounter, $1, ast::ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::MINUS, $3);
	}
|
	arithmetic_expr_lvl_5 {
		$$ = new ast::ArithmeticExprLvl4Node(linesCounter, $1);
	}
;

arithmetic_expr_lvl_5:
	arithmetic_expr_lvl_5 MULTIPLY arithmetic_term {
		$$ = new ast::ArithmeticExprLvl5Node(linesCounter, $1, ast::ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::MULTIPLY, $3);
	}
|
	arithmetic_expr_lvl_5 DIVIDE arithmetic_term {
		$$ = new ast::ArithmeticExprLvl5Node(linesCounter, $1, ast::ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::DIVIDE, $3);
	}
|
	arithmetic_expr_lvl_5 MOD arithmetic_term {
		$$ = new ast::ArithmeticExprLvl5Node(linesCounter, $1, ast::ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::MOD, $3);
	}
|
	arithmetic_term {
		$$ = new ast::ArithmeticExprLvl5Node(linesCounter, $1);
	}
;

arithmetic_term:
	MINUS arithmetic_term {
		$$ = new ast::ArithmeticTermNode(linesCounter, ast::ArithmeticTermNode::ArithmeticTermNodeOperation::MINUS, $2);
	}
|
	BITWISE_NOT arithmetic_term {
		$$ = new ast::ArithmeticTermNode(linesCounter, ast::ArithmeticTermNode::ArithmeticTermNodeOperation::BITWISE_NOT, $2);
	}
|
	LITERAL_LEFT_PARENT arithmetic_expression LITERAL_RIGHT_PARENT {
		$$ = new ast::ArithmeticTermNode(linesCounter, $2);
	}
|
	l_value {
		$$ = new ast::ArithmeticTermNode(linesCounter, $1);
	}
|
	r_value {
		$$ = new ast::ArithmeticTermNode(linesCounter, $1);
	}
;

logic_expression:
	logic_expression OR logic_expr_lvl_1 {
		$$ = new ast::LogicExpressionNode(linesCounter, $1, ast::LogicExpressionNode::LogicExpressionNodeOperation::OR, $3);
	}
|
	logic_expr_lvl_1 {
		$$ = new ast::LogicExpressionNode(linesCounter, $1);
	}
;

logic_expr_lvl_1:
	logic_expr_lvl_1 XOR logic_expr_lvl_2 {
		$$ = new ast::LogicExprLvl1Node(linesCounter, $1, ast::LogicExprLvl1Node::LogicExprLvl1NodeOperation::XOR, $3);
	}
|
	logic_expr_lvl_2 {
		$$ = new ast::LogicExprLvl1Node(linesCounter, $1);
	}
;

logic_expr_lvl_2:
	logic_term AND logic_term {
		$$ = new ast::LogicExprLvl2Node(linesCounter, $1, ast::LogicExprLvl2Node::LogicExprLvl2NodeOperation::AND, $3);
	}
|
	logic_term {
		$$ = new ast::LogicExprLvl2Node(linesCounter, $1);
	}
;

logic_term:
	NOT logic_term {
		$$ = new ast::LogicTermNode(linesCounter, ast::LogicTermNode::LogicTermNodeOperation::NOT, $2);
	}
|
	LITERAL_LEFT_PARENT logic_expression LITERAL_RIGHT_PARENT {
		$$ = new ast::LogicTermNode(linesCounter, $2);
	}
|
	arithmetic_expressions_comparison {
		$$ = new ast::LogicTermNode(linesCounter, $1);
	}
|
	l_value {
		$$ = new ast::LogicTermNode(linesCounter, $1);
	}
|
	r_value {
		$$ = new ast::LogicTermNode(linesCounter, $1);
	}
;

arithmetic_expressions_comparison:
	arithmetic_expression LESS_THAN arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::LESS_THAN, $3);
	}
|
	arithmetic_expression LESS_THAN_EQUAL arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::LESS_THAN_EQUAL, $3);
	}
|
	arithmetic_expression GREATER_THAN arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::GREATER_THAN, $3);
	}
|
	arithmetic_expression GREATER_THAN_EQUAL arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::GREATER_THAN_EQUAL, $3);
	}
|
	arithmetic_expression EQUAL arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::EQUAL, $3);
	}
|
	arithmetic_expression NOT_EQUAL arithmetic_expression {
		$$ = new ast::ArithmeticExpressionsComparisonNode(linesCounter, $1, ast::ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::NOT_EQUAL, $3);
	}
;

l_value:
	IDENTIFIER {
		$$ = new ast::LValueNode(linesCounter, new ast::IdentifierNode(*$1.stringValue));
	}
;

r_value:
	arithmetic_constant {
		$$ = new ast::RValueNode(linesCounter, $1);
	}
|
	logic_constant {
		$$ = new ast::RValueNode(linesCounter, $1);
	}
;

arithmetic_constant:
	INTEGER {
		$$ = new ast::ArithmeticConstantNode(linesCounter, new ast::IntegerNode($1.intValue));
	}
|
	REAL {
		$$ = new ast::ArithmeticConstantNode(linesCounter, new ast::RealNode($1.realValue));
	}
;

logic_constant:
	TRUE {
		$$ = new ast::LogicConstantNode(linesCounter, ast::LogicConstantNode::LogicConstantNodeOperation::TRUE);
	}
|
	FALSE {
		$$ = new ast::LogicConstantNode(linesCounter, ast::LogicConstantNode::LogicConstantNodeOperation::FALSE);
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
