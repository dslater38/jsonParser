#ifndef JSON_OBJECT_H_
#define JSON_OBJECT_H_
#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>

namespace JSON
{
	// Forward declaration
	class Value;

	/** A JSON object, i.e., a container whose keys are strings, this
	is roughly equivalent to a Python dictionary, a PHP's associative
	array, a Perl or a C++ map (depending on the implementation). */
	class Object
	{
		typedef std::unordered_map<std::string, Value> Map;
	public:

		class Val {
		public:
			explicit Val(Value &v_) : v(v_) {}

			template<class T> void operator=(T rhs);

		private:
			Value &v;
		};

		/** Constructor. */
		Object() = default;

		/** Copy constructor.
		@param o object to copy from
		*/
		Object(const Object& o) = default;

		/** Move constructor. */
		Object(Object&& o) = default;

		/** Destructor. */
		~Object() = default;

		/** Swap */
		void swap(Object &o)noexcept {
			std::swap(_object, o._object);
		}
		/** Assignment operator.
		@param o object to assign from
		*/
		Object& operator=(Object o)noexcept {
			swap(o);
			return *this;
		}

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		Val operator[] (const std::string& key);

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		const Value& operator[] (const std::string& key) const {
			return _object.at(key);
		}

		/** Retrieves the starting iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator begin() const {
			return _object.begin();
		}

		/** Retrieves the ending iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator end() const {
			return _object.end();
		}

		/** Retrieves the starting iterator */
		Map::iterator begin() {
			return _object.begin();
		}

		/** Retrieves the ending iterator */
		Map::iterator end() {
			return _object.end();
		}

		/** Inserts a field in the object.
		@param v pair <key, value> to insert
		@return an iterator to the inserted object
		*/
		std::pair<Map::iterator, bool> insert(std::pair<std::string, Value> v);


		template< class... Args >
		void emplace(Args&&... args) {
			_object.emplace(std::forward<Args>(args)...);
		}


		/** Size of the object. */
		size_t size() const {
			return _object.size();
		}

	protected:

		/** Inner container. */
		Map _object;
	};
	inline
		void swap(Object &a, Object &b)noexcept {
		a.swap(b);
	}
}

namespace std {
	template<>
	inline
		void swap<JSON::Object>(JSON::Object &a, JSON::Object &b)noexcept {
		a.swap(b);
	}
}

/** Output operator for Objects */
std::ostream& operator<<(std::ostream&, const JSON::Object&);


#include "Value.hh"

namespace JSON {

	template<class T>
	inline
		void Object::Val::operator=(T rhs) {
		v = Value(std::move(rhs));
	}


	inline
		std::pair<Object::Map::iterator, bool> Object::insert(std::pair<std::string, Value> v) {
		return _object.insert(std::move(v));
	}

	inline Object::Val Object::operator[] (const std::string& key) {
		return Val(_object[key]);
	}

}

#endif // JSON_OBJECT_H_
