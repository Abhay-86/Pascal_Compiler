/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "hash.h"
#include "reg_stack.h"
#include "gencode.h"
#include "compiler.tab.h"
#include "externs.h"


int yydebug = 1;

int yywrap() { return 1; }

void yyerror(const char *str) { fprintf(stderr, "\nERROR, LINE %d: %s\n", yylineno, str); }

int main(int argc, char** argv) 
{ 
	
	if(argc != 2)
	{
		fprintf(stderr, "Incorrect number of arguments given.\n");
		exit(0);
	}
	
	
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
	{
		fprintf(stderr, "Invalid input file name given.\n");
		exit(0);
	}

	
	char* outfile_name = (char*)malloc(strlen(argv[1]));
	strcpy(outfile_name, (char*)argv[1]);
	outfile_name[strlen(outfile_name)-1] = 's';
	outfile = fopen(outfile_name, "w");

	
	head_table = (table_t*)malloc(sizeof(table_t));
	for(int i = 0; i < TABLE_SIZE; i++)
		head_table->hash_table[i] = NULL;
	head_table->prev = head_table;
	head_table->next = head_table;
	head_table->id = -1;

	
	rstack = (stack_t*)malloc(sizeof(stack_t));
	for(int i = 0; i < MAX_REGS; i++)
		rstack->reg[i] = i;
	for(int i = 0; i < MAX_TEMPS; i++)
		rstack->temp[i] = -i; 
	rstack->top_idx = MAX_REGS-1;

	
	fprintf(stderr, "Converting into Token\n____________\n\n");
	yyin = infile;
	file_header(argv[1]);
	do { yyparse(); }
	while (!feof(yyin));
	file_footer();
	
	fclose(infile);
	fclose(outfile);
}

#line 142 "compiler.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_COMPILER_TAB_H_INCLUDED
# define YY_YY_COMPILER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INUM = 258,
    RNUM = 259,
    ADDOP = 260,
    MULOP = 261,
    RELOP = 262,
    ASSOP = 263,
    NOT = 264,
    ARRAYOP = 265,
    PARENOP = 266,
    LISTOP = 267,
    IDENT = 268,
    STRING = 269,
    PROGRAM = 270,
    FUNCTION = 271,
    PROCEDURE = 272,
    VAR = 273,
    ARRAY = 274,
    OF = 275,
    DOTDOT = 276,
    INTEGER = 277,
    REAL = 278,
    BOOL = 279,
    IF = 280,
    WHILE = 281,
    FOR = 282,
    REPEAT = 283,
    BEG = 284,
    END = 285,
    THEN = 286,
    THAN = 287,
    ELSE = 288,
    DO = 289,
    DOWNTO = 290,
    TO = 291,
    UNTIL = 292,
    EMPTY = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 77 "compiler.y"

	int ival;
	float fval;
	char *opval;
	char *sval;

	tree_t *tval;

#line 242 "compiler.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

#define YYUNDEFTOK  2
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    43,     2,    42,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   173,   173,   176,   176,   176,   176,   190,   197,   206,
     214,   217,   219,   227,   229,   233,   236,   239,   239,   253,
     259,   266,   266,   271,   271,   275,   275,   280,   280,   284,
     286,   290,   295,   299,   302,   305,   307,   311,   317,   322,
     324,   324,   330,   330,   330,   336,   336,   342,   342,   348,
     348,   358,   358,   370,   372,   376,   377,   385,   387,   390,
     393,   400,   409,   411,   418,   422,   424,   428,   430,   432,
     437,   439,   441,   443,   447,   451,   454,   458
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INUM", "RNUM", "ADDOP", "MULOP",
  "RELOP", "ASSOP", "NOT", "ARRAYOP", "PARENOP", "LISTOP", "IDENT",
  "STRING", "PROGRAM", "FUNCTION", "PROCEDURE", "VAR", "ARRAY", "OF",
  "DOTDOT", "INTEGER", "REAL", "BOOL", "IF", "WHILE", "FOR", "REPEAT",
  "BEG", "END", "THEN", "THAN", "ELSE", "DO", "DOWNTO", "TO", "UNTIL",
  "EMPTY", "'('", "')'", "';'", "'.'", "','", "':'", "'['", "']'",
  "$accept", "start", "program", "$@1", "$@2", "$@3", "ident_list",
  "decls", "type", "std_type", "subprogram_decls", "subprogram_decl",
  "$@4", "subprogram_head", "fn_header", "$@5", "$@6", "proc_header",
  "$@7", "$@8", "param_list", "param", "compound_stmt", "opt_stmts",
  "stmt_list", "stmt", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "var", "procedure_stmt", "expr_list", "expr", "simple_expr",
  "term", "factor", "id", "fn", "inum", "rnum", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    40,
      41,    59,    46,    44,    58,    91,    93
};
# endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,     6,    27,   -75,   -75,   -75,   -75,     1,    44,   -75,
     -28,   -75,    50,    45,   -75,   -75,    35,    44,    19,    28,
       6,     6,    53,    52,   -75,     9,    55,    58,    59,    60,
      41,    42,   -75,    35,    61,   -75,   -75,    62,   -75,    24,
      65,   -75,   -75,    66,   -75,   -75,    17,    17,    94,   -75,
     -75,    79,    69,   -75,   103,   -75,     3,   -75,    19,   109,
     -75,    72,    44,    44,   -75,   -75,    20,    20,    17,    43,
      57,   108,   -75,   -29,   -75,   -75,   -75,   107,    71,    41,
     -75,    41,    17,    17,    17,    53,    97,   -75,    33,    40,
     -75,    49,   108,   -75,    80,   -75,   -75,    20,    17,    20,
      17,    17,    85,    17,    84,   -75,   -75,    -6,   -75,    78,
     -75,   109,     9,   -75,    44,   -75,   -75,    41,    41,   108,
     120,   -75,    12,    81,    41,    56,    17,   -75,    17,   -75,
      82,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    17,    17,
     -75,   -75,   106,    96,    98,    99,    24,    41,   -75,   -75,
     -75,   -75,    41,    41,   -75,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,    75,     3,     1,     0,     0,     7,
       0,     4,     0,     0,     8,    10,    16,     0,     5,     0,
       0,     0,     0,     0,    10,     0,     0,    21,     0,    25,
      34,     0,    15,    16,     0,    13,    14,     0,    11,     0,
       0,    24,    20,     0,    28,    74,     0,     0,     0,    47,
      39,     0,    33,    35,     0,    38,    55,     6,    17,     0,
       9,     0,     0,     0,    76,    77,     0,     0,     0,     0,
      60,    62,    65,    67,    70,    71,    45,     0,    53,     0,
      32,     0,     0,    59,     0,     0,     0,    19,     0,     0,
      29,     0,    63,    73,     0,    40,    42,     0,     0,     0,
      59,     0,     0,     0,     0,    36,    37,     0,    57,     0,
      18,     0,     0,    22,     0,    26,    72,     0,     0,    64,
      61,    66,     0,     0,     0,     0,     0,    56,     0,    54,
       0,    31,    30,    41,    43,    69,    68,    46,     0,     0,
      48,    58,     0,     0,     0,     0,     0,     0,    51,    49,
      12,    44,     0,     0,    52,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,     0,   110,    18,   -38,
     102,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
      68,    22,   -20,   -75,   -75,   -74,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,    89,   -75,    38,   -43,    46,   -52,   -61,
     -30,    77,   -50,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,    13,    22,    88,    16,    37,    38,
      18,    23,    85,    24,    26,    40,    41,    28,    43,    44,
      89,    90,    50,    51,    52,    53,   117,   118,   143,   102,
      79,   153,   152,    54,    55,   107,   108,    70,    71,    72,
      73,     5,    74,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    61,    31,    69,    76,   104,    93,   105,    10,    86,
     100,   -53,    11,     1,    92,    12,   101,    19,    78,     4,
      64,    65,    66,    64,    65,    94,    67,     6,    34,    67,
      45,    35,    36,    45,   127,    20,    21,   128,   121,   106,
       8,   109,    83,   133,   134,   119,    35,    36,    84,    56,
     137,    56,   135,    17,    45,   128,    68,     9,   123,    68,
     125,   130,    97,    14,    98,   110,    46,    47,    48,    49,
      30,    12,    25,   151,    95,    96,    12,   112,   154,   155,
     113,   114,    30,   140,    57,   141,    15,    56,    56,   115,
     114,   138,   139,    32,    56,   144,   145,    27,    29,    39,
      42,   -27,   -23,    60,    62,    63,    59,    45,   150,    80,
      81,    82,    64,    87,    99,   103,    84,    56,   111,   124,
     116,   126,    56,    56,   129,    97,   146,   136,   142,   147,
     131,    91,   148,   149,    33,    58,   132,    77,   122,     0,
       0,     0,     0,     0,   120
};

static const yytype_int16 yycheck[] =
{
      30,    39,    22,    46,    47,    79,    67,    81,     8,    59,
      39,     8,    40,    15,    66,    43,    45,    17,    48,    13,
       3,     4,     5,     3,     4,    68,     9,     0,    19,     9,
      13,    22,    23,    13,    40,    16,    17,    43,    99,    82,
      39,    84,    39,   117,   118,    97,    22,    23,    45,    79,
     124,    81,    40,    18,    13,    43,    39,    13,   101,    39,
     103,   111,     5,    13,     7,    85,    25,    26,    27,    28,
      29,    43,    44,   147,    31,    32,    43,    44,   152,   153,
      40,    41,    29,   126,    42,   128,    41,   117,   118,    40,
      41,    35,    36,    41,   124,   138,   139,    20,    21,    44,
      41,    41,    44,    41,    39,    39,    45,    13,   146,    30,
      41,     8,     3,    41,     6,     8,    45,   147,    21,    34,
      40,    37,   152,   153,    46,     5,    20,    46,    46,    33,
     112,    63,    34,    34,    24,    33,   114,    48,   100,    -1,
      -1,    -1,    -1,    -1,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    15,    48,    49,    13,    88,     0,    50,    39,    13,
      53,    40,    43,    51,    13,    41,    54,    18,    57,    53,
      16,    17,    52,    58,    60,    44,    61,    88,    64,    88,
      29,    69,    41,    54,    19,    22,    23,    55,    56,    44,
      62,    63,    41,    65,    66,    13,    25,    26,    27,    28,
      69,    70,    71,    72,    80,    81,    87,    42,    57,    45,
      41,    56,    39,    39,     3,     4,     5,     9,    39,    83,
      84,    85,    86,    87,    89,    90,    83,    80,    87,    77,
      30,    41,     8,    39,    45,    59,    89,    41,    53,    67,
      68,    67,    85,    86,    83,    31,    32,     5,     7,     6,
      39,    45,    76,     8,    72,    72,    83,    82,    83,    83,
      69,    21,    44,    40,    41,    40,    40,    73,    74,    85,
      84,    86,    82,    83,    34,    83,    37,    40,    43,    46,
      89,    55,    68,    72,    72,    40,    46,    72,    35,    36,
      83,    83,    46,    75,    83,    83,    20,    33,    34,    34,
      56,    72,    79,    78,    72,    72
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    50,    51,    52,    49,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    59,    58,    60,
      60,    62,    61,    63,    61,    65,    64,    66,    64,    67,
      67,    68,    69,    70,    70,    71,    71,    72,    72,    72,
      73,    72,    74,    75,    72,    76,    72,    77,    72,    78,
      72,    79,    72,    80,    80,    81,    81,    82,    82,    82,
      83,    83,    84,    84,    84,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    87,    88,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     0,     0,    13,     1,     3,     6,
       0,     1,     8,     1,     1,     3,     0,     0,     5,     5,
       3,     0,     5,     0,     2,     0,     5,     0,     2,     1,
       3,     3,     3,     1,     0,     1,     3,     3,     1,     1,
       0,     5,     0,     0,     8,     0,     5,     0,     5,     0,
       9,     0,     9,     1,     4,     1,     4,     1,     3,     0,
       1,     3,     1,     2,     3,     1,     3,     1,     4,     4,
       1,     1,     3,     2,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYPTRDIFF_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyesa, yy_state_t **yyes,
                YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

    yy_state_t yyesa[20];
    yy_state_t *yyes;
    YYPTRDIFF_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = 20;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2:
#line 173 "compiler.y"
                { print_tree((yyvsp[0].tval), 0); }
#line 1762 "compiler.tab.c"
    break;

  case 3:
#line 176 "compiler.y"
                     { push_table((yyvsp[0].tval)->attribute.sval, FUNCTION); }
#line 1768 "compiler.tab.c"
    break;

  case 4:
#line 176 "compiler.y"
                                                                                      { add_io((yyvsp[-1].tval)); }
#line 1774 "compiler.tab.c"
    break;

  case 5:
#line 176 "compiler.y"
                                                                                                                                 { main_header(); caller = top_table(); }
#line 1780 "compiler.tab.c"
    break;

  case 6:
#line 177 "compiler.y"
                {
			(yyval.tval) = str_tree(PROGRAM, "head body",
					op_tree(PARENOP, "()", (yyvsp[-11].tval), (yyvsp[-8].tval)),
					str_tree(PROGRAM, "decls compound_stmt",
						str_tree(PROGRAM, "decls sub_decls", (yyvsp[-4].tval), (yyvsp[-3].tval)),
					(yyvsp[-1].tval))
				);
			main_footer();
			print_table(top_table());
			pop_table();
		}
#line 1796 "compiler.tab.c"
    break;

  case 7:
#line 191 "compiler.y"
                {
			(yyval.tval) = op_tree(LISTOP, ",", 
					empty_tree(),
					str_tree(IDENT, (yyvsp[0].sval), empty_tree(), empty_tree())
				);
		}
#line 1807 "compiler.tab.c"
    break;

  case 8:
#line 198 "compiler.y"
                {
			(yyval.tval) = op_tree(LISTOP, ",", 
					(yyvsp[-2].tval),
					str_tree(IDENT, (yyvsp[0].sval), empty_tree(), empty_tree())
				);
		}
#line 1818 "compiler.tab.c"
    break;

  case 9:
#line 207 "compiler.y"
                {
			(yyval.tval) = op_tree(LISTOP, ":",
					op_tree(VAR, (yyvsp[-4].sval), (yyvsp[-5].tval), (yyvsp[-3].tval)),
				 (yyvsp[-1].tval));
			make_vars((yyvsp[-3].tval), (yyvsp[-1].tval));
		}
#line 1829 "compiler.tab.c"
    break;

  case 10:
#line 214 "compiler.y"
                { (yyval.tval) = empty_tree(); }
#line 1835 "compiler.tab.c"
    break;

  case 11:
#line 218 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 1841 "compiler.tab.c"
    break;

  case 12:
#line 220 "compiler.y"
                { 
			(yyval.tval) = str_tree(ARRAY, "array-range type",
					op_tree(DOTDOT, (yyvsp[-4].sval), (yyvsp[-5].tval), (yyvsp[-3].tval)),
				 (yyvsp[0].tval));
		}
#line 1851 "compiler.tab.c"
    break;

  case 13:
#line 228 "compiler.y"
                { (yyval.tval) = str_tree(INTEGER, (yyvsp[0].sval), empty_tree(), empty_tree()); }
#line 1857 "compiler.tab.c"
    break;

  case 14:
#line 230 "compiler.y"
                { (yyval.tval) = str_tree(REAL, (yyvsp[0].sval), empty_tree(), empty_tree()); }
#line 1863 "compiler.tab.c"
    break;

  case 15:
#line 234 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, "_", (yyvsp[-2].tval), (yyvsp[-1].tval)); }
#line 1869 "compiler.tab.c"
    break;

  case 16:
#line 236 "compiler.y"
                { (yyval.tval) = empty_tree(); }
#line 1875 "compiler.tab.c"
    break;

  case 17:
#line 239 "compiler.y"
                                                         { function_header((yyvsp[-2].tval)); caller = top_table(); }
#line 1881 "compiler.tab.c"
    break;

  case 18:
#line 240 "compiler.y"
                {
			check_function((yyvsp[-4].tval), (yyvsp[0].tval));
			(yyval.tval) = op_tree(LISTOP, "_", (yyvsp[-4].tval), 
					op_tree(LISTOP, "_", (yyvsp[-3].tval), 
						op_tree(LISTOP, "_", (yyvsp[-2].tval), (yyvsp[0].tval))
					)
				 );
			function_footer((yyvsp[-4].tval)); 
			print_table(top_table());
			pop_table();
		}
#line 1897 "compiler.tab.c"
    break;

  case 19:
#line 254 "compiler.y"
                {
			(yyval.tval) = int_tree(FUNCTION, (yyvsp[-4].ival), (yyvsp[-3].tval), (yyvsp[-1].tval));
			make_function((yyvsp[-3].tval), (yyvsp[-1].tval));
			set_fn_assembly_label((yyvsp[-4].ival));
		}
#line 1907 "compiler.tab.c"
    break;

  case 20:
#line 260 "compiler.y"
                {
			(yyval.tval) = int_tree(PROCEDURE, (yyvsp[-2].ival), (yyvsp[-1].tval), empty_tree());
			make_procedure((yyvsp[-1].tval));
		}
#line 1916 "compiler.tab.c"
    break;

  case 21:
#line 266 "compiler.y"
               { push_table((yyvsp[0].tval)->attribute.sval, FUNCTION); }
#line 1922 "compiler.tab.c"
    break;

  case 22:
#line 267 "compiler.y"
                { 
			add_params((yyvsp[-1].tval));
			(yyval.tval) = op_tree(PARENOP, "()", (yyvsp[-4].tval), (yyvsp[-1].tval));
		}
#line 1931 "compiler.tab.c"
    break;

  case 23:
#line 271 "compiler.y"
             { push_table((yyvsp[0].tval)->attribute.sval, FUNCTION); }
#line 1937 "compiler.tab.c"
    break;

  case 24:
#line 272 "compiler.y"
                { (yyval.tval) = (yyvsp[-1].tval); }
#line 1943 "compiler.tab.c"
    break;

  case 25:
#line 275 "compiler.y"
                 { push_table((yyvsp[0].tval)->attribute.sval, PROCEDURE); }
#line 1949 "compiler.tab.c"
    break;

  case 26:
#line 276 "compiler.y"
                { 
			add_params((yyvsp[-1].tval));
			(yyval.tval) = op_tree(PARENOP, "()", (yyvsp[-4].tval), (yyvsp[-1].tval));
		}
#line 1958 "compiler.tab.c"
    break;

  case 27:
#line 280 "compiler.y"
             { push_table((yyvsp[0].tval)->attribute.sval, PROCEDURE); }
#line 1964 "compiler.tab.c"
    break;

  case 28:
#line 281 "compiler.y"
                { (yyval.tval) = (yyvsp[-1].tval); }
#line 1970 "compiler.tab.c"
    break;

  case 29:
#line 285 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ";", empty_tree(), (yyvsp[0].tval)); }
#line 1976 "compiler.tab.c"
    break;

  case 30:
#line 287 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ";", (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1982 "compiler.tab.c"
    break;

  case 31:
#line 291 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ":", (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1988 "compiler.tab.c"
    break;

  case 32:
#line 296 "compiler.y"
                { (yyval.tval) = str_tree(BEG, "begin-end", (yyvsp[-1].tval), empty_tree()); }
#line 1994 "compiler.tab.c"
    break;

  case 33:
#line 300 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2000 "compiler.tab.c"
    break;

  case 34:
#line 302 "compiler.y"
                { (yyval.tval) = empty_tree(); }
#line 2006 "compiler.tab.c"
    break;

  case 35:
#line 306 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2012 "compiler.tab.c"
    break;

  case 36:
#line 308 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ";", (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 2018 "compiler.tab.c"
    break;

  case 37:
#line 312 "compiler.y"
                { 
			check_types((yyvsp[-2].tval), (yyvsp[0].tval));
			(yyval.tval) = op_tree(ASSOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval));
			assignment_gencode((yyval.tval));
		}
#line 2028 "compiler.tab.c"
    break;

  case 38:
#line 318 "compiler.y"
                { 
			(yyval.tval) = (yyvsp[0].tval);
			call_procedure((yyval.tval));
		}
#line 2037 "compiler.tab.c"
    break;

  case 39:
#line 323 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2043 "compiler.tab.c"
    break;

  case 40:
#line 324 "compiler.y"
                       { start_if_gencode((yyvsp[-1].tval), (yyvsp[-2].ival)); }
#line 2049 "compiler.tab.c"
    break;

  case 41:
#line 325 "compiler.y"
                {
			(yyval.tval) = str_tree(IF, "if then", (yyvsp[-3].tval), (yyvsp[0].tval));
			enforce_type((yyvsp[-3].tval), BOOL);
			end_if_gencode((yyvsp[-4].ival));
		}
#line 2059 "compiler.tab.c"
    break;

  case 42:
#line 330 "compiler.y"
                       { start_if_else_gencode((yyvsp[-1].tval), (yyvsp[-2].ival)); }
#line 2065 "compiler.tab.c"
    break;

  case 43:
#line 330 "compiler.y"
                                                               { mid_if_else_gencode((yyvsp[-4].ival)); }
#line 2071 "compiler.tab.c"
    break;

  case 44:
#line 331 "compiler.y"
                {
			(yyval.tval) = str_tree(IF, "if then-else", (yyvsp[-6].tval), str_tree(IF, "then else", (yyvsp[-3].tval), (yyvsp[0].tval)));
			enforce_type((yyvsp[-6].tval), BOOL);
			end_if_gencode(((yyvsp[-7].ival)+1));
		}
#line 2081 "compiler.tab.c"
    break;

  case 45:
#line 336 "compiler.y"
                     { start_while_do_gencode((yyvsp[0].tval), (yyvsp[-1].ival)); }
#line 2087 "compiler.tab.c"
    break;

  case 46:
#line 337 "compiler.y"
                {
			(yyval.tval) = str_tree(WHILE, "while do", (yyvsp[-3].tval), (yyvsp[0].tval));
			enforce_type((yyvsp[-3].tval), BOOL);
			end_while_do_gencode((yyvsp[-4].ival));
		}
#line 2097 "compiler.tab.c"
    break;

  case 47:
#line 342 "compiler.y"
                 { start_repeat_until_gencode((yyvsp[0].ival)); }
#line 2103 "compiler.tab.c"
    break;

  case 48:
#line 343 "compiler.y"
                {
			(yyval.tval) = str_tree(REPEAT, "repeat until", (yyvsp[-2].tval), (yyvsp[0].tval));
			enforce_type((yyvsp[0].tval), BOOL);
			end_repeat_until_gencode((yyvsp[0].tval), (yyvsp[-4].ival));
		}
#line 2113 "compiler.tab.c"
    break;

  case 49:
#line 348 "compiler.y"
                                        { start_for_gencode((yyvsp[-6].ival), (yyvsp[-5].tval), (yyvsp[-3].tval), (yyvsp[-2].sval), (yyvsp[-1].tval)); }
#line 2119 "compiler.tab.c"
    break;

  case 50:
#line 349 "compiler.y"
                {
			check_types((yyvsp[-5].tval), (yyvsp[-3].tval));
			check_types((yyvsp[-7].tval), (yyvsp[-5].tval));
			(yyval.tval) = str_tree(FOR, "for",
					op_tree(ASSOP, (yyvsp[-6].opval), (yyvsp[-7].tval), (yyvsp[-5].tval)),
					str_tree(TO, "to do", (yyvsp[-3].tval), (yyvsp[0].tval))
				);
			end_for_gencode((yyvsp[-8].ival), (yyvsp[-7].tval), (yyvsp[-4].sval));
		}
#line 2133 "compiler.tab.c"
    break;

  case 51:
#line 358 "compiler.y"
                                            { start_for_gencode((yyvsp[-6].ival), (yyvsp[-5].tval), (yyvsp[-3].tval), (yyvsp[-2].sval), (yyvsp[-1].tval)); }
#line 2139 "compiler.tab.c"
    break;

  case 52:
#line 359 "compiler.y"
                {
			check_types((yyvsp[-5].tval), (yyvsp[-3].tval));
			check_types((yyvsp[-7].tval), (yyvsp[-5].tval));
			(yyval.tval) = str_tree(FOR, "for",
					op_tree(ASSOP, (yyvsp[-6].opval), (yyvsp[-7].tval), (yyvsp[-5].tval)),
					str_tree(DOWNTO, "downto do", (yyvsp[-3].tval), (yyvsp[0].tval))
				);
			end_for_gencode((yyvsp[-8].ival), (yyvsp[-7].tval), (yyvsp[-4].sval));
		}
#line 2153 "compiler.tab.c"
    break;

  case 53:
#line 371 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2159 "compiler.tab.c"
    break;

  case 54:
#line 373 "compiler.y"
                { (yyval.tval) = op_tree(ARRAYOP, "[]", (yyvsp[-3].tval), (yyvsp[-1].tval)); }
#line 2165 "compiler.tab.c"
    break;

  case 55:
#line 376 "compiler.y"
                    { (yyval.tval) = (yyvsp[0].tval); }
#line 2171 "compiler.tab.c"
    break;

  case 56:
#line 378 "compiler.y"
                { 
			(yyval.tval) = op_tree(PARENOP, "()", (yyvsp[-3].tval), (yyvsp[-1].tval));
			entry_t* fn_entry = find_entry(top_table(), (yyvsp[-3].tval)->attribute.sval);
			check_args(fn_entry, (yyvsp[-1].tval));
		}
#line 2181 "compiler.tab.c"
    break;

  case 57:
#line 386 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ",", empty_tree(), (yyvsp[0].tval)); }
#line 2187 "compiler.tab.c"
    break;

  case 58:
#line 388 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ",", (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 2193 "compiler.tab.c"
    break;

  case 59:
#line 390 "compiler.y"
                { (yyval.tval) = op_tree(LISTOP, ",", empty_tree(), empty_tree()); }
#line 2199 "compiler.tab.c"
    break;

  case 60:
#line 394 "compiler.y"
                { 
			tree_t* t = (yyvsp[0].tval);
			number_tree(t);
			type(t);
			(yyval.tval) = t;
		}
#line 2210 "compiler.tab.c"
    break;

  case 61:
#line 401 "compiler.y"
                { 
			tree_t* t = op_tree(RELOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval));
			number_tree(t);
			type(t);
			(yyval.tval) = t;
		}
#line 2221 "compiler.tab.c"
    break;

  case 62:
#line 410 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2227 "compiler.tab.c"
    break;

  case 63:
#line 412 "compiler.y"
                { 	
			(yyval.tval) = op_tree(ADDOP, (yyvsp[-1].opval), 
					int_tree(INUM, 0, empty_tree(), empty_tree()), 
					(yyvsp[0].tval)
				);
		}
#line 2238 "compiler.tab.c"
    break;

  case 64:
#line 419 "compiler.y"
                { (yyval.tval) = op_tree(ADDOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 2244 "compiler.tab.c"
    break;

  case 65:
#line 423 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2250 "compiler.tab.c"
    break;

  case 66:
#line 425 "compiler.y"
                { (yyval.tval) = op_tree(MULOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 2256 "compiler.tab.c"
    break;

  case 67:
#line 429 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2262 "compiler.tab.c"
    break;

  case 68:
#line 431 "compiler.y"
                { (yyval.tval) = op_tree(ARRAYOP, "[]", (yyvsp[-3].tval), (yyvsp[-1].tval)); }
#line 2268 "compiler.tab.c"
    break;

  case 69:
#line 433 "compiler.y"
                {
			(yyval.tval) = op_tree(PARENOP, "()", (yyvsp[-3].tval), (yyvsp[-1].tval));
			call_function((yyval.tval));
		}
#line 2277 "compiler.tab.c"
    break;

  case 70:
#line 438 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2283 "compiler.tab.c"
    break;

  case 71:
#line 440 "compiler.y"
                { (yyval.tval) = (yyvsp[0].tval); }
#line 2289 "compiler.tab.c"
    break;

  case 72:
#line 442 "compiler.y"
                { (yyval.tval) = (yyvsp[-1].tval); }
#line 2295 "compiler.tab.c"
    break;

  case 73:
#line 444 "compiler.y"
                { (yyval.tval) = op_tree(NOT, (yyvsp[-1].opval), (yyvsp[0].tval), empty_tree()); }
#line 2301 "compiler.tab.c"
    break;

  case 74:
#line 448 "compiler.y"
                { (yyval.tval) = str_tree(IDENT, (yyvsp[0].sval), empty_tree(), empty_tree()); }
#line 2307 "compiler.tab.c"
    break;

  case 75:
#line 452 "compiler.y"
                { (yyval.tval) = str_tree(IDENT, (yyvsp[0].sval), empty_tree(), empty_tree()); }
#line 2313 "compiler.tab.c"
    break;

  case 76:
#line 455 "compiler.y"
                { (yyval.tval) = int_tree(INUM, (yyvsp[0].ival), empty_tree(), empty_tree()); }
#line 2319 "compiler.tab.c"
    break;

  case 77:
#line 459 "compiler.y"
                { (yyval.tval) = float_tree(RNUM, (yyvsp[0].fval), empty_tree(), empty_tree()); }
#line 2325 "compiler.tab.c"
    break;


#line 2329 "compiler.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 462 "compiler.y"

