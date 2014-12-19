/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     IFX = 285,
     ELSE = 286,
     OR = 287,
     AND = 288,
     NE = 289,
     EQ = 290,
     LE = 291,
     GE = 292,
     UMINUS = 293
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define VARIABLE 259
#define ASIGN 260
#define ARRAYASIGN 261
#define FUNCTION 262
#define END 263
#define ARRAY 264
#define TYPE 265
#define OF 266
#define RETURN 267
#define CLASS 268
#define EXTENDS 269
#define CLASSFUN 270
#define PROGRAM 271
#define VAR 272
#define IS 273
#define BEGINNING 274
#define WHILE 275
#define IF 276
#define PRINT 277
#define DO 278
#define ELIF 279
#define THEN 280
#define REPEAT 281
#define UNTIL 282
#define FOREACH 283
#define IN 284
#define IFX 285
#define ELSE 286
#define OR 287
#define AND 288
#define NE 289
#define EQ 290
#define LE 291
#define GE 292
#define UMINUS 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

