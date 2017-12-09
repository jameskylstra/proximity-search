#include "flags.h"
using namespace std;

void Flags::gather(int argc, char* argv[]) {
    //goes through the argv and checks whether it's a flag, based on
    //whether it starts with leader.  If so, it checks whether it's a
    //recognized flag in the flag_map.  If so, it turns that flag on.
    //If not, it prints an error message to stderr and exits.
    bool bad = false;
    for (int i = 0; i < argc; i++) {
	if (isFlag(argv[i])) {
	    if (flag_map.count(argv[i]) > 0) {
		flag_map.at(argv[i]).turnOn();
	    } else {	//It's not a recognized flag, so throw an error
		cerr << "Unrecognized flag: " << argv[i] << endl;
		bad = true;
	    }
	}
    }
    if (bad) {
	cerr << "Aborting..." << endl;
	exit(1);
    }
}

Flags flags;
