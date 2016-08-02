#ifndef JLEXER_H_
#define JLEXER_H_
#pragma once

#include "FlexLexer.h"
#include "json.hh"

namespace JSON {

	typedef union yystype {
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
		yystype() { memset(this, '\0', sizeof(semantic_type)); }
		~yystype() {}
		yystype &operator=(const semantic_type &rhs) {
			memcpy(this, &rhs, sizeof(semantic_type));
			return *this;
		}
	} yystype;

	class myLexer : public yyFlexLexer
	{
	public:
		myLexer() = default;
		~myLexer() = default;
		myLexer(myLexer &&) = default;
		myLexer(const myLexer &) = default;

		JSON::Value json;

	};

}

#endif // JLEXER_H_