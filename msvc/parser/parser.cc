#ifdef NDEBUG
#pragma inline_depth(255)
#pragma inline_recursion(on)
#endif

#include "json.hh"
#include <pegtl.hh>
#include <pegtl/contrib/json.hh>
#include <pegtl/contrib/changes.hh>

#include "json_unescape.hh"
#include "json_errors.hh"

#include "json_st.hh"

namespace JSON {

	using namespace examples;

	namespace Parser {

		struct result_state
		{
			result_state() = default;

			result_state(const result_state &) = delete;
			void operator= (const result_state &) = delete;

			Value result;
		};
		// Action class for the simple cases...

		template< typename Rule > struct value_action : unescape_action< Rule > {};

		struct string_state
			: public unescape_state_base
		{
			void success(result_state & result)
			{
				result.result = std::move(unescaped);
			}
		};

		template<>
		struct value_action< pegtl::json::null >
		{
			template< typename Input >
			static void apply(const Input &, result_state & result)
			{
				result.result = Value{};
			}
		};

		template<>
		struct value_action< pegtl::json::true_ >
		{
			template< typename Input >
			static void apply(const Input &, result_state & result)
			{
				result.result = true;
			}
		};

		template<>
		struct value_action< pegtl::json::false_ >
		{
			template< typename Input >
			static void apply(const Input &, result_state & result)
			{
				result.result = false;
			}
		};

		template<>
		struct value_action< pegtl::json::number >
		{
			template< typename Input >
			static void apply(const Input & in, result_state & result)
			{
				result.result = std::stold(in.string());  // NOTE: stold() is not quite correct for JSON but we'll use it for this simple example.
			}
		};

		// State and action classes to accumulate the data for a JSON array.

		struct array_state
			: public result_state
		{
			Array array{};

			void push_back()
			{
				array.emplace_back(std::move(result));
			}

			void success(result_state & result)
			{
				if (this->result.type() != ValueType::NIL) {
					push_back();
				}
				result.result = std::move(array);
			}
		};

		template< typename Rule > struct array_action : pegtl::nothing< Rule > {};

		template<>
		struct array_action< pegtl::json::value_separator >
		{
			template< typename Input >
			static void apply(const Input &, array_state & result)
			{
				result.push_back();
			}
		};

		// State and action classes to accumulate the data for a JSON object.

		struct object_state
			: public result_state
		{
			std::string unescaped;
			Object object{};

			void insert()
			{
				object.emplace(std::move(unescaped), std::move(result));
				unescaped.clear();
			}

			void success(result_state & result)
			{
				if (this->result.type() != ValueType::NIL) {
					insert();
				}
				result.result = std::move(object);
			}
		};

		template< typename Rule > struct object_action : unescape_action< Rule > {};

		template<>
		struct object_action< pegtl::json::value_separator >
		{
			template< typename Input >
			static void apply(const Input &, object_state & result)
			{
				result.insert();
			}
		};


		// Put together a control class that changes the actions and states as required.

		template< typename Rule > struct control : errors< Rule > {};  // Inherit from json_errors.hh.

		template<> struct control< pegtl::json::value > : pegtl::change_action< pegtl::json::value, value_action, errors > {};
		template<> struct control< pegtl::json::string::content > : pegtl::change_state< pegtl::json::string::content, string_state, errors > {};
		template<> struct control< pegtl::json::array::content > : pegtl::change_state_and_action< pegtl::json::array::content, array_state, array_action, errors > {};
		template<> struct control< pegtl::json::object::content > : pegtl::change_state_and_action< pegtl::json::object::content, object_state, object_action, errors > {};

		struct grammar : pegtl::must< pegtl::json::text, pegtl::eof > {};
	}
}

const char *jsonS = "{ \"a\" : 123, \"b\" : \"\\uD83D\\uDE02\"}";

int main(int argc, char ** argv)
{
	JSON::Parser::result_state result;
	// pegtl::file_parser("tests/comp.json").parse<JSON::Parser::grammar, pegtl::nothing, JSON::Parser::control >(result);
	pegtl::string_parser(jsonS, "test").parse<JSON::Parser::grammar, pegtl::nothing, JSON::Parser::control >(result);
	std::cout << result.result << std::endl;
	return 0;
}