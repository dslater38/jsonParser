%option noyywrap 
%option yyclass="JSON::Lexer"
%option c++
%option yylineno
%option nodefault

%{
    // Provided externally
    //extern "C" 
    //{
    //    int yylex();
   //}
    
//#ifdef _MSC_VER
//#include <io.h>
//#define isatty _isatty
//#define fileno _fileno
//#endif

    // Needed for the tokens
    #include "json.tab.hh"
	#include "jsonLexer.hh"
	
	using token=yy::parser::token;
	

%}

%%

\"[^\"]*\"                              { yylval->value = std::string{yytext}; return token::DOUBLE_QUOTED_STRING; }
\'[^\']*\'                              { yylval->value = std::string{yytext}; return token::SINGLE_QUOTED_STRING; }
"["                                     { return token::SQUARE_BRACKET_L; }
"]"                                     { return token::SQUARE_BRACKET_R; }
"{"                                     { return token::CURLY_BRACKET_L; }
"}"                                     { return token::CURLY_BRACKET_R; }
","                                     { return token::COMMA; }
":"                                     { return token::COLON; }
\n                                      { }
[ \t]                                   { }
[-+]?[0-9]+                             { yylval->value = atoi(yytext); return token::NUMBER_I; }
[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  { yylval->value = atof(yytext); return token::NUMBER_F; }
true|false                              { yylval->value = ( strcmp(yytext, "true") == 0 ? true : false); return token::BOOLEAN; }
null                                    { return token::NULL_T; }
.                                       {  }

%%

#if 0

/** Sets the input string to the lexer */
void load_string(JSON::Lexer &lexer, const char* str)
{
    lexer.yy_switch_to_buffer(lexer.yy_scan_string(str));
}

/** Sets the input file to the lexer */
void load_file(FILE* file)
{
    yyrestart(file);
}

#endif // 0