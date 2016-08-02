%{

    #include <iostream>
	#include <fstream>
	#include <sstream>
    #include <cstring>
    #include <stdio.h>
    #include <stdexcept>
    #include "json_st.hh"
    #include "jsonLexer.hh"


    extern "C" 
    {
       // void yyerror(const char *);
        int yylex(JSON::SemanticType *val,  JSON::Lexer *lexer);
    } 
        
  //  void load_string(const char *);
   // void load_file(FILE*);
  //   JSON::Value parsd{};
%}

%require "3.0"

/* make a re-entrant parser - fewer globals*/
/* %pure_parser */
/* %define api.pure full */
%language "C++"
/* %locations */
/* %skeleton "glr.cc" */
/* %glr-parser */

%parse-param { JSON::Lexer *ptr }
%lex-param { JSON::Lexer *ptr }

%code requires { 

#include "json_st.hh" 
#include "SemanticType.hh"
#include "jsonLexer.hh"
// class FlexLexer;
// #   define YYCOPY(To, From, Count) memcpy (To, From, (Count) * sizeof (*(From)))

}

%union
{
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
	semantic_type() {memset(this,'\0',sizeof(semantic_type));}
	~semantic_type(){}
	semantic_type &operator=(const semantic_type &rhs){
		memcpy(this, &rhs, sizeof(semantic_type));
		return *this;
	}
} 

/** Define types for union values */
%type<value> DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING string
%type<value> NUMBER_I
%type<value> NUMBER_F
%type<value> BOOLEAN
    
/** Declare tokens */
%token COMMA COLON
%token SQUARE_BRACKET_L SQUARE_BRACKET_R
%token CURLY_BRACKET_L CURLY_BRACKET_R
%token DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
%token NUMBER_I NUMBER_F
%token BOOLEAN
%token NULL_T

%type <value> object assignment_list
%type <value> array list
%type <value> value

%start json

%%

// Entry point (every JSON file represents a value)
json: value { ptr->setParsd($1); } ;

// Object rule
object: CURLY_BRACKET_L assignment_list CURLY_BRACKET_R { $$ = std::move($2); } ;

// Array rule
array : SQUARE_BRACKET_L list SQUARE_BRACKET_R { $$ = std::move($2); } ;

// Values rule
value : NUMBER_I { $$ = std::move($1); }
    | NUMBER_F { $$ = std::move($1); }
    | BOOLEAN {$$ = std::move($1); }
    | NULL_T { $$ = JSON::Value{}; }
    | string { $$ = std::move($1); }
    | object { $$ = std::move($1); }
    | array { $$ = std::move($1); }
    ;

// String rule
string : DOUBLE_QUOTED_STRING {
        // Trim string
        const auto &s = $1.as_string();
        $$ = s.substr(1, s.length()-2);
    } 
    | SINGLE_QUOTED_STRING {
        // Trim string
        const auto &s = $1.as_string();
		$$ = s.substr(1, s.length()-2);
    };

// Assignments rule
assignment_list: /* empty */ { $$ = JSON::Object{}; } 
    | string COLON value {
		$$ = JSON::Object{};
		$$.emplace($1.as_string().c_str(), std::move($3));
    } 
    | assignment_list COMMA string COLON value { 
        $$.emplace($3.as_string().c_str(), std::move($5));
    }
    ;
    
// List rule
list: /* empty */ { $$ = JSON::Array{}; }
    | value {
        $$ = JSON::Array{};
        $$.emplace_back(std::move($1));
    }
    | list COMMA value { 
        $$.emplace_back(std::move($3)); 
    }
    ;
    
%%

class FileHandle
{
public:
	FileHandle(const char *fname) : fh_(nullptr) {
		fh_ = fopen(fname, "r");
		if(!fh_)
			throw std::runtime_error("Impossible to open file.");
	}
	~FileHandle() {
		if( fh_ ){
			fclose(fh_);
		}
	}
	operator FILE *() {return fh_;}
private:
	FILE *fh_;
};

JSON::Value parse_file(const char* filename)
{
	using Lexer=JSON::Lexer;
	auto stream = std::fstream{};
	stream.open(filename);
	if( stream.is_open() ){
		Lexer lexer{};
		lexer.switch_streams(&stream);
		yy::parser p{&lexer};
		auto status = p.parse();
		if (status)
			throw std::runtime_error("Error parsing file: JSON syntax.");

		return std::move(reinterpret_cast<Lexer &&>(lexer).getParsd());
	}
	return JSON::Value{};
/*
	auto fh = FileHandle{filename};
    JSON::Value v;
    load_file(fh);
    int status = yyparse();
        
    if (status)
        throw std::runtime_error("Error parsing file: JSON syntax.");

    return std::move( lexer.getParsd() ); // std::move(reinterpret_cast<Lexer &&>(lexer).getParsd());
*/
}

JSON::Value parse_string(const std::string& s)
{
	using Lexer = JSON::Lexer;
	auto stream = std::stringstream{s};
	Lexer lexer{};
	lexer.switch_streams(&stream);
	yy::parser p{&lexer};
	auto status = p.parse();
    if (status)
        throw std::runtime_error("Error parsing file: JSON syntax.");

    return std::move( lexer.getParsd() );


/*

    load_string(lexer, s.c_str());
    int status = yyparse();
    
    if (status)
    {
        throw std::runtime_error("Error parsing file: JSON syntax.");
    }
    else
    {
        return parsd;    
    }
	*/
}

void yy::parser::error(const std::string& msg)
{
    fprintf(stderr, "error: %s\n", msg.c_str());
}

int yylex(JSON::SemanticType *val,  JSON::Lexer *lexer)
{
	if( lexer ){
		lexer->yylval = val;
		return lexer->yylex();
	}else {
	return 0;
	}
}