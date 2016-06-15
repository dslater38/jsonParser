#include "json_st.hh"
#include <stdexcept>

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
            os << (long long int)v;
            break;
        
        case ValueType::FLOAT:
            os << (long double)v;
            break;
        
        case ValueType::BOOL:
            os << ((bool)v ? "true" : "false");
            break;
        
        case ValueType::NIL:
            os << "null";
            break;
        
        case ValueType::STRING:
            os << '"' << ((string)v).c_str() << '"';                
            break;
        
        /** Compound types */
        case ValueType::ARRAY:
            os << (Array)v;                
            break;
        
        case ValueType::OBJECT:
            os << (Object)v;                
            break;
        
    }
    return os;
}

ostream& operator<<(ostream& os, const Object& o)
{    
    os << "{" << endl;
    ind++;
    for (auto e = o.begin(); e != o.end();)
    {
        JSON::indent(os);
		os << '"';
		auto str = std::string{e->first};
		os << str.c_str();
		os << '"';
		os << ": ";
		os << e->second;
        // os << '"' << e->first << '"' << ": " << e->second;
        if (++e != o.end())
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
    for (auto e = a.begin(); e != a.end();)
    {
        JSON::indent(os);
        os << (*e);
        if (++e != a.end())
            os << ",";
        os << endl;
    }    
    ind--;
    JSON::indent(os);
    os << "]";
    
    return os;
}
