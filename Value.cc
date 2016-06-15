#include "Object.hh"
#include "Value.hh"

namespace JSON {

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
			string_v = v.string_v;
			break;

			/** Compound types */
		case ValueType::ARRAY:
			array_v = v.array_v;
			break;

		case ValueType::OBJECT:
			object_v = v.object_v;
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
			string_v = std::move(v.string_v);
			break;

			/** Compound types */
		case ValueType::ARRAY:
			array_v = std::move(v.array_v);
			break;

		case ValueType::OBJECT:
			object_v = std::move(v.object_v);
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