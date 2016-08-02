#ifndef JSON_ST_HH
#define JSON_ST_HH

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>

#include "ValueType.hh"
#include "Object.hh"
#include "Array.hh"
#include "Value.hh"

namespace JSON
{

	/** Indentation counter */
	static unsigned int ind;

	/** Print correct indentation before printing anything */
	static void indent(std::ostream& os = std::cout);

	/** Swap */
	inline void Object::swap(Object &o)noexcept {
		using std::swap;
		swap(_object, o._object);
	}

	inline std::pair<Object::Map::iterator, bool> Object::insert(std::pair<const char *, Value> v) {
		return _object.insert(std::move(v));
	}

	/** Initializer list constructor */
	inline Array::Array(const std::initializer_list<Value> &theList) {
		_array.reserve(theList.size());
		for (const auto &entry : theList) {
			_array.emplace_back(entry);
		}
	}






}


#endif