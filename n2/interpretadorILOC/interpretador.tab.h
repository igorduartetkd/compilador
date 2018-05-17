/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_INTERPRETADOR_TAB_H_INCLUDED
# define YY_YY_INTERPRETADOR_TAB_H_INCLUDED
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
    add = 258,
    sub = 259,
    mult = 260,
    div1 = 261,
    addI = 262,
    subI = 263,
    rsubI = 264,
    multI = 265,
    divI = 266,
    rdivI = 267,
    lshift = 268,
    lshiftI = 269,
    rshift = 270,
    rshiftI = 271,
    and = 272,
    andI = 273,
    or = 274,
    orI = 275,
    xor = 276,
    xorI = 277,
    loadI = 278,
    load = 279,
    loadAI = 280,
    loadAO = 281,
    cload = 282,
    cloadAI = 283,
    cloadAO = 284,
    store = 285,
    storeAI = 286,
    storeAO = 287,
    cstore = 288,
    cstoreAI = 289,
    cstoreAO = 290,
    i2i = 291,
    c2c = 292,
    c2i = 293,
    i2c = 294,
    jump = 295,
    jumpI = 296,
    cbr = 297,
    tbl = 298,
    cmp_LT = 299,
    cmp_LE = 300,
    cmp_EQ = 301,
    cmp_GE = 302,
    cmp_GT = 303,
    cmp_NE = 304,
    comp = 305,
    cbr_LT = 306,
    cbr_LE = 307,
    cbr_EQ = 308,
    cbr_GE = 309,
    cbr_GT = 310,
    cbr_NE = 311,
    nop = 312,
    reg = 313,
    virgula = 314,
    pontoVirgula = 315,
    doisPontos = 316,
    caractere = 317,
    label = 318,
    num = 319,
    abreColchete = 320,
    fechaColchete = 321,
    erro = 322,
    inputi = 323,
    outputi = 324,
    inputc = 325,
    outputc = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETADOR_TAB_H_INCLUDED  */
