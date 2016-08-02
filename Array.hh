#ifndef JSON_ARRAY_H_
#define JSON_ARRAY_H_
#pragma once
#include <vector>
#include  <initializer_list>

#ifdef _MSC_VER
#ifdef NDEBUG
#pragma inline_recursion(on)
#pragma inline_depth(255)
#endif
#endif

namespace JSON
{
	class Value;

	/** A JSON array, i.e., an indexed container of elements. It contains
	JSON values, that can have any of the types in ValueType. */
	class Array
	{
	public:

		/** Constructor. */
		Array() = default;

		/** Destructor. */
		~Array() = default;

		/** Copy constructor.
		@param o the object to copy from
		*/
		Array(const Array& a) = default;

		/** Move constructor.
		@param o the object to copy from
		*/
		Array(Array&& a) = default;

		template<typename T, typename ...Targs >
		Array(T value, Targs&&...Fargs) {
			_array.reserve(sizeof...(Fargs));
			assign(std::move(value), std::forward<Targs>(Fargs)...);
		}

		/** Initializer list constructor */
		Array(const std::initializer_list<Value> &theList);

		/** Swap.
		@param o array to swap with
		*/
		void swap(Array& o)noexcept {
			using std::swap;
			swap(_array, o._array);
		}

		/** Assignment operator.
		@param a array to copy from
		*/
		Array& operator=(Array a)noexcept {
			swap(a);
			return *this;
		}

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		Value& operator[] (size_t i)noexcept {
			return _array[i];
		}

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		const Value& operator[] (size_t i) const {
			return _array.at(i);
		}

		/** Retrieves the starting const_iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator begin() const noexcept {
			return _array.begin();
		}

		/** Retrieves the ending const_iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator end() const noexcept {
			return _array.end();
		}

		/** Retrieves the starting const_iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator cbegin() const noexcept {
			return _array.cbegin();
		}

		/** Retrieves the ending const_iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator cend() const noexcept {
			return _array.cend();
		}

		/** Retrieves the starting iterator. */
		std::vector<Value>::iterator begin() noexcept {
			return _array.begin();
		}

		/** Retrieves the ending iterator */
		std::vector<Value>::iterator end() noexcept {
			return _array.end();
		}

		/** Inserts an element in the array.
		@param n (a pointer to) the value to add
		*/
		void push_back(const Value& n) {
			_array.push_back(n);
		}

		template< class... Args >
		void emplace_back(Args&&... args) {
			_array.emplace_back( std::forward<Args>(args)... );
		}

		/** Size of the array. */
		size_t size() const {
			return _array.size();
		}

		void reserve(size_t size) {
			_array.reserve(size);
		}

		/** unparse this Array into a JSON string */
		std::string toString()const;

	private:

		void assign() {}

		template<typename T, typename ...Targs>
		void
			assign(T value, Targs...Fargs) {
			_array.emplace_back(std::move(value));
			assign(std::forward<Targs>(Fargs)...);
		}


	protected:

		/** Inner container. */
		std::vector<Value> _array;

	};

	inline void swap(Array &a, Array &b)noexcept {
		a.swap(b);
	}

}


/** Output operator for Arrays */
std::ostream& operator<<(std::ostream&, const JSON::Array&);


namespace std {
	template<>
	inline
		void swap<JSON::Array>(JSON::Array &a, JSON::Array &b)noexcept {
		a.swap(b);
	}
}

static_assert(std::is_nothrow_move_constructible<JSON::Array>::value, "Error: JSON::Array should be nothrow move constructible");
static_assert(std::is_nothrow_destructible<JSON::Array>::value, "Error: JSON::Array should be nothrow destructible");
static_assert(std::is_nothrow_move_assignable<JSON::Array>::value, "Error: JSON::Array should be nothrow move assignable");

#endif // JSON_ARRAY_H_