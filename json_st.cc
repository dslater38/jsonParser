#include "json_st.hh"
#include <stdexcept>
#include "json.tab.hh" // parser

using namespace std;
using namespace JSON;


void JSON::indent(ostream& os)
{
    for (unsigned int i  = 0; i < ind; i++)
        os << "\t";
}

ostream& operator<<(ostream& os, const Value& v)
{    
    switch(v.type())
    {
        /** Base types */
        case ValueType::INT:
            os << v.as_int();
            break;
        
        case ValueType::FLOAT:
            os << v.as_float();
            break;
        
        case ValueType::BOOL:
            os << (v.as_bool() ? "true" : "false");
            break;
        
        case ValueType::NIL:
            os << "null";
            break;
        
        case ValueType::STRING:
            os << '"' << v.as_string().c_str() << '"';                
            break;
        
        /** Compound types */
        case ValueType::ARRAY:
            os << v.as_array();                
            break;
        
        case ValueType::OBJECT:
            os << v.as_object();                
            break;
        
    }
    return os;
}

ostream& operator<<(ostream& os, const Object& o)
{    
    os << "{" << endl;
    ind++;
    for (auto e = std::cbegin(o), ee=std::cend(o); e !=ee; )
    {
        JSON::indent(os);
		os << '"';
		auto str = std::string{e->first};
		os << str.c_str();
		os << '"';
		os << ": ";
		os << e->second;
        // os << '"' << e->first << '"' << ": " << e->second;
        if (++e != ee)
            os << ",";
        os << endl;
    }    
    ind--;
    JSON::indent(os);
    os << "}";
    
    return os;
}

ostream& operator<<(ostream& os, const Array& a)
{
    os << "[" << endl;
    ind++;
    for (auto e = std::cbegin(a), ee = std::cend(a); e != ee;)
    {
        JSON::indent(os);
        os << (*e);
        if (++e != ee)
            os << ",";
        os << endl;
    }    
    ind--;
    JSON::indent(os);
    os << "]";
    
    return os;
}
