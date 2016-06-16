#include <iostream>
#include "json.hh"

using namespace std;
using namespace JSON;


int main(int argc, char** argv)
{
    // Load JSON file
    
	for (auto i = 0; i < 2; ++i) {

		Value v = parse_file("tests/comp.json");
		//cerr << v << endl;
		cerr << "---" << endl;

		// Build object programmatically
		const Object obj{
			"foo",			true,
			"bar",			3LL,
			"baz",			Object{	"failure", true,
									"success", "no way"	},
			"beer",			Array{ true, "asia", "europa", 55LL, 3.12L, 3.12 },
			"foobar", "foobar"
		};

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

		cerr << obj << endl;
	}
    return 0;
}