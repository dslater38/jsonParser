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
	public:
		typedef std::unordered_map<std::string, Value> Map;

		/** Constructor. */
		Object() = default;

		/** Copy constructor.
		@param o object to copy from
		*/
		Object(const Object& o) = default;

		/** Move constructor. */
		Object(Object&& o) noexcept;

		/** Destructor. */
		~Object() = default;


		template<typename T, typename ...Targs >
		Object(const char * key, T value, Targs&&...Fargs)
		: Object(std::forward<Targs>(Fargs)...){
			//assign(std::move(key), std::move(value), std::forward<Targs>(Fargs)...);
			_object.emplace(key, value);
		}


		/** Swap */
		void swap(Object &o)noexcept;

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
		Value &operator[] (const char *key) {
			return operator[](std::string{ key });
		}

		Value &operator[](const std::string &key) {
			return _object[key];
		}

		Value &operator[](const std::string &&key) {
			return _object[std::move(key)];
		}

		/** Subscript operator, access an element by key.
		@param key key of the object to access
		*/
		const Value& operator[] (const char *key) const {
			return operator[](std::string{ key });
		}

		const Value& operator[] (const std::string &key) const {
			return _object.at(key);
		}

		/** Retrieves the starting const_iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator begin() const {
			return _object.begin();
		}

		/** Retrieves the ending const_iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator end() const {
			return _object.end();
		}

		/** Retrieves the starting const_iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator cbegin() const {
			return _object.cbegin();
		}

		/** Retrieves the ending const_iterator (const).
		@remark mainly for printing
		*/
		Map::const_iterator cend() const {
			return _object.cend();
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
		std::pair<Map::iterator, bool> insert(std::pair<const char *, Value> v);


		template< class... Args >
		void emplace(Args&&... args) {
			_object.emplace(std::forward<Args>(args)...);
		}


		/** Size of the object. */
		size_t size() const {
			return _object.size();
		}

		/** unparse this Object into a JSON string */
		std::string toString()const;

	private:
		void assign() {}

		template<typename T, typename ...Targs>
		void
			assign(const char * key, T v, Targs...Fargs) {
			_object.emplace(key, std::move(v));
			// _object[key] = Value{ std::move(v) };
			assign(std::forward<Targs>(Fargs)...);
		}

	protected:

		/** Inner container. */
		Map _object;
	};

	inline Object::Object(Object &&o) noexcept
		: _object(std::move(o._object)) {
	}


	inline void swap(Object &a, Object &b)noexcept {
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

static_assert(std::is_nothrow_move_constructible<JSON::Object>::value, "Error: JSON::Object should be nothrow move constructible");
static_assert(std::is_nothrow_destructible<JSON::Object>::value, "Error: JSON::Object should be nothrow destructible");
static_assert(std::is_nothrow_move_assignable<JSON::Object>::value, "Error: JSON::Object should be nothrow move assignable");
/** Output operator for Objects */
std::ostream& operator<<(std::ostream&, const JSON::Object&);


#endif // JSON_OBJECT_H_
