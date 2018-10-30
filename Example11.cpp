#include<iostream>
#include<string>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	sampleTrie.insertWord("a");
	sampleTrie.insertWord("ab");
	sampleTrie.insertWord("abc");

	cout << sampleTrie.getWordCountByPrefix("a") << endl;
	cout << sampleTrie.getWordCountByPrefix("ab") << endl;
	cout << sampleTrie.getWordCountByPrefix("abc") << endl;

	return (0);
}

