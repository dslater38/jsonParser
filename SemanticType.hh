#ifndef JSON_SEMANTICTYPE_H_
#define JSON_SEMANTICTYPE_H_
#pragma once
#include <string>
#include "Object.hh"
#include "Array.hh"
#include "Value.hh"

namespace JSON {
	struct SemanticType {
		JSON::Value value;
	};
	//union SemanticType
	//{
	//	// "Pure" types
	//	long long int int_v;
	//	long double float_v;
	//	bool bool_v;
	//	bool null_p;
	//	std::string string_v;

	//	// Pointers to more complex classes
	//	JSON::Object object_p;
	//	JSON::Array array_p;
	//	JSON::Value value_p;
	//	SemanticType() { memset(this, '\0', sizeof(SemanticType)); }
	//	~SemanticType() {}
	//	SemanticType &operator=(const SemanticType &rhs) {
	//		memcpy(this, &rhs, sizeof(SemanticType));
	//		return *this;
	//	}
	//};
}

#define YYSTYPE JSON::SemanticType

#endif // JSON_SEMANTICTYPE_H_
