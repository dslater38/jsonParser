/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_D_DEV_JSON_MSVC_JSON_JSON_TAB_HH_INCLUDED
# define YY_YY_D_DEV_JSON_MSVC_JSON_JSON_TAB_HH_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2058 of yacc.c  */
#line 20 "json.y"
 #include "json_st.hh" 

#   define YYCOPY(To, From, Count) memcpy (To, From, (Count) * sizeof (*(From)))



/* Line 2058 of yacc.c  */
#line 53 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.hh"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMA = 258,
     COLON = 259,
     SQUARE_BRACKET_L = 260,
     SQUARE_BRACKET_R = 261,
     CURLY_BRACKET_L = 262,
     CURLY_BRACKET_R = 263,
     DOUBLE_QUOTED_STRING = 264,
     SINGLE_QUOTED_STRING = 265,
     NUMBER_I = 266,
     NUMBER_F = 267,
     BOOLEAN = 268,
     NULL_T = 269
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 27 "json.y"

    // "Pure" types
    long long int int_v;
    long double float_v;
    bool bool_v;
    bool null_p;
    std::string string_v;
    
    // Pointers to more complex classes
    JSON::Object object_p;
    JSON::Array array_p;
    JSON::Value value_p;
	YYSTYPE() {memset(this,'\0',sizeof(YYSTYPE));}
	~YYSTYPE(){}
	YYSTYPE &operator=(const YYSTYPE &rhs){
		memcpy(this, &rhs, sizeof(YYSTYPE));
		return *this;
	}


/* Line 2058 of yacc.c  */
#line 103 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
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

#endif /* !YY_YY_D_DEV_JSON_MSVC_JSON_JSON_TAB_HH_INCLUDED  */
