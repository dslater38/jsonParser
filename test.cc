#include <iostream>
#include "json.hh"

using namespace std;
using namespace JSON;

int main(int argc, char** argv)
{
    // Load JSON file
    
	for (auto i = 0; i < 1000; ++i) {

		volatile Value v = parse_file("tests/comp.json");
//		cerr << v << endl;
//		cerr << "---" << endl;

		// Build object programmatically
		Object obj;

		obj["foo"] = true;
		obj["bar"] = 3LL;
		obj["bar"] = 3L;
		obj["bar"] = 3;

		Object o;
		o["failure"] = true;
		o["success"] = "no way";

		obj["baz"] = std::move(o);

		Array a;
		a.emplace_back(true);
		a.emplace_back( "asia");
		a.emplace_back("europa");
		a.emplace_back(55LL );
		a.emplace_back(3.12L );
		a.emplace_back(3.12 );

		obj["beer"] = std::move(a);

//		cerr << obj << endl;
	}
    return 0;
}