#ifndef JSON_VALUE_H_
#define JSON_VALUE_H_
#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>

#include "ValueType.hh"
#include "Object.hh"
#include "Array.hh"

namespace JSON
{
	class Object;
	class Array;
	/** A JSON value. Can have either type in ValueTypes. */
	class Value
	{
	public:

		/** Default constructor (type = ValueType::NIL). */
		Value();

		/** Copy constructor. */
		Value(const Value& v);

		/** Move constructor. */
		Value(Value&& v);

		/** Constructor from int. */
		explicit Value(const long long int i);

		/** Constructor from int. */
		explicit Value(const long int i);

		/** Constructor from int. */
		explicit Value(const int i);

		/** Constructor from float. */
		explicit Value(const long double f);

		/** Constructor from float. */
		explicit Value(const double f);

		/** Constructor from bool. */
		explicit Value(const bool b);

		/** Constructor from pointer to char (C-string).  */
		explicit Value(const char* s);

		/** Constructor from STD string  */
		explicit Value(std::string s);

		/** Constructor from Object. */
		explicit Value(Object o);

		/** Constructor from Array. */
		explicit Value(Array a);

		/** Swap with another value */
		void swap(Value &o)noexcept {
			swapValue(*this, o, type_t);
			if (o.type_t != type_t) {
				swapValue(*this, o, o.type_t);
			}
			std::swap(type_t, o.type_t);
		}

		/** Type query. */
		ValueType type() const
		{
			return type_t;
		}

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		Object::Val operator[] (const std::string& key);

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		const Value& operator[] (const std::string& key) const;

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		Value& operator[] (size_t i);

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		const Value& operator[] (size_t i) const;

		/** Assignment operator. */
		Value& operator=(Value v) {
			swap(v);
			return *this;
		}

		/** Cast operator for float */
		explicit operator long double() const { return float_v; }

		/** Cast operator for int */
		explicit operator long long int() const { return int_v; }

		/** Cast operator for bool */
		explicit operator bool() const { return bool_v; }

		/** Cast operator for string */
		explicit operator std::string() const { return string_v; }

		/** Cast operator for Object */
		operator Object () const { return object_v; }

		/** Cast operator for Object */
		operator Array () const { return array_v; }

		/** Cast operator for float */
		long double as_float() const { return float_v; }

		/** Cast operator for int */
		long long int as_int() const { return int_v; }

		/** Cast operator for bool */
		bool as_bool() const { return bool_v; }

		/** Cast operator for string */
		std::string as_string() const { return string_v; }
	private:
		static void swapValue(Value &a, Value &b, ValueType type)noexcept;

	protected:

		long double         float_v;
		long long int       int_v;
		bool                bool_v;
		std::string         string_v;

		Object              object_v;
		Array               array_v;

		ValueType           type_t;
	};

	inline
		void swap(Value &a, Value &b)noexcept {
		a.swap(b);
	}


	inline Value::Value() : type_t(ValueType::NIL) { }

	inline Value::Value(const long long int i) : int_v(i), type_t(ValueType::INT) { }

	inline Value::Value(const long int i) : int_v(static_cast<long long int>(i)), type_t(ValueType::INT) { }

	inline Value::Value(const int i) : int_v(static_cast<int>(i)), type_t(ValueType::INT) { }

	inline Value::Value(const long double f) : float_v(f), type_t(ValueType::FLOAT) { }

	inline Value::Value(const double f) : float_v(static_cast<long double>(f)), type_t(ValueType::FLOAT) { }

	inline Value::Value(const bool b) : bool_v(b), type_t(ValueType::BOOL) { }

	inline Value::Value(const char* s) : string_v(s), type_t(ValueType::STRING) { }

	inline Value::Value(std::string s) : string_v(std::move(s)), type_t(ValueType::STRING) { }

	inline Value::Value(Object o) : object_v(std::move(o)), type_t(ValueType::OBJECT) { }

	inline Value::Value(Array o) : array_v(std::move(o)), type_t(ValueType::ARRAY) { }

	inline Object::Val Value::operator[] (const std::string& key)
	{
		if (type() != ValueType::OBJECT)
			throw std::logic_error("Value not an object");
		return object_v[key];
	}

	inline const Value& Value::operator[] (const std::string& key) const
	{
		if (type() != ValueType::OBJECT)
			throw std::logic_error("Value not an object");
		return object_v[key];
	}

	inline Value& Value::operator[] (size_t i)
	{
		if (type() != ValueType::ARRAY)
			throw std::logic_error("Value not an array");
		return array_v[i];
	}

	inline const Value& Value::operator[] (size_t i) const
	{
		if (type() != ValueType::ARRAY)
			throw std::logic_error("Value not an array");
		return array_v[i];
	}

}

/** Output operator for Values */
std::ostream& operator<<(std::ostream&, const JSON::Value&);

namespace std {
	template<>
	inline
		void swap<JSON::Value>(JSON::Value &a, JSON::Value &b)noexcept {
		a.swap(b);
	}
}

#endif // JSON_VALUE_H_