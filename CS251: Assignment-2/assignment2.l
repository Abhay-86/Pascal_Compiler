alphabet [a-zA-Z]
digit [0-9]

%%
[ \t]       ;
[ \n]   { yylineno = yylineno + 1;}
"integer"  return INT;
"boolean" return BOOLEAN;
"char" return CHAR;
"real" return REAL;
"string" return TSTRING;
"for"     return FOR;
"while"   return WHILE;
"function" return FUNCTION;
"procedure" return PROCEDURE;
"continue" return CONTINUE;
"goto" return GOTO;
"case" return CASE;
"downto" return DOWNTO;
"repeat" return REPEAT;
"until" return UNTIL;
"to" return TO;
"do" return DO;
"of" return OF;
"nil" return NIL;
"then" return THEN;
"if"  return IF;
"else"    return ELSE;
"writeln"  return PRINTF;
"return" return RETURN;
"begin" return BEGN;
"const" return CONST1;
"end" return END;
"break" return BREAK;
"readln" return READLN;
"ReadKey" return READKEY;
"Write" return WRITE;
"and then" return ANDTHEN; 
"program " return PROGRAM;
"uses crt" return CRT;
"div" return DIV;
"var" return VAR1;
"not" return NOT;
"and" return AND;
"or" return OR;
"xor" return XOR;
"shr" return SHIFTR;
"shl" return SHIFTL;
"//"[^\n]* return COMMENT;
("{")(.*|\n)+?("}") return MCOMMENT;
{digit}+       return NUM;
{digit}"."{digit}* return FLOAT;
'([^\\']|\\.)*' return STRING;
{alphabet}({alphabet}|{digit})* return ID;
"<>" return LG;
"<=" return LE;
">=" return GE;
"==" return EQ;
"!=" return NE;
. return yytext[0];
%%
