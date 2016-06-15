%{

    #include <iostream>
    #include <cstring>
    #include <stdio.h>
    #include <stdexcept>
    #include "json_st.hh"
    
    extern "C" 
    {
        void yyerror(const char *);
        int yylex();
    } 
        
    void load_string(const char *);
    void load_file(FILE*);
    JSON::Value parsd{};
%}

%code requires { #include "json_st.hh" 

#   define YYCOPY(To, From, Count) memcpy (To, From, (Count) * sizeof (*(From)))

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
	YYSTYPE() {memset(this,'\0',sizeof(YYSTYPE));}
	~YYSTYPE(){}
	YYSTYPE &operator=(const YYSTYPE &rhs){
		memcpy(this, &rhs, sizeof(YYSTYPE));
		return *this;
	}
} 

/** Define types for union values */
%type<string_v> DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING string
%type<int_v> NUMBER_I
%type<float_v> NUMBER_F
%type<bool_v> BOOLEAN
    
/** Declare tokens */
%token COMMA COLON
%token SQUARE_BRACKET_L SQUARE_BRACKET_R
%token CURLY_BRACKET_L CURLY_BRACKET_R
%token DOUBLE_QUOTED_STRING SINGLE_QUOTED_STRING
%token NUMBER_I NUMBER_F
%token BOOLEAN
%token NULL_T

%type <object_p> object assignment_list
%type <array_p> array list
%type <value_p> value

%start json

%%

// Entry point (every JSON file represents a value)
json: value { parsd = std::move($1); } ;

// Object rule
object: CURLY_BRACKET_L assignment_list CURLY_BRACKET_R { new (&$$) JSON::Object{std::move($2)}; } ;

// Array rule
array : SQUARE_BRACKET_L list SQUARE_BRACKET_R { new (&$$) JSON::Array{std::move($2)}; } ;

// Values rule
value : NUMBER_I { new (&$$) JSON::Value{$1}; }
    | NUMBER_F { new (&$$) JSON::Value{$1}; }
    | BOOLEAN { new (&$$) JSON::Value{$1}; }
    | NULL_T { new (&$$) JSON::Value{}; }
    | string { new (&$$) JSON::Value{std::move($1)}; }
    | object { new (&$$) JSON::Value{std::move($1)}; }
    | array { new (&$$) JSON::Value{std::move($1)}; }
    ;

// String rule
string : DOUBLE_QUOTED_STRING {
        // Trim string
        std::string s($1);
        new(&$$) std::string{s.substr(1, s.length()-2)};
    } 
    | SINGLE_QUOTED_STRING {
        // Trim string
        std::string s($1);
		new(&$$) std::string{s.substr(1, s.length()-2)};
    };

// Assignments rule
assignment_list: /* empty */ { new(&$$) JSON::Object{}; } 
    | string COLON value {
		new(&$$) JSON::Object{};
        $$.emplace(std::string($1), std::move($3));
    } 
    | assignment_list COMMA string COLON value { 
        $$.emplace(std::move($3), std::move($5));
    }
    ;
    
// List rule
list: /* empty */ { new (&$$) JSON::Array{}; }
    | value {
        new (&$$) JSON::Array{};
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
	auto fh = FileHandle{filename};
    JSON::Value v;
    load_file(fh);
    int status = yyparse();
        
    if (status)
        throw std::runtime_error("Error parsing file: JSON syntax.");

    return std::move(parsd);
}

JSON::Value parse_string(const std::string& s)
{
    load_string(s.c_str());
    
    int status = yyparse();
    
    if (status)
    {
        throw std::runtime_error("Error parsing file: JSON syntax.");
    }
    else
    {
        return parsd;    
    }
}

void yyerror(const char *s)
{
    fprintf(stderr, "error: %s\n", s);
}
