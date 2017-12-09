#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <vector>
using namespace std;

class Trie {
    struct InsensitiveNode {
	bool isWord;
	InsensitiveNode* branches[26];
	void addChild(int index);
	vector<int> indices;
	int numOccurrences() { return indices.size(); }
	void addIndex(int index) { indices.push_back(index); }
	bool hasIndex(int index);
	InsensitiveNode();
	~InsensitiveNode();
    }* root;
    void freeInsTrie(InsensitiveNode* rt);
    int ltrToInd(char ltr) const;		//returns index from 0 to 25 for a given letter
    bool isProx(int prox, vector<int> indices1, vector<int> indices2);
    int size;
    string filename;
  public:
    void add(string word, int file_index);
    bool has(string word) const;
    int getSize() const { return size; }
    string getFilename() const { return filename; }
    InsensitiveNode* getWord(string word);
    bool proxSearch(int prox, string word1, string word2);
    Trie();
    Trie(string filename);
    ~Trie();
};

#endif //TRIE_H
