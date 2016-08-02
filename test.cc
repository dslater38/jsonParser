#include <iostream>
#include "json.hh"

using namespace std;
using namespace JSON;


int main(int argc, char** argv)
{
    // Load JSON file
    
	for (auto i = 0; i < 20; ++i) {

		using O = JSON::Object;
		using A = JSON::Array;

		auto str = std::string{"{\"a\":5,\"b\":[1,2,3]}"};

		Value v = parse_file("tests/comp.json");
		// cerr << v << endl;
		// cerr << "---" << endl;

		auto Nil = Value{};
		auto IntVal = Value{ 45LL };
		auto i1 = Value{ 23 };
		auto i2 = Value{ (short)45 };
		auto ie = Value{ 0 };
		auto fVal = Value{ 3.1415926536 };
		auto sVal = Value{ "string value" };

		// Build object programmatically
		const Value val = Value{ O{
			"foo",		true,
			"bar",		3LL,
			"baz",		O{	"failure", true,
							"success", "no way"	},
			"beer",		A{ true, "asia", "europa", 55LL, 3.12L, 3.12 },
			"foobar",	"foobar"
		} };

		// Build object programmatically
		const Value val2{ { O{
			"foo",		true,
			"bar",		3LL,
			"baz",		O{ "failure", true,
			"success", "no way" },
			"beer",		A{ true, "asia", "europa", 55LL, 3.12L, 3.12 },
			"foobar",	"foobar"
		} } };


		auto obj2 = O{
			"bar" , 45L,
			"bool", true,
			"arr", A{2,3,"str",45.6}
		};

		auto foo = obj2["bar"];

		char *foom = "baba";

		obj2["baz"] = nullptr;

		// std::cout << obj2 << std::endl;

		//obj["foo"] = true;
		//obj["bar"] = 3LL;
		//obj["bar"] = 3L;
		//obj["bar"] = 3;

//		Object o{
//			"failure", true,
//			"success", "no way"
//		};
//		o["failure"] = true;
//		o["success"] = "no way";

//		obj["baz"] = std::move(o);

		// Array a{ Value{true}, Value{"asia"}, Value{"europa"}, Value{55LL}, Value{3.12L}, Value{3.12} };
//		Array a{ true, "asia", "europa", 55LL, 3.12L, 3.12 };
		//a.reserve(6);
		//a.emplace_back(true);
		//a.emplace_back( "asia");
		//a.emplace_back("europa");
		//a.emplace_back(55LL );
		//a.emplace_back(3.12L );
		//a.emplace_back(3.12 );

		// obj["beer"] = std::move(a);

		// cerr << val << endl;
	}
    return 0;
}