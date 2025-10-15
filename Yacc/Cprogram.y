%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
%}

/* -------- Tokens -------- */
%token IF ELSE WHILE DO FOR
%token ID NUMBER
%token ASSIGN
%token ADD SUB MUL DIV
%token LT GT LE GE EQ NE
%token LPAREN RPAREN LBRACE RBRACE SEMI COMMA

%left ADD SUB
%left MUL DIV
%left LT GT LE GE EQ NE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

/* ================================
   Program Structure
   ================================ */

Program
    : StatementList
    ;

StatementList
    : Statement
    | StatementList Statement
    ;

Statement
    : AssignmentStatement
    | IfStatement
    | WhileStatement
    | DoWhileStatement
    | ForStatement
    | CompoundStatement
    | SEMI
    ;

/* ================================
   Control Flow Statements
   ================================ */

IfStatement
    : IF LPAREN Condition RPAREN Statement %prec LOWER_THAN_ELSE
    | IF LPAREN Condition RPAREN Statement ELSE Statement
    ;

WhileStatement
    : WHILE LPAREN Condition RPAREN Statement
    ;

DoWhileStatement
    : DO Statement WHILE LPAREN Condition RPAREN SEMI
    ;

ForStatement
    : FOR LPAREN OptionalExpression SEMI OptionalExpression SEMI OptionalExpression RPAREN Statement
    ;

/* ================================
   Blocks
   ================================ */

CompoundStatement
    : LBRACE StatementList RBRACE
    | LBRACE RBRACE
    ;

/* ================================
   Expressions
   ================================ */

AssignmentStatement
    : ID ASSIGN Expression SEMI
    ;

AssignmentExpression
    : ID ASSIGN Expression
    ;

OptionalExpression
    : /* empty */
    | AssignmentExpression
    | Expression
    | Condition
    ;

Condition
    : Expression RelOp Expression
    ;

RelOp
    : LT
    | GT
    | LE
    | GE
    | EQ
    | NE
    ;

Expression
    : Term
    | Expression ADD Term
    | Expression SUB Term
    ;

Term
    : Factor
    | Term MUL Factor
    | Term DIV Factor
    ;

Factor
    : ID
    | NUMBER
    | LPAREN Expression RPAREN
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    yyin = fp;   /* tell Lex to read from this file */
    if (yyparse() == 0)
        printf("Parsing finished successfully.\n");
    else
        printf("Parsing failed.\n");
    fclose(fp);
    return 0;
}

