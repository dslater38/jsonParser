#ifndef JSON_LEXER_H_
#define JSON_LEXER_H_
#pragma once

#ifndef yyFlexLexerOnce
#include "FlexLexer.h"
#endif


#include "Value.hh"
#include "SemanticType.hh"

namespace JSON {
	class Lexer : public yyFlexLexer
	{
	public:
		Lexer() = default;
		Lexer(Lexer &&) = delete;
		Lexer(const Lexer &) = delete;
		Lexer &operator=(const Lexer &) = delete;
		Lexer &operator=(Lexer &&) = delete;

		virtual int yylex() override;

		void setParsd(Value val) {
			parsd = std::move(val);
		}
		const Value &getParsd() & {
			return parsd;
		}
		Value &&getParsd() && {
			return std::move(parsd);
		}
	public:
		SemanticType *yylval{nullptr};
	private:
		Value parsd;
	};
}

#endif // JSON_LEXER_H_
