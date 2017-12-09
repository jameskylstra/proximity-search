#include "trie.h"
#include <cctype>
#include <fstream>
using namespace std;

bool Trie::InsensitiveNode::hasIndex(int index) {
    for (int i = 0; i < indices.size(); i++)
	if (indices[i] == index) return true;
    return false;
}

Trie::InsensitiveNode::InsensitiveNode() {
    isWord = false;
    for (int i = 0; i < 26; i++)
	branches[i] = NULL;
}

Trie::InsensitiveNode::~InsensitiveNode() {}

void Trie::InsensitiveNode::addChild(int index) {
    InsensitiveNode* child = new InsensitiveNode;
    branches[index] = child;
}

Trie::Trie() {
    size = 0;
    root = new InsensitiveNode;
}

Trie::Trie(string filename) {
    size = 0;
    this->filename = filename;
    root = new InsensitiveNode;
    ifstream in(filename);
    string word;
    int index = 0;
    while (in >> word) {
	add(word, index);
	index++;
    }
    in.close();
}

Trie::~Trie() {
    freeInsTrie(root);
}

void Trie::freeInsTrie(InsensitiveNode* rt) {
    if (rt == NULL) return;
    for (int i = 0; i < 26; i++)
	freeInsTrie(rt->branches[i]);
    delete rt;
}

void Trie::add(string word, int file_index) {
    int length = word.size();
    InsensitiveNode* inPtr = root;
    int index = 0;
    while (index < length) {
	if (isalpha(word[index])) {
	    if (inPtr->branches[ltrToInd(word[index])] == NULL)  	//There's no child there yet
	        inPtr->addChild(ltrToInd(word[index]));
	    inPtr = inPtr->branches[ltrToInd(word[index])];
	}
    	index++;
    }
    if (!inPtr->isWord) size++;
    inPtr->isWord = true;
    inPtr->addIndex(file_index);
}


int Trie::ltrToInd(char ltr) const {
    return toupper(ltr) - 65;
}
    
bool Trie::has(string word) const {
    int length = word.size();
    InsensitiveNode* inPtr = root;
    for (int i = 0; i < length; i++) {
	if (isalpha(word[i])) {
	    if (inPtr->branches[ltrToInd(word[i])] == NULL)
	        return false;
	    inPtr = inPtr->branches[ltrToInd(word[i])];
	}
    }
    if (inPtr->isWord)
	return true;
    return false;
}

Trie::InsensitiveNode* Trie::getWord(string word) {
    int length = word.size();
    InsensitiveNode* inPtr = root;
    for (int i = 0; i < length; i++) {
	if (isalpha(word[i])) {
	    if (inPtr->branches[ltrToInd(word[i])] == NULL)
		return NULL;
	    inPtr = inPtr->branches[ltrToInd(word[i])];
	}
    }
    if (inPtr->isWord)
	return inPtr;
    return NULL;
}

bool Trie::proxSearch(int prox, string word1, string word2) {
    InsensitiveNode* w1_node = getWord(word1);
    InsensitiveNode* w2_node = getWord(word2);
    if (w1_node == NULL || w2_node == NULL)
	return false;	//one or both words isn't in the file, so false
    return isProx(prox, w1_node->indices, w2_node->indices);
}

bool Trie::isProx(int prox, vector<int> indices1, vector<int> indices2) {
    //returns true if any index in indices2 is within prox
    //of any index in indices1.  Assumes that indices2 and
    //indices1 are both sorted low to high.
    int tracker1 = 0;
    int tracker2 = 0;
    int size1 = indices1.size();
    int size2 = indices2.size();
    while (tracker1 < size1 && tracker2 < size2) { 
	if (indices2[tracker2] - indices1[tracker1] <= prox &&
		indices2[tracker2] - indices1[tracker1] >= -prox) {
	    return true;
	} else if (indices1[tracker1] < indices2[tracker2]) {
	    tracker1++;
	} else {
	    tracker2++;
	}
    }
    return false;
} 
    
    
