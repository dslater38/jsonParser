// A Bison parser, made by GNU Bison 3.0.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 1 "json.y" // lalr1.cc:404


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

#line 59 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:404

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "json.tab.hh"

// User implementation prologue.

#line 73 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 140 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:479

  /// Build a parser object.
  parser::parser (JSON::Lexer *ptr_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ptr (ptr_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }

#if __cplusplus >= 199711L
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (basic_symbol && other)
    : Base (std::move(other))
    , value (std::move(other.value))
  {
    ((void)0);
  }
#endif

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }
  
#if __cplusplus >= 199711L
  
  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type&& that)
  {
    state = that.state;
    value = std::move(that.value);
    return *this;
  }
  
#endif

  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// $$ and @$.
    stack_symbol_type yylhs;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULL, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, ptr));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYLHS.VALUE to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yylhs.value = yystack_[yylen - 1].value;
    else
      yylhs.value = yystack_[0].value;


    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    try
      {
        switch (yyn)
          {
  case 2:
#line 92 "json.y" // lalr1.cc:867
    { ptr->setParsd((yystack_[0].value.value)); }
#line 558 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 3:
#line 95 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[1].value.value)); }
#line 564 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 4:
#line 98 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[1].value.value)); }
#line 570 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 5:
#line 101 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 576 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 6:
#line 102 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 582 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 7:
#line 103 "json.y" // lalr1.cc:867
    {(yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 588 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 8:
#line 104 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = JSON::Value{}; }
#line 594 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 9:
#line 105 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 600 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 10:
#line 106 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 606 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 11:
#line 107 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = std::move((yystack_[0].value.value)); }
#line 612 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 12:
#line 111 "json.y" // lalr1.cc:867
    {
        // Trim string
        const auto &s = (yystack_[0].value.value).as_string();
        (yylhs.value.value) = s.substr(1, s.length()-2);
    }
#line 622 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 13:
#line 116 "json.y" // lalr1.cc:867
    {
        // Trim string
        const auto &s = (yystack_[0].value.value).as_string();
		(yylhs.value.value) = s.substr(1, s.length()-2);
    }
#line 632 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 14:
#line 123 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = JSON::Object{}; }
#line 638 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 15:
#line 124 "json.y" // lalr1.cc:867
    {
		(yylhs.value.value) = JSON::Object{};
		(yylhs.value.value).emplace((yystack_[2].value.value).as_string().c_str(), std::move((yystack_[0].value.value)));
    }
#line 647 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 16:
#line 128 "json.y" // lalr1.cc:867
    { 
        (yylhs.value.value).emplace((yystack_[2].value.value).as_string().c_str(), std::move((yystack_[0].value.value)));
    }
#line 655 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 17:
#line 134 "json.y" // lalr1.cc:867
    { (yylhs.value.value) = JSON::Array{}; }
#line 661 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 18:
#line 135 "json.y" // lalr1.cc:867
    {
        (yylhs.value.value) = JSON::Array{};
        (yylhs.value.value).emplace_back(std::move((yystack_[0].value.value)));
    }
#line 670 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;

  case 19:
#line 139 "json.y" // lalr1.cc:867
    { 
        (yylhs.value.value).emplace_back(std::move((yystack_[0].value.value))); 
    }
#line 678 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
    break;


#line 682 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:867
          default:
            break;
          }
      }
    catch (const syntax_error& yyexc)
      {
        error (yyexc);
        YYERROR;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yylhs);
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    // Shift the result of the reduction.
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -5;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -4,    -4,     4,    -5,    -5,    -5,    -5,    -5,    -5,    17,
      -5,    -5,    -5,    -5,    -5,     9,    15,     8,    -5,    -4,
      -5,    -4,     4,    -5,    -5,    -5,    19,    -4,    -5
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,    17,    14,    12,    13,     5,     6,     7,     8,     0,
      10,    11,     2,     9,    18,     0,     0,     0,     1,     0,
       4,     0,     0,     3,    19,    15,     0,     0,    16
  };

  const signed char
  parser::yypgoto_[] =
  {
      -5,    -5,    -5,    -5,    -1,     0,    -5,    -5
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    12,    13,    17,    15
  };

  const unsigned char
  parser::yytable_[] =
  {
      14,     1,    16,     2,     0,     3,     4,     5,     6,     7,
       8,    22,    19,     3,     4,    20,    23,    18,    24,    21,
      25,     0,    26,    27,     0,     0,    28
  };

  const signed char
  parser::yycheck_[] =
  {
       1,     5,     2,     7,    -1,     9,    10,    11,    12,    13,
      14,     3,     3,     9,    10,     6,     8,     0,    19,     4,
      21,    -1,    22,     4,    -1,    -1,    27
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     5,     7,     9,    10,    11,    12,    13,    14,    16,
      17,    18,    19,    20,    19,    22,    20,    21,     0,     3,
       6,     4,     3,     8,    19,    19,    20,     4,    19
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    15,    16,    17,    18,    19,    19,    19,    19,    19,
      19,    19,    20,    20,    21,    21,    21,    22,    22,    22
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     5,     0,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "COMMA", "COLON", "SQUARE_BRACKET_L",
  "SQUARE_BRACKET_R", "CURLY_BRACKET_L", "CURLY_BRACKET_R",
  "DOUBLE_QUOTED_STRING", "SINGLE_QUOTED_STRING", "NUMBER_I", "NUMBER_F",
  "BOOLEAN", "NULL_T", "$accept", "json", "object", "array", "value",
  "string", "assignment_list", "list", YY_NULL
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    92,    92,    95,    98,   101,   102,   103,   104,   105,
     106,   107,   111,   116,   123,   124,   128,   134,   135,   139
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
    };
    const unsigned int user_token_number_max_ = 269;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1014 "D:\\Dev\\json\\msvc\\json\\..\\..\\json.tab.cc" // lalr1.cc:1177
#line 144 "json.y" // lalr1.cc:1178


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
