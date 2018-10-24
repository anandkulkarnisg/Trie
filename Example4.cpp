#include<iostream>
#include<string>
#include<vector>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	sampleTrie.insertWord("pet");
	sampleTrie.insertWord("peter");
	sampleTrie.insertWord("peterson");
	sampleTrie.insertWord("petrol");
	sampleTrie.insertWord("petronas");

	sampleTrie.insertWord("miguel");
	sampleTrie.insertWord("columbia");
	sampleTrie.insertWord("germany");

	vector<string> wordList = { "pet", "peter", "peterson", "petrol", "petronas", "petulant" };
	for(const auto& iter : wordList)
	{
		if(sampleTrie.isWord(iter))
			cout << "Yes the word = " << iter << " is a complete word." << endl;
		else
			cout << "No the word = " << iter << " is not a valid complete word." << endl;
	}

	vector<string> prefixWordList;
	prefixWordList.reserve(10);

	string prefix = "pe";
	sampleTrie.getWordsByPrefix(prefix, prefixWordList);
	cout << "The valid words in the Trie for prefix = " << prefix << " are below." << endl;
	for(const auto& iter : prefixWordList)
		cout << iter << endl;

	prefix = "ps";
	vector<string> sampleWordList;
	sampleTrie.getWordsByPrefix(prefix, sampleWordList);
	if(sampleWordList.empty())
		cout << "No such words starting with prefix = " << prefix << " found in the Trie." << endl;

	prefix = "abk";
	if(sampleTrie.isValidPrefix(prefix))
		cout << "The prefix = " << prefix << " is a valid one." << endl;
	else
		cout << "The prefix = " << prefix << " is not a valid." << endl;

	vector<string> allTrieWordList;
	allTrieWordList.reserve(100);

	sampleTrie.getAllTrieWords(allTrieWordList);

	cout << "All the Trie words are listed below" << endl;
	for(const auto& iter : allTrieWordList)
		cout << iter << " , ";
	cout << '\n';


	return(0);
}
