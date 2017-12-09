list_test: list.h list_test.cpp list.cpp
	clang++ list.cpp list_test.cpp -o list_test

list_test_db: list.h list_test.cpp list.cpp
	clang++ -O0 -g list.cpp list_test.cpp -o list_test_db

hash_test: hashtable.cpp hashtable.h hash_test.cpp list.h list.cpp
	clang++ list.cpp hashtable.cpp hash_test.cpp -o hash_test

prox_test: hashtable.h list.h list.cpp hashtable.cpp prox.h prox.cpp prox_test.cpp
	clang++ list.cpp hashtable.cpp prox.cpp prox_test.cpp -o prox_test

prox_test2: hashtable.h list.h prox.h hashtable.cpp list.cpp prox.cpp 
	clang++ list.cpp hashtable.cpp prox.cpp prox_test2.cpp -o prox_test2
	
prox_test2_db: hashtable.h list.h prox.h hashtable.cpp list.cpp prox.cpp prox_test2.cpp
	clang++ -O0 -g list.cpp hashtable.cpp prox.cpp prox_test2.cpp -o prox_test2_db
	
prox_search: prox.cpp hashtable.cpp list.cpp prox_search.cpp prox.h list.h
	clang++ prox_search.cpp prox.cpp hashtable.cpp list.cpp -o prox_search

prox.cpp: prox.h hashtable.h list.h hashtable.cpp list.cpp

prox_search2: prox.cpp prox_search2.cpp
	clang++ prox_search2.cpp prox.cpp hashtable.cpp list.cpp -o prox_search2

trie_prox: trie.h trie.cpp trie_prox.cpp
	clang++ trie_prox.cpp trie.cpp -o trie_prox

trie_prox_db: trie.h trie.cpp trie_prox.cpp
	clang++ -O0 -g trie_prox.cpp trie.cpp -o trie_prox_db

