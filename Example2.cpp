#include<iostream>
#include<string>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	sampleTrie.insertWord("anand");
	sampleTrie.insertWord("anant");
	cout << "Trie size = " << sampleTrie.getTrieSize() << " bytes" << endl;
	return(0);
}
