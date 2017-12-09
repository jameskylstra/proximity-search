#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "trie.h"
#include "../args/flags.h"
using namespace std;

const string flag_ids[] = {"-case"};

int main(int argc, char* argv[]) {
    //takes a list of files as arguments
    //then, from the command line, it takes proximity search requests
    //prints out true or false
    assert(argc > 1);
    flags.add(flag_ids, 1);
    if(flags["-case"].isOn()) {
    vector<Trie*> files;
    Trie* trie_ptr;
    for (int i = 1; i < argc; i++) {
	trie_ptr = new Trie(argv[i]);
	files.push_back(trie_ptr);
    }
    int prox;
    string word1;
    string word2;
    bool any_hits;
    while (true)
    {
	any_hits = false;
	cin >> prox >> word1 >> word2;
	if (prox == 0) break;
	for (int i = 0, n = files.size(); i < n; i++) {
	    if (files[i]->proxSearch(prox, word1, word2)) {
		if (!any_hits) {
		    cout << word1 << " is within " << prox <<
			" words of " << word2 << " in:" << endl;
		}
		cout << files[i]->getFilename() << endl;
		any_hits = true;
	    }
	}
	if (!any_hits) {
	    cout << word1 << " is not within " << prox << " words of "
		<< word2 << " in any of the listed files." << endl;
	}
    }
    for (int i = 0; i < files.size(); i++) {
	delete files[i];
    }
}
