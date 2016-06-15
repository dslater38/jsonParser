#ifndef JSON_VALUETYPE_H_
#define JSON_VALUETYPE_H_
#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>

namespace JSON
{
	/** Possible JSON type of a value (array, object, bool, ...). */
	enum class ValueType
	{
		INT,        // JSON's int
		FLOAT,      // JSON's float 3.14 12e-10
		BOOL,       // JSON's boolean (true, false)
		STRING,     // JSON's string " ... " or (not really JSON) ' ... '
		OBJECT,     // JSON's object { ... }
		ARRAY,      // JSON's array [ ... ]
		NIL         // JSON's null
	};

}


#endif // JSON_VALUETYPE_H_