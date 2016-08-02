#include "json_st.hh"
#include <string>
#include <array>

namespace JSON {

	void Value::moveValueInto(Value &&v)noexcept {
		type_t = v.type_t;
		switch (type_t)
		{
			/** Base types */
		case ValueType::INT:
			int_v = std::move(v.int_v);
			break;

		case ValueType::FLOAT:
			float_v = std::move(v.float_v);
			break;

		case ValueType::BOOL:
			bool_v = std::move(v.bool_v);
			break;

		case ValueType::NIL:
			break;

		case ValueType::STRING:
			new (&string_v) std::string{ std::move(v.string_v) };
			break;

			/** Compound types */
		case ValueType::ARRAY:
			new (&array_v) Array{ std::move(v.array_v) };
			break;

		case ValueType::OBJECT:
			new (&object_v) Object{ std::move(v.object_v) };
			break;
		}
	}

	Value::Value(const Value& v)
		: type_t(v.type_t)
	{
		switch (type_t)
		{
			/** Base types */
		case ValueType::INT:
			int_v = v.int_v;
			break;

		case ValueType::FLOAT:
			float_v = v.float_v;
			break;

		case ValueType::BOOL:
			bool_v = v.bool_v;
			break;

		case ValueType::NIL:
			break;

		case ValueType::STRING:
			new (&string_v) std::string{ v.string_v };
			break;

			/** Compound types */
		case ValueType::ARRAY:
			new (&array_v) Array{ v.array_v };
			break;

		case ValueType::OBJECT:
			new (&object_v) Object{ v.object_v };
			break;
		}
	}

	void Value::swapValue(Value &a, Value &b, ValueType type)noexcept
	{
		using std::swap;
		switch (type)
		{
			/** Base types */
		case ValueType::INT:
			swap(a.int_v, b.int_v);
			break;

		case ValueType::FLOAT:
			swap(a.float_v, b.float_v);
			break;

		case ValueType::BOOL:
			swap(a.bool_v, b.bool_v);
			break;

		case ValueType::NIL:
			break;

		case ValueType::STRING:
			swap(a.string_v, b.string_v);
			break;

			/** Compound types */
		case ValueType::ARRAY:
			swap(a.array_v, b.array_v);
			break;

		case ValueType::OBJECT:
			swap(a.object_v, b.object_v);
			break;

		}
	}

	std::string Value::toString()const
	{
		switch (type_t)
		{
				/** Base types */
			case ValueType::INT:
				return std::to_string(as_int());
				break;

			case ValueType::FLOAT:
				return std::to_string(as_float());
				break;

			case ValueType::BOOL:
				return as_bool() ? "true" : "false";
				break;

			case ValueType::NIL:
				return "null";
				break;

			case ValueType::STRING:
				return escapeString(as_string());
				break;

				/** Compound types */
			case ValueType::ARRAY:
				return as_array().toString();
				break;

			case ValueType::OBJECT:
				return as_object().toString();
				break;
		}
		return "";
	}

	namespace {
		constexpr std::array<char, 16> digits{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
		};

		std::string char2hex(const char c) {
			char str[7] = "\\u0000";
			str[4] = digits[static_cast<unsigned>((c & 0xF0) >> 4)];
			str[5] = digits[static_cast<unsigned>(c & 0x0F)];
			return std::string{ str };
		}
	}

	/**
	*
	* Create a JSON encoded string with all required fields escaped.
	*
	*/
	std::string Value::escapeString(const std::string &s) {
		auto retStr = std::string{"\""};
		for (const auto &c : s) {
			switch (c) {
			case '"':
			case '\\':
			case '/':
				retStr += '\\' + c;
				break;
			case '\b':
				retStr += "\\b";
				break;
			case '\f':
				retStr += "\\f";
				break;
			case '\n':
				retStr += "\\n";
				break;
			case '\r':
				retStr += "\\r";
				break;
			case '\t':
				retStr += "\\t";
				break;
			default:
				if (static_cast<unsigned char>(c) < ' ' || static_cast<unsigned char>(c) > 126) {
					retStr += char2hex(c);
				} else {
					retStr += c;
				}
			}
		}
		retStr += "\"";
		return retStr;
	}

	std::string Array::toString()const
	{
		auto retVal = std::string{ "[" };
		if (!_array.empty()) {
			for (const auto &entry : _array) {
				retVal += entry.toString() + ",";
			}
			retVal.at(retVal.size() - 1) = ']';	// overwrite the trailing , with the closing ]
		}
		else
			retVal += "]";
		return retVal;
	}

	std::string Object::toString()const
	{
		auto retVal = std::string{ "{" };
		if (!_object.empty()) {
			for (const auto & entry : _object) {
				retVal += "\"" + entry.first + "\":" + entry.second.toString() + ",";
			}
			retVal.at(retVal.size() - 1) = '}'; // overwrite the trailing , with the closing }
		}
		else
			retVal += "}";
		return retVal;
	}
}