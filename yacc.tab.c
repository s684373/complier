/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "yacc.y"

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <map>
#include <stack>
#include <string>
int ex(nodeType *p);
nodeType *opr(int oper,int nops,...);
nodeType *id(char *s);
nodeType *con(int value);
unsigned int BKDRHash(char *str);
void freeNode(nodeType *p);
int symi[1000];
int symb[1000];
extern int yylineno;
map<string,map<string,string> >symtable;
map<string,string>curmap;
stack<string> curscope;
extern "C"      
{         
  void yyerror(const char *s);
  extern int yylex(void);
  char *strdup(char *str);
}

/* Line 371 of yacc.c  */
#line 96 "yacc.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     VARIABLE = 259,
     ASIGN = 260,
     ARRAYASIGN = 261,
     FUNCTION = 262,
     END = 263,
     ARRAY = 264,
     TYPE = 265,
     OF = 266,
     RETURN = 267,
     CLASS = 268,
     EXTENDS = 269,
     CLASSFUN = 270,
     PROGRAM = 271,
     VAR = 272,
     IS = 273,
     BEGINNING = 274,
     WHILE = 275,
     IF = 276,
     PRINT = 277,
     DO = 278,
     ELIF = 279,
     THEN = 280,
     REPEAT = 281,
     UNTIL = 282,
     FOREACH = 283,
     IN = 284,
     ENDIF = 285,
     ENDWHILE = 286,
     ENDFOR = 287,
     XIABIAO = 288,
     IFX = 289,
     ELSE = 290,
     OR = 291,
     AND = 292,
     NE = 293,
     EQ = 294,
     LE = 295,
     GE = 296,
     UMINUS = 297
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 203 "yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    48,     2,     2,
      51,    52,    46,    44,    55,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      39,     2,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    40,    41,    42,    43,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    14,    18,    29,
      39,    48,    59,    73,    85,    98,   113,   127,   131,   134,
     140,   149,   154,   162,   173,   180,   186,   195,   202,   215,
     224,   226,   229,   231,   233,   238,   246,   250,   255,   258,
     262,   266,   270,   274,   278,   282,   286,   290,   294,   298,
     302,   306,   310,   314,   316,   318
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,    58,    59,    -1,    -1,    50,
      -1,    61,    50,    -1,    22,    61,    50,    -1,    16,     4,
      51,    52,    60,    18,    60,    19,    60,     8,    -1,    16,
       4,    51,    52,    18,    60,    19,    60,     8,    -1,    10,
       4,    18,    13,    60,     8,    13,    50,    -1,    10,     4,
      18,    13,    14,     4,    60,     8,    13,    50,    -1,     7,
       4,    51,    52,    60,    18,    60,    19,    60,     8,     7,
       4,    50,    -1,     7,     4,    51,    52,    18,    19,    60,
       8,     7,     4,    50,    -1,     7,     4,    51,    52,    60,
      18,    19,    60,     8,     7,     4,    50,    -1,     7,     4,
      51,    62,    52,    60,    18,    60,    19,    60,     8,     7,
       4,    50,    -1,     7,     4,    51,    62,    52,    60,    18,
      19,    60,     8,     7,     4,    50,    -1,    12,    61,    50,
      -1,    12,    50,    -1,    17,     4,    18,     4,    50,    -1,
      10,     4,    18,     9,    11,    61,     4,    50,    -1,     4,
       5,    61,    50,    -1,     4,    53,    61,    54,     5,    61,
      50,    -1,     4,    53,    61,    54,    53,    61,    54,     5,
      61,    50,    -1,    20,    61,    23,    60,     8,    20,    -1,
      26,    60,    27,    61,    50,    -1,    28,     4,    29,     4,
      23,    60,     8,    28,    -1,    21,    61,    25,    60,     8,
      21,    -1,    21,    61,    25,    60,    24,    61,    25,    60,
      35,    60,     8,    21,    -1,    21,    61,    25,    60,    35,
      60,     8,    21,    -1,    59,    -1,    60,    59,    -1,     3,
      -1,     4,    -1,     4,    53,    61,    54,    -1,     4,    53,
      61,    54,    53,    61,    54,    -1,     4,    51,    52,    -1,
       4,    51,    62,    52,    -1,    45,    61,    -1,    61,    44,
      61,    -1,    61,    45,    61,    -1,    61,    46,    61,    -1,
      61,    47,    61,    -1,    61,    48,    61,    -1,    61,    39,
      61,    -1,    61,    38,    61,    -1,    61,    43,    61,    -1,
      61,    42,    61,    -1,    61,    40,    61,    -1,    61,    41,
      61,    -1,    61,    37,    61,    -1,    61,    36,    61,    -1,
      51,    61,    52,    -1,    63,    -1,    61,    -1,    63,    55,
      61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    45,    45,    48,    49,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      79,    80,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   107,   110,   111
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "VARIABLE", "ASIGN",
  "ARRAYASIGN", "FUNCTION", "END", "ARRAY", "TYPE", "OF", "RETURN",
  "CLASS", "EXTENDS", "CLASSFUN", "PROGRAM", "VAR", "IS", "BEGINNING",
  "WHILE", "IF", "PRINT", "DO", "ELIF", "THEN", "REPEAT", "UNTIL",
  "FOREACH", "IN", "ENDIF", "ENDWHILE", "ENDFOR", "XIABIAO", "IFX", "ELSE",
  "OR", "AND", "'>'", "'<'", "NE", "EQ", "LE", "GE", "'+'", "'-'", "'*'",
  "'/'", "'%'", "UMINUS", "';'", "'('", "')'", "'['", "']'", "','",
  "$accept", "program", "function", "stmt", "stmt_list", "expr",
  "optparams", "params", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    62,    60,
     293,   294,   295,   296,    43,    45,    42,    47,    37,   297,
      59,    40,    41,    91,    93,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,    10,     9,
       8,    10,    13,    11,    12,    14,    13,     3,     2,     5,
       8,     4,     7,    10,     6,     5,     8,     6,    12,     8,
       1,     2,     1,     1,     4,     7,     3,     4,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    32,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,     3,
       0,     0,     0,     0,     0,     0,    33,    18,     0,     0,
       0,     0,     0,     0,    30,     0,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     0,    36,    54,     0,    53,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     7,     0,    31,
       0,    52,    51,    50,    45,    44,    48,    49,    47,    46,
      39,    40,    41,    42,    43,    21,    37,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,    19,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    27,     0,     0,     0,    22,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,    10,    35,
       0,     0,     0,    29,    26,     0,     0,     0,     0,     0,
       0,     0,     9,     0,     0,    23,     0,     0,     0,     0,
       0,    11,     8,     0,    13,     0,     0,     0,     0,     0,
      14,     0,     0,     0,    28,    12,    16,     0,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    34,    35,    20,    56,    57
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int16 yypact[] =
{
     -40,     4,   936,   -40,   -40,    -4,     1,    11,    19,    17,
      28,    21,    21,    21,   936,    49,    21,   -40,    21,   -40,
    1109,    21,     6,    21,   -20,    37,   -39,   -40,  1124,     8,
      42,   955,   979,  1139,   -40,   228,    33,   -40,  1092,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,   -40,  1154,   -40,  1214,    13,    22,  1016,    16,
      39,    21,   -40,    24,    67,   936,   936,   -40,    21,   -40,
      74,   -40,  1226,    45,   -18,   -18,   -18,   -18,   -18,   -18,
      27,    27,   -40,   -40,   -40,   -40,   -40,    21,    -3,   254,
      29,    68,   280,  1035,   306,    30,   332,   202,  1169,    75,
    1214,    21,    21,    80,   358,   936,    21,    96,   384,    50,
     936,   410,   -40,    84,    86,    21,   936,   -40,   936,  1184,
    1054,   936,   437,   463,   929,   936,    92,    21,   490,   936,
     -40,   -40,  1003,   516,   542,   -40,   103,   568,   936,   595,
     622,    61,   648,    64,  1073,   936,   675,   936,    94,    88,
      21,   110,   701,   936,   936,   728,   -40,   105,   -40,   -40,
     754,   936,   780,   -40,   -40,  1199,   115,   113,   806,   832,
     936,    73,   -40,   858,   936,   -40,    77,   120,   118,   121,
     884,   -40,   -40,   910,   -40,    79,   126,   129,   127,   117,
     -40,    93,    97,   138,   -40,   -40,   -40,    98,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,    -2,    47,    -5,    87,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      19,    21,   101,    28,     3,    24,    31,    32,    33,     4,
      26,    37,    22,    38,    61,    25,    53,    55,    58,     4,
      26,    29,     4,    26,     4,    26,    47,    48,    49,    50,
      51,    59,    30,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    22,    91,    23,
     102,    16,    92,    36,    55,    60,    93,    18,    54,    63,
      64,    16,    70,    98,    16,    86,    16,    18,    89,    27,
      18,    95,    18,    49,    50,    51,    94,    87,    99,   106,
     112,   105,   100,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    69,    69,   119,   120,   118,   121,
     125,   124,    69,   127,   130,   143,    69,   131,   150,    69,
     132,   156,    96,    97,   158,   163,   164,   166,   171,   176,
     177,    69,   144,   181,   185,   186,    69,   184,   187,   190,
     191,    69,    69,   192,   193,    69,   104,    69,   194,   108,
      69,   111,   197,   195,    69,   165,    90,   196,   198,     0,
      69,     0,   123,    69,     0,     0,     0,   128,    69,     0,
      69,     0,     0,   133,     0,   134,    69,    69,   137,   139,
       0,    69,   142,     0,     0,     0,   146,     0,    69,     0,
       0,    69,     0,     0,     0,   152,     0,   155,     0,     0,
       0,     0,   160,     0,   162,     0,     0,     0,     0,     0,
     168,   169,     0,     0,     0,     4,     5,     0,   173,     6,
     114,     0,     7,     0,     8,     0,     0,   180,     9,    10,
       0,   183,    11,    12,    13,     0,   115,     0,    14,     0,
      15,     4,     5,     0,     0,     6,     0,   116,     7,     0,
       8,     0,     0,     0,     9,    10,     0,    16,    11,    12,
      13,     0,    17,    18,    14,    68,    15,     4,     5,     0,
       0,     6,     0,     0,     7,     0,     8,     0,     0,     0,
       9,    10,   103,    16,    11,    12,    13,     0,    17,    18,
      14,     0,    15,     4,     5,     0,     0,     6,     0,     0,
       7,     0,     8,     0,   107,     0,     9,    10,     0,    16,
      11,    12,    13,     0,    17,    18,    14,     0,    15,     4,
       5,     0,     0,     6,     0,     0,     7,     0,     8,     0,
       0,     0,     9,    10,   110,    16,    11,    12,    13,     0,
      17,    18,    14,     0,    15,     4,     5,     0,     0,     6,
     113,     0,     7,     0,     8,     0,     0,     0,     9,    10,
       0,    16,    11,    12,    13,     0,    17,    18,    14,     0,
      15,     4,     5,     0,     0,     6,     0,     0,     7,     0,
       8,     0,     0,     0,     9,    10,   122,    16,    11,    12,
      13,     0,    17,    18,    14,     0,    15,     4,     5,     0,
       0,     6,   126,     0,     7,     0,     8,     0,     0,     0,
       9,    10,     0,    16,    11,    12,    13,     0,    17,    18,
      14,     0,    15,     4,     5,     0,     0,     6,     0,     0,
       7,     0,     8,     0,     0,     0,     9,    10,   129,    16,
      11,    12,    13,     0,    17,    18,    14,     0,    15,     0,
       4,     5,     0,     0,     6,     0,     0,     7,     0,     8,
       0,     0,     0,     9,    10,    16,   138,    11,    12,    13,
      17,    18,     0,    14,     0,    15,     4,     5,     0,     0,
       6,     0,     0,     7,     0,     8,     0,     0,     0,     9,
      10,   140,    16,    11,    12,    13,     0,    17,    18,    14,
       0,    15,     0,     4,     5,     0,     0,     6,     0,     0,
       7,     0,     8,     0,     0,     0,     9,    10,    16,   145,
      11,    12,    13,    17,    18,     0,    14,     0,    15,     4,
       5,     0,     0,     6,   148,     0,     7,     0,     8,     0,
       0,     0,     9,    10,     0,    16,    11,    12,    13,     0,
      17,    18,    14,     0,    15,     4,     5,     0,     0,     6,
     149,     0,     7,     0,     8,     0,     0,     0,     9,    10,
       0,    16,    11,    12,    13,     0,    17,    18,    14,     0,
      15,     4,     5,     0,     0,     6,   151,     0,     7,     0,
       8,     0,     0,     0,     9,    10,     0,    16,    11,    12,
      13,     0,    17,    18,    14,     0,    15,     0,     4,     5,
       0,     0,     6,     0,     0,     7,     0,     8,     0,     0,
       0,     9,    10,    16,   153,    11,    12,    13,    17,    18,
       0,    14,     0,    15,     0,     4,     5,     0,     0,     6,
       0,     0,     7,     0,     8,     0,     0,     0,     9,    10,
      16,   154,    11,    12,    13,    17,    18,     0,    14,     0,
      15,     4,     5,     0,     0,     6,   157,     0,     7,     0,
       8,     0,     0,     0,     9,    10,     0,    16,    11,    12,
      13,     0,    17,    18,    14,     0,    15,     0,     4,     5,
       0,     0,     6,     0,     0,     7,     0,     8,     0,     0,
       0,     9,    10,    16,   161,    11,    12,    13,    17,    18,
       0,    14,     0,    15,     4,     5,     0,     0,     6,   167,
       0,     7,     0,     8,     0,     0,     0,     9,    10,     0,
      16,    11,    12,    13,     0,    17,    18,    14,     0,    15,
       0,     4,     5,     0,     0,     6,     0,     0,     7,     0,
       8,     0,     0,     0,     9,    10,    16,   170,    11,    12,
      13,    17,    18,     0,    14,     0,    15,     4,     5,     0,
       0,     6,   172,     0,     7,     0,     8,     0,     0,     0,
       9,    10,     0,    16,    11,    12,    13,     0,    17,    18,
      14,     0,    15,     4,     5,     0,     0,     6,     0,     0,
       7,     0,     8,     0,     0,     0,     9,    10,     0,    16,
      11,    12,    13,     0,    17,    18,    14,     0,    15,     4,
       5,     0,     0,     6,   178,   174,     7,     0,     8,     0,
       0,     0,     9,    10,     0,    16,    11,    12,    13,     0,
      17,    18,    14,     0,    15,     4,     5,     0,     0,     6,
     179,     0,     7,     0,     8,     0,     0,     0,     9,    10,
       0,    16,    11,    12,    13,     0,    17,    18,    14,     0,
      15,     4,     5,     0,     0,     6,   182,     0,     7,     0,
       8,     0,     0,     0,     9,    10,     0,    16,    11,    12,
      13,     0,    17,    18,    14,     0,    15,     4,     5,     0,
       0,     6,   188,     0,     7,     0,     8,     0,     0,     0,
       9,    10,     0,    16,    11,    12,    13,     0,    17,    18,
      14,     0,    15,     4,     5,     0,     0,     6,   189,     0,
       7,     0,     8,     0,     0,     0,     9,    10,     0,    16,
      11,    12,    13,   141,    17,    18,    14,     0,    15,     4,
       5,     0,     0,     6,     0,     0,     7,     0,     8,     0,
       0,     0,     9,    10,     0,    16,    11,    12,    13,     0,
      17,    18,    14,     0,    15,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    65,     0,
       0,    16,     0,     0,     0,     0,    17,    18,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,     0,     0,     0,     0,     0,
      88,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,     0,     0,     0,     0,     0,   109,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     0,     0,     0,     0,     0,   136,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,     0,     0,     0,   159,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,     0,     0,     0,    71,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,    52,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     0,    62,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,    67,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     0,    85,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,   117,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     0,   135,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,   175,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,     5,     5,     8,     0,     4,    11,    12,    13,     3,
       4,    16,    51,    18,    53,     4,    21,    22,    23,     3,
       4,     4,     3,     4,     3,     4,    44,    45,    46,    47,
      48,    51,     4,    35,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    51,     9,    53,
      53,    45,    13,     4,    59,    18,    61,    51,    52,    51,
      18,    45,    29,    68,    45,    52,    45,    51,    52,    50,
      51,     4,    51,    46,    47,    48,    52,    55,     4,    11,
      50,    52,    87,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    96,    97,   101,   102,    23,    19,
       4,   106,   104,    53,    20,    13,   108,    21,     5,   111,
     115,    50,    65,    66,    50,    21,    28,     7,    13,     4,
       7,   123,   127,    50,     4,     7,   128,    50,     7,    50,
       4,   133,   134,     4,     7,   137,    89,   139,    21,    92,
     142,    94,     4,    50,   146,   150,    59,    50,    50,    -1,
     152,    -1,   105,   155,    -1,    -1,    -1,   110,   160,    -1,
     162,    -1,    -1,   116,    -1,   118,   168,   169,   121,   122,
      -1,   173,   125,    -1,    -1,    -1,   129,    -1,   180,    -1,
      -1,   183,    -1,    -1,    -1,   138,    -1,   140,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,    -1,    -1,    -1,    -1,
     153,   154,    -1,    -1,    -1,     3,     4,    -1,   161,     7,
       8,    -1,    10,    -1,    12,    -1,    -1,   170,    16,    17,
      -1,   174,    20,    21,    22,    -1,    24,    -1,    26,    -1,
      28,     3,     4,    -1,    -1,     7,    -1,    35,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    -1,    45,    20,    21,
      22,    -1,    50,    51,    26,    27,    28,     3,     4,    -1,
      -1,     7,    -1,    -1,    10,    -1,    12,    -1,    -1,    -1,
      16,    17,    18,    45,    20,    21,    22,    -1,    50,    51,
      26,    -1,    28,     3,     4,    -1,    -1,     7,    -1,    -1,
      10,    -1,    12,    -1,    14,    -1,    16,    17,    -1,    45,
      20,    21,    22,    -1,    50,    51,    26,    -1,    28,     3,
       4,    -1,    -1,     7,    -1,    -1,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    18,    45,    20,    21,    22,    -1,
      50,    51,    26,    -1,    28,     3,     4,    -1,    -1,     7,
       8,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,    17,
      -1,    45,    20,    21,    22,    -1,    50,    51,    26,    -1,
      28,     3,     4,    -1,    -1,     7,    -1,    -1,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    18,    45,    20,    21,
      22,    -1,    50,    51,    26,    -1,    28,     3,     4,    -1,
      -1,     7,     8,    -1,    10,    -1,    12,    -1,    -1,    -1,
      16,    17,    -1,    45,    20,    21,    22,    -1,    50,    51,
      26,    -1,    28,     3,     4,    -1,    -1,     7,    -1,    -1,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    18,    45,
      20,    21,    22,    -1,    50,    51,    26,    -1,    28,    -1,
       3,     4,    -1,    -1,     7,    -1,    -1,    10,    -1,    12,
      -1,    -1,    -1,    16,    17,    45,    19,    20,    21,    22,
      50,    51,    -1,    26,    -1,    28,     3,     4,    -1,    -1,
       7,    -1,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    18,    45,    20,    21,    22,    -1,    50,    51,    26,
      -1,    28,    -1,     3,     4,    -1,    -1,     7,    -1,    -1,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    45,    19,
      20,    21,    22,    50,    51,    -1,    26,    -1,    28,     3,
       4,    -1,    -1,     7,     8,    -1,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    45,    20,    21,    22,    -1,
      50,    51,    26,    -1,    28,     3,     4,    -1,    -1,     7,
       8,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,    17,
      -1,    45,    20,    21,    22,    -1,    50,    51,    26,    -1,
      28,     3,     4,    -1,    -1,     7,     8,    -1,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    -1,    45,    20,    21,
      22,    -1,    50,    51,    26,    -1,    28,    -1,     3,     4,
      -1,    -1,     7,    -1,    -1,    10,    -1,    12,    -1,    -1,
      -1,    16,    17,    45,    19,    20,    21,    22,    50,    51,
      -1,    26,    -1,    28,    -1,     3,     4,    -1,    -1,     7,
      -1,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,    17,
      45,    19,    20,    21,    22,    50,    51,    -1,    26,    -1,
      28,     3,     4,    -1,    -1,     7,     8,    -1,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    -1,    45,    20,    21,
      22,    -1,    50,    51,    26,    -1,    28,    -1,     3,     4,
      -1,    -1,     7,    -1,    -1,    10,    -1,    12,    -1,    -1,
      -1,    16,    17,    45,    19,    20,    21,    22,    50,    51,
      -1,    26,    -1,    28,     3,     4,    -1,    -1,     7,     8,
      -1,    10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,
      45,    20,    21,    22,    -1,    50,    51,    26,    -1,    28,
      -1,     3,     4,    -1,    -1,     7,    -1,    -1,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    45,    19,    20,    21,
      22,    50,    51,    -1,    26,    -1,    28,     3,     4,    -1,
      -1,     7,     8,    -1,    10,    -1,    12,    -1,    -1,    -1,
      16,    17,    -1,    45,    20,    21,    22,    -1,    50,    51,
      26,    -1,    28,     3,     4,    -1,    -1,     7,    -1,    -1,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,    45,
      20,    21,    22,    -1,    50,    51,    26,    -1,    28,     3,
       4,    -1,    -1,     7,     8,    35,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    45,    20,    21,    22,    -1,
      50,    51,    26,    -1,    28,     3,     4,    -1,    -1,     7,
       8,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,    17,
      -1,    45,    20,    21,    22,    -1,    50,    51,    26,    -1,
      28,     3,     4,    -1,    -1,     7,     8,    -1,    10,    -1,
      12,    -1,    -1,    -1,    16,    17,    -1,    45,    20,    21,
      22,    -1,    50,    51,    26,    -1,    28,     3,     4,    -1,
      -1,     7,     8,    -1,    10,    -1,    12,    -1,    -1,    -1,
      16,    17,    -1,    45,    20,    21,    22,    -1,    50,    51,
      26,    -1,    28,     3,     4,    -1,    -1,     7,     8,    -1,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,    45,
      20,    21,    22,     4,    50,    51,    26,    -1,    28,     3,
       4,    -1,    -1,     7,    -1,    -1,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    45,    20,    21,    22,    -1,
      50,    51,    26,    -1,    28,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    23,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,     0,     3,     4,     7,    10,    12,    16,
      17,    20,    21,    22,    26,    28,    45,    50,    51,    59,
      61,     5,    51,    53,     4,     4,     4,    50,    61,     4,
       4,    61,    61,    61,    59,    60,     4,    61,    61,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    50,    61,    52,    61,    62,    63,    61,    51,
      18,    53,    50,    51,    18,    23,    25,    50,    27,    59,
      29,    52,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    50,    52,    55,    54,    52,
      62,     9,    13,    61,    52,     4,    60,    60,    61,     4,
      61,     5,    53,    18,    60,    52,    11,    14,    60,    54,
      18,    60,    50,     8,     8,    24,    35,    50,    23,    61,
      61,    19,    18,    60,    61,     4,     8,    53,    60,    18,
      20,    21,    61,    60,    60,    50,    54,    60,    19,    60,
      18,     4,    60,    13,    61,    19,    60,    25,     8,     8,
       5,     8,    60,    19,    19,    60,    50,     8,    50,    54,
      60,    19,    60,    21,    28,    61,     7,     8,    60,    60,
      19,    13,     8,    60,    35,    50,     4,     7,     8,     8,
      60,    50,     8,    60,    50,     4,     7,     7,     8,     8,
      50,     4,     4,     7,    21,    50,    50,     4,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 45 "yacc.y"
    {exit(0);}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 48 "yacc.y"
    {ex((yyvsp[(2) - (2)].nPtr));freeNode((yyvsp[(2) - (2)].nPtr));}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 52 "yacc.y"
    {(yyval.nPtr) = opr(';',2,NULL,NULL);}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 53 "yacc.y"
    {(yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 54 "yacc.y"
    {(yyval.nPtr) = opr(PRINT,1,(yyvsp[(2) - (3)].nPtr));}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 55 "yacc.y"
    {(yyval.nPtr) = opr(PROGRAM,3,id((yyvsp[(2) - (10)].sIndex)),(yyvsp[(7) - (10)].nPtr),(yyvsp[(9) - (10)].nPtr));}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 56 "yacc.y"
    {(yyval.nPtr) = opr(PROGRAM,3,id((yyvsp[(2) - (9)].sIndex)),(yyvsp[(6) - (9)].nPtr),(yyvsp[(8) - (9)].nPtr));}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 57 "yacc.y"
    {(yyval.nPtr) = opr(CLASS,2,id((yyvsp[(2) - (8)].sIndex)),(yyvsp[(5) - (8)].nPtr));}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 58 "yacc.y"
    {(yyval.nPtr) = opr(EXTENDS,3,id((yyvsp[(2) - (10)].sIndex)),id((yyvsp[(6) - (10)].sIndex)),(yyvsp[(7) - (10)].nPtr));}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 59 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,4,(yyvsp[(2) - (13)].sIndex),(yyvsp[(5) - (13)].nPtr),(yyvsp[(7) - (13)].nPtr),(yyvsp[(9) - (13)].nPtr));}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 60 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,2,(yyvsp[(2) - (11)].sIndex),(yyvsp[(7) - (11)].nPtr));}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 61 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,3,(yyvsp[(2) - (12)].sIndex),(yyvsp[(5) - (12)].nPtr),(yyvsp[(8) - (12)].nPtr));}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 62 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,5,id((yyvsp[(2) - (14)].sIndex)),(yyvsp[(4) - (14)].nPtr),(yyvsp[(6) - (14)].nPtr),(yyvsp[(8) - (14)].nPtr),(yyvsp[(10) - (14)].nPtr));}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 63 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,4,id((yyvsp[(2) - (13)].sIndex)),(yyvsp[(4) - (13)].nPtr),(yyvsp[(6) - (13)].nPtr),(yyvsp[(9) - (13)].nPtr));}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 64 "yacc.y"
    {(yyval.nPtr) = opr(RETURN,1,(yyvsp[(2) - (3)].nPtr));}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 65 "yacc.y"
    {(yyval.nPtr) = opr(RETURN,0);}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 66 "yacc.y"
    {(yyval.nPtr) = opr(VAR,2,id((yyvsp[(2) - (5)].sIndex)),id((yyvsp[(4) - (5)].sIndex)));}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 67 "yacc.y"
    {(yyval.nPtr) = opr(ARRAY,3,id((yyvsp[(2) - (8)].sIndex)),(yyvsp[(6) - (8)].nPtr),id((yyvsp[(7) - (8)].sIndex)));}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 68 "yacc.y"
    {(yyval.nPtr) = opr(ASIGN,2,id((yyvsp[(1) - (4)].sIndex)),(yyvsp[(3) - (4)].nPtr));}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 69 "yacc.y"
    {(yyval.nPtr) = opr(ARRAYASIGN,3,id((yyvsp[(1) - (7)].sIndex)),opr(XIABIAO,1,(yyvsp[(3) - (7)].nPtr)),(yyvsp[(6) - (7)].nPtr));}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 70 "yacc.y"
    {(yyval.nPtr) = opr(ARRAYASIGN,3,id((yyvsp[(1) - (10)].sIndex)),opr(XIABIAO,2,(yyvsp[(3) - (10)].nPtr),(yyvsp[(6) - (10)].nPtr)),(yyvsp[(9) - (10)].nPtr));}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 71 "yacc.y"
    {(yyval.nPtr) = opr(WHILE,3,(yyvsp[(2) - (6)].nPtr),(yyvsp[(4) - (6)].nPtr),opr(ENDWHILE,0));}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 72 "yacc.y"
    {(yyval.nPtr) = opr(REPEAT,2,(yyvsp[(2) - (5)].nPtr),(yyvsp[(4) - (5)].nPtr));}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 73 "yacc.y"
    {(yyval.nPtr) = opr(FOREACH,4,id((yyvsp[(2) - (8)].sIndex)),id((yyvsp[(4) - (8)].sIndex)),(yyvsp[(6) - (8)].nPtr),opr(ENDFOR,0));}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 74 "yacc.y"
    {(yyval.nPtr) = opr(IF,3,(yyvsp[(2) - (6)].nPtr),(yyvsp[(4) - (6)].nPtr),opr(ENDIF,0));}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 75 "yacc.y"
    {(yyval.nPtr) = opr(IF,5,(yyvsp[(2) - (12)].nPtr),(yyvsp[(4) - (12)].nPtr),opr(ELIF,2,(yyvsp[(6) - (12)].nPtr),(yyvsp[(8) - (12)].nPtr)),opr(ELSE,1,(yyvsp[(10) - (12)].nPtr)),opr(ENDIF,0));}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 76 "yacc.y"
    {(yyval.nPtr) = opr(IF,4,(yyvsp[(2) - (8)].nPtr),(yyvsp[(4) - (8)].nPtr),opr(ELSE,1,(yyvsp[(6) - (8)].nPtr)),opr(ENDIF,0));}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 79 "yacc.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 80 "yacc.y"
    {(yyval.nPtr) = opr(';',2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 83 "yacc.y"
    {(yyval.nPtr) = con((yyvsp[(1) - (1)].iValue));}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 84 "yacc.y"
    {(yyval.nPtr) = id((yyvsp[(1) - (1)].sIndex));}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 85 "yacc.y"
    {(yyval.nPtr) = opr(ARRAY,2,id((yyvsp[(1) - (4)].sIndex)),opr(XIABIAO,1,(yyvsp[(3) - (4)].nPtr)));}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 86 "yacc.y"
    {(yyval.nPtr) = opr(ARRAY,2,id((yyvsp[(1) - (7)].sIndex)),opr(XIABIAO,2,(yyvsp[(3) - (7)].nPtr),(yyvsp[(6) - (7)].nPtr)));}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 87 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,1,id((yyvsp[(1) - (3)].sIndex)));}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 88 "yacc.y"
    {(yyval.nPtr) = opr(FUNCTION,2,id((yyvsp[(1) - (4)].sIndex)),(yyvsp[(3) - (4)].nPtr));}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 89 "yacc.y"
    {(yyval.nPtr) = opr(UMINUS,1,(yyvsp[(2) - (2)].nPtr));}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 90 "yacc.y"
    {(yyval.nPtr) = opr('+',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 91 "yacc.y"
    {(yyval.nPtr) = opr('-',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 92 "yacc.y"
    {(yyval.nPtr) = opr('*',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 93 "yacc.y"
    {(yyval.nPtr) = opr('/',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 94 "yacc.y"
    {(yyval.nPtr) = opr('%',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 95 "yacc.y"
    {(yyval.nPtr) = opr('<',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 96 "yacc.y"
    {(yyval.nPtr) = opr('>',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 97 "yacc.y"
    {(yyval.nPtr) = opr(GE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 98 "yacc.y"
    {(yyval.nPtr) = opr(LE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 99 "yacc.y"
    {(yyval.nPtr) = opr(NE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 100 "yacc.y"
    {(yyval.nPtr) = opr(EQ,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 101 "yacc.y"
    {(yyval.nPtr) = opr(AND,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 102 "yacc.y"
    {(yyval.nPtr) = opr(OR,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 103 "yacc.y"
    {(yyval.nPtr) = (yyvsp[(2) - (3)].nPtr);}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 107 "yacc.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 110 "yacc.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 111 "yacc.y"
    {(yyval.nPtr) = opr(',',2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;


/* Line 1787 of yacc.c  */
#line 2075 "yacc.tab.c"
      default: break;
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 113 "yacc.y"

nodeType *con(int value){
    nodeType *p;
    size_t nodeSize;
    nodeSize = sizeof(nodeType*) + sizeof(conNodeType);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
       yyerror("out of memory");
    p->type = typeCon;
    p->con.value = value;
    return p;
}
nodeType *id(char *s){ 
    nodeType *p;
    size_t nodeSize;
    int i = BKDRHash(s);
    //if(strcmp(s,"interger")==0)i = 1;
   // if(strcmp(s,"boolean")==0)i = 2;
    nodeSize = sizeof(nodeType*) + sizeof(idNodeType);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
      yyerror("out of memory");
    p->type = typeId;
    p->id.i = i;
    p->id.s = strdup(s);
    return p;
}
nodeType *opr(int  oper, int nops, ...) { 
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;
    nodeSize = sizeof(nodeType*) + sizeof(oprNodeType) + 
    (nops - 1)*sizeof(nodeType*);
    if((p = (nodeType*)malloc(nodeSize)) == NULL)
      yyerror("out of memory");
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap,nops);
    for(i = 0;i<nops;i++)
      p->opr.op[i] = va_arg(ap,nodeType*);
    va_end(ap);
    if(oper==PROGRAM)
      {
          /*
          if(symtable.find(p->opr.op[0]->id.s)==symtable.end())
          {
            curscope.push(p->opr.op[0]->id.s);
            map<string,string>varmap;
            symtable[p->opr.op[0]->id.s]=varmap;
          }
          else
          {
            yyerror("this program can not be named this");
          }    */
      }
      else if(oper==FUNCTION)
      {
          /*map<string,string>::iterator iter;
          for(iter=curmap.begin();iter!=curmap.end();++iter)
          {
            cout<<"key:"<<iter->first<<" value:"<<iter->second<<endl;
          } 
          if(symtable[curscope.top()].find(p->opr.op[0]->id.s)==symtable[curscope.top()].end())
          {
            //symtable[curscope.top()][p->opr.op[0]->id.s]="function";
            curscope.push(p->opr.op[0]->id.s);
          }
           else
          {
            yyerror("this function's name has been used");
          }   
          cout<<symtable["example"]["isodd"];*/
      }
      else if(oper==VAR)
      {
        /*if(p->opr.op[1]->id.s!="ingeter"&&p->opr.op[1]->id.s!="boolean")
        {
          if(curmap.find(p->opr.op[1]->id.s)==curmap.end())
          {
            cout<<p->opr.op[1]->id.s;
            yyerror("this variable's type has not been defined");
          }
        }
        if(curmap.find(p->opr.op[0]->id.s)==curmap.end())
        {
          curmap[p->opr.op[0]->id.s]=p->opr.op[1]->id.s;
        }
        else
        {
          yyerror("this variable's name has been used");
        }*/
      }
      
    return p;
} 
void freeNode(nodeType *p) { 
  int i;
  if(!p)return;
  if(p->type == typeOpr){
    for(i = 0;i < p->opr.nops;i++)
      freeNode(p->opr.op[i]);
  }
  free(p);
} 
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 1; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
  
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
  
void yyerror(const char *s)     
{
   cerr<<yylineno<<":"<<s<<endl;  
}
int main()              //³ÌÐòÖ÷º¯Êý£¬Õâ¸öº¯ÊýÒ²¿ÉÒÔ·Åµ½ÆäËü.c, .cppÎÄ¼þÀï
{
  yyparse();            //Ê¹yacc¿ªÊ¼¶ÁÈ¡ÊäÈëºÍ½âÎö£¬Ëü»áµ÷ÓÃlexµÄyylex()¶ÁÈ¡¼ÇºÅ
  return 0;
}