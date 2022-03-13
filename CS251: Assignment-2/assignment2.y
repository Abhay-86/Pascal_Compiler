%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *fp;
%}

%token INT BOOLEAN CHAR REAL TSTRING
%token FOR WHILE GOTO CONTINUE CASE DOWNTO BREAK
%token IF ELSE TO DO THEN ANDTHEN REPEAT UNTIL OF
%token STRING COMMENT MCOMMENT
%token NUM ID FLOAT NIL
%token PROGRAM CRT FUNCTION PROCEDURE
%token VAR1 CONST1
%token BEGN END RETURN
%token READLN READKEY WRITE PRINTF
%token NOT XOR PERCENT SHIFTL SHIFTR AND OR LE GE EQ NE LG DIV
%%

start: PreProDirective start	 
    | Declaration start
    | Declaration
    | PreProDirective
    | block  
    | StmtList start
    | StmtList
    | CommentStmt
    ;

block: BEGN start END '.'
     | BEGN start END ';'
     ;

Declaration: Assignment ';'
    | VAR
    | CONST
    ;

VAR : VAR1 	
    | VAR '\n' Assignment ';'
    ;

CONST : CONST1
    | CONST '\n' Assignment ';'
    ;

PreProDirective: PreProDirective CRT ';'
		| PROGRAM ID ';' 
		| PROGRAM ID Assignment';'
		| CRT ';' 
		;
		
StmtList: stmt StmtList
	| stmt
	;

stmt: 	ForStmt
	| RepeatUntilStmt
	| WhileStmt
	| CaseStmt
	| IfStmt
	| IfElseStmt
	| Declaration
	| IOFunc
	| ControlFlow
	| CommentStmt
	| FuncStmt
	| block
	;

FuncStmt: FUNCTION ID Declaration StmtList
	;
FuncInvo : ID Assignment
	;

CommentStmt: COMMENT StmtList
	    | COMMENT
	    | MCOMMENT StmtList
	    | MCOMMENT
	    ;

For_Cond: TO
	| DOWNTO
	;
	
ForStmt: FOR Assignment For_Cond Z DO BEGN StmtList END ';'
	| FOR Assignment For_Cond Z DO BEGN END ';'
	;

RepeatUntilStmt: REPEAT StmtList UNTIL Assignment ';'
		| REPEAT UNTIL Assignment ';'
		; 
 
CaseStmt: CASE Assignment OF CaseStmtList END ';'
	 | CASE Assignment OF END ';'
	 ;

CaseStmtList: Z ':' stmt CaseStmtList
	     | Z ':' stmt 
	     ;
WhileStmt: WHILE Assignment DO BEGN StmtList END ';'
	| WHILE Assignment DO BEGN END ';'
	; 

IfStmt: IF Assignment THEN StmtList
	;

IfElseStmt: ELSE StmtList
	  | ELSE IF Assignment StmtList 
	  ;
	
ControlFlow: CONTINUE ';'
	    | BREAK ';'
	    | GOTO ';'
	    | RETURN Assignment';'
	    ;
 
/* Assignment block */
Assignment: Assignment OP Assignment
    	  | '(' Assignment ')'
    	  | UNARY_OP Assignment
    	  | Z
    	  | Type
    	  | READKEY
    	  | FuncInvo
    	  ;

UNARY_OP: '&'
  | '*'
  | '!'
  | '~'
  | '-'
  | '+'
  ;
  
OP: '='
  | ':'
  | '+'
  | '-'
  | '*'
  | '/'
  | ','
  | '^'
  | '<'
  | '>'
  | OR
  | AND
  | EQ
  | LE
  | LG
  | GE
  | NE
  | OP OP
  ;
   
/* Type Identifier block */
Type:   INT
    | BOOLEAN
    | CHAR
    | REAL
    | TSTRING
    ;
   
/* IO Funct */
IOFunc : PrintFunc | ReadFunc 
	;
	
PrintFunc : PRINTF '('Assignment')' ';'
	  | WRITE '('Assignment')' ';'
   	  ;
ReadFunc : READLN '('Assignment')' ';'
   	  ;

Z : NUM
  | ID
  | STRING 
  | FLOAT
  ;

%%
#include"lex.yy.c"
#include<ctype.h>
int count=0;

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");

   if(!yyparse())
        printf("\nValid Program\n");
    else
        printf("\nParsing failed, Invalid Program\n");

    fclose(yyin);
    return 0;
}

yyerror(char *s) 
{
	printf("%d : %s %s\n", yylineno, s, yytext );
}
