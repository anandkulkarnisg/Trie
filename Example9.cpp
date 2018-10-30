#include<iostream>
#include<string>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	// case 1 :
	cout << "case 1 : " << endl;
	{
		Trie sampleTrie;
		sampleTrie.insertWord("a");
		sampleTrie.insertWord("ab");
		sampleTrie.insertWord("abc");
		cout << "The prefix count for a = " << sampleTrie.getWordCountByPrefix("a") << endl;
		cout << "The prefix count for ab = " << sampleTrie.getWordCountByPrefix("ab") << endl;
		cout << "The prefix count for abc = " << sampleTrie.getWordCountByPrefix("abc") << endl;
	}

	// case 2 :
	cout << "case 2 : " << endl;
	{
		Trie sampleTrie;
		sampleTrie.insertWord("ab");
		sampleTrie.insertWord("abc");
		cout << "The prefix count for a = " << sampleTrie.getWordCountByPrefix("a") << endl;
		cout << "The prefix count for ab = " << sampleTrie.getWordCountByPrefix("ab") << endl;
		cout << "The prefix count for abc = " << sampleTrie.getWordCountByPrefix("abc") << endl;
	}

	// Case 3 :
	cout << "case 3 : " << endl;
	{
		Trie sampleTrie;
		sampleTrie.insertWord("ab");
		sampleTrie.insertWord("abc");
		sampleTrie.insertWord("abcd");
		sampleTrie.insertWord("abcde");
		cout << "The prefix count for ab = " << sampleTrie.getWordCountByPrefix("ab") << endl;
		cout << "The prefix count for abc = " << sampleTrie.getWordCountByPrefix("abc") << endl;
		cout << "The prefix count for abcd = " << sampleTrie.getWordCountByPrefix("abcd") << endl;
		cout << "The prefix count for abcde = " << sampleTrie.getWordCountByPrefix("abcde") << endl;
	}

	// Case 4 :
	cout << "case 4 : " << endl;
	{
		Trie sampleTrie;
		sampleTrie.insertWord("abcd");
		sampleTrie.insertWord("abcde");
		cout << "The prefix count for abcd = " << sampleTrie.getWordCountByPrefix("abcd") << endl;
		cout << "The prefix count for abcde = " << sampleTrie.getWordCountByPrefix("abcde") << endl;
	}

	return(0);
}
