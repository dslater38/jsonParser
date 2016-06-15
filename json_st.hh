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
}


#endif