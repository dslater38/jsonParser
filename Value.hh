#ifndef JSON_VALUE_H_
#define JSON_VALUE_H_
#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cassert>
#include <experimental\string>

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

		template<typename T> using isntod  = std::is_nothrow_destructible<T>;
		template<typename T> using nothrowmove = std::is_nothrow_move_constructible<T>;

		/** Default constructor (type = ValueType::NIL). */
		Value()noexcept;

		/** Copy constructor. */
		Value(const Value& v);

		/** Move constructor. */
		Value(Value&& v)noexcept;

		/** Constructor from int. */
		explicit Value(const int64_t i)noexcept;

		/** Constructor from int. */
		explicit Value(const long int i)noexcept;

		/** Constructor from int. */
		explicit Value(const int i)noexcept;

		/** Constructor from float. */
		explicit Value(const long double f)noexcept;

		/** Constructor from float. */
		explicit Value(const double f)noexcept;

		/** Constructor from bool. */
		explicit Value(const bool b)noexcept;

		/** Constructor from pointer to char (C-string).  */
		explicit Value(const char* s);

		/** Constructor from STD string  */
		explicit Value(std::string s)noexcept(nothrowmove<std::string>::value);

		/** Constructor from Object. */
		explicit Value(Object o)noexcept(nothrowmove<Object>::value);

		/** Constructor from Array. */
		explicit Value(Array a)noexcept(nothrowmove<Array>::value);

		/** Destructor */
		~Value()noexcept;

		/** Swap with another value */
		void swap(Value &o)noexcept {
			if (this != &o) {
				if (type_t == o.type_t) {
					swapValue(*this, o, type_t);
				}
				else {
					auto t1{ std::move(o) };
					o.releaseResources();
					o.moveValueInto(std::move(*this));
					releaseResources();
					moveValueInto(std::move(t1));
				}
			}
		}

		/** Type query. */
		ValueType type() const
		{
			return type_t;
		}

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		Value &operator[] (const std::string& key);

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
		Value& operator=(Value v)noexcept {
			swap(v);
			return *this;
		}
		// Generalized assignment operator. Allow direct assignment
		// from supported types such as int, double, etc..
		template<class T>
		Value &operator=(T val)noexcept(std::is_nothrow_move_constructible<T>::value) {
			return this->operator=(Value{ std::move(val) });
		}

		// Explicitly enable assignment from a char *
		// and a const char * as the template below dis-allows pointers.
		Value &operator=(const char *key) {
			return this->operator=(Value{ key });
		}
		Value &operator=(char *key) {
			return this->operator=(const_cast<const char *>(key));
		}

		// prevent assignment from pointer types (both const & non-const )
		// otherwise, they'll be converted to bool
		// and create a Value with a bool type.
		template<class T>
		Value & operator=(T *val) = delete;

		template<class T>
		Value & operator=(const T *val) = delete;

		// prevent assignment from nullptr_t, otherwise
		// the nullptr_t value will silently convert to
		// (const char *)0, and cause an exception
		// inside the std::string constructor.
		// An alternative option would be to 
		// assign a NIL value for this method,
		Value &operator=(std::nullptr_t)noexcept {
			return operator=(Value{});
		}

		template< class... Args >
		void emplace_back(Args&&... args); 

		template< class... Args >
		void emplace(Args&&... args); 

		/** Cast operator for float */
		explicit operator long double() const noexcept { return as_float(); }

		/** Cast operator for int */
		explicit operator int64_t() const noexcept { return as_int(); }

		/** Cast operator for bool */
		explicit operator bool() const noexcept { return as_bool(); }

		/** Cast operator for string */
		explicit operator const std::string &() const noexcept { return as_string(); }

		/** Cast operator for Object */
		operator const Object &() const noexcept { return as_object(); }

		/** Cast operator for Array */
		operator const Array &() const noexcept { return as_array(); }

		/** Cast operator for float */
		long double as_float() const noexcept { assert(type_t == ValueType::FLOAT); return float_v; }

		/** Cast operator for int */
		int64_t as_int() const noexcept { assert(type_t == ValueType::INT); return int_v; }

		/** Cast operator for bool */
		bool as_bool() const noexcept { assert(type_t == ValueType::BOOL); return bool_v; }

		/** Cast operator for string */
		const std::string &as_string() const noexcept { assert(type_t == ValueType::STRING); return string_v; }

		/** Cast operator for Array */
		const Array &as_array()const noexcept { assert(type_t == ValueType::ARRAY); return array_v; }

		/** Cast operator for Object */
		const Object &as_object()const noexcept { assert(type_t == ValueType::OBJECT); return object_v; }

		/** unparse this Value into a JSON string */
		std::string toString()const;

	private:
		static void swapValue(Value &a, Value &b, ValueType type)noexcept;
		void releaseResources()noexcept;
		void moveValueInto(Value &&o)noexcept;
		static std::string Value::escapeString(const std::string &s);
	protected:

		union {
			long double   float_v;
			int64_t       int_v;
			bool          bool_v;
			std::string   string_v;

			Object        object_v;
			Array         array_v;
		};
		ValueType           type_t;
	};

	inline
		void swap(Value &a, Value &b)noexcept {
		a.swap(b);
	}


	inline Value::Value()noexcept : type_t(ValueType::NIL) {}

	inline Value::Value(const int64_t i)noexcept : int_v(i), type_t(ValueType::INT) { }

	inline Value::Value(const long int i)noexcept : int_v(static_cast<int64_t>(i)), type_t(ValueType::INT) { }

	inline Value::Value(const int i)noexcept : int_v(static_cast<int>(i)), type_t(ValueType::INT) { }

	inline Value::Value(const long double f)noexcept : float_v(f), type_t(ValueType::FLOAT) { }

	inline Value::Value(const double f)noexcept : float_v(static_cast<long double>(f)), type_t(ValueType::FLOAT) { }

	inline Value::Value(const bool b)noexcept : bool_v(b), type_t(ValueType::BOOL) { }

	inline Value::Value(const char* s) : type_t(ValueType::STRING) { new (&string_v) std::string{ s }; }

	inline Value::Value(std::string s)noexcept(std::is_nothrow_move_constructible<std::string>::value) : type_t(ValueType::STRING) { new (&string_v) std::string{ std::move(s) }; }

	inline Value::Value(Object o)noexcept(std::is_nothrow_move_constructible<Object>::value) : type_t(ValueType::OBJECT) { new (&object_v) Object{ std::move(o) }; }

	inline Value::Value(Array o)noexcept(std::is_nothrow_move_constructible<Array>::value) : type_t(ValueType::ARRAY) { new (&array_v) Array{ std::move(o) }; }

	inline Value::Value(Value &&v)noexcept { moveValueInto(std::move(v)); }

	inline Value::~Value()noexcept {
		releaseResources();
#ifdef _DEBUG
		memset(this, '\xFE', sizeof(Value));
#endif
	}


	inline Value &Value::operator[] (const std::string& key)
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

	template< class... Args >
	inline
	void Value::emplace_back(Args&&... args) {
		if (type_t != ValueType::ARRAY)
			throw std::logic_error("Value not an array");
		array_v.emplace_back(std::forward<Args>(args)...);
	}


	template< class... Args >
	inline
	void Value::emplace(Args&&... args) {
		if (type_t != ValueType::OBJECT)
			throw std::logic_error("Value not an object");
		object_v.emplace(std::forward<Args>(args)...);
	}

	inline void Value::releaseResources()noexcept {
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


static_assert(std::is_nothrow_move_constructible<JSON::Value>::value, "Error: JSON::Value should be nothrow move constructible");
static_assert(std::is_nothrow_destructible<JSON::Value>::value, "Error: JSON::Value should be nothrow destructible");
static_assert(std::is_nothrow_move_assignable<JSON::Value>::value, "Error: JSON::Value should be nothrow move assignable");
static_assert(std::is_nothrow_destructible<std::string>::value, "Error: JSON::Value::~Value assumes std::string is nothrow destructible");

#endif // JSON_VALUE_H_