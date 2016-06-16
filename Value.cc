#include "Object.hh"
#include "Value.hh"

namespace JSON {

	/** Initializer list constructor */
		Array::Array(const std::initializer_list<Value> &theList) {
		_array.reserve(theList.size());
		for (const auto &entry : theList) {
			_array.emplace_back(entry);
		}
	}


	Value::~Value()noexcept {
		switch (type_t) {
		case ValueType::STRING:
			string_v.~basic_string();
			break;
		case ValueType::ARRAY:
			array_v.~Array();
			break;
		case ValueType::OBJECT:
			object_v.~Object();
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

	Value::Value(Value&& v)
		: type_t(v.type_t)
	{
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
			new (&object_v) Object{ std::move(v.object_v) } ;
			break;
		}
	}

	void Value::swapValue(Value &a, Value &b, ValueType type)noexcept
	{
		switch (type)
		{
			/** Base types */
		case ValueType::INT:
			std::swap(a.int_v, b.int_v);
			break;

		case ValueType::FLOAT:
			std::swap(a.float_v, b.float_v);
			break;

		case ValueType::BOOL:
			std::swap(a.bool_v, b.bool_v);
			break;

		case ValueType::NIL:
			break;

		case ValueType::STRING:
			std::swap(a.string_v, b.string_v);
			break;

			/** Compound types */
		case ValueType::ARRAY:
			std::swap(a.array_v, b.array_v);
			break;

		case ValueType::OBJECT:
			std::swap(a.object_v, b.object_v);
			break;

		}
	}
}