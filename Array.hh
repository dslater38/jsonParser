#ifndef JSON_ARRAY_H_
#define JSON_ARRAY_H_
#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>

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

		/** Swap.
		@param o array to swap with
		*/
		void swap(Array& o)noexcept {
			std::swap(_array, o._array);
		}

		/** Assignment operator.
		@param a array to copy from
		*/
		Array& operator=(Array a) {
			swap(a);
			return *this;
		}

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		Value& operator[] (size_t i) {
			return _array[i];
		}

		/** Subscript operator, access an element by index.
		@param i index of the element to access
		*/
		const Value& operator[] (size_t i) const {
			return _array.at(i);
		}

		/** Retrieves the starting iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator begin() const {
			return _array.begin();
		}

		/** Retrieves the ending iterator (const).
		@remark mainly for printing
		*/
		std::vector<Value>::const_iterator end() const {
			return _array.end();
		}

		/** Retrieves the starting iterator. */
		std::vector<Value>::iterator begin() {
			return _array.begin();
		}

		/** Retrieves the ending iterator */
		std::vector<Value>::iterator end() {
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

	protected:

		/** Inner container. */
		std::vector<Value> _array;

	};

	inline
		void swap(Array &a, Array &b)noexcept {
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


#endif // JSON_ARRAY_H_