#include<iostream>
#include<vector>
#include<string>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	vector<string> wordList = { "pet", "peter", "petrol", "peterson", "magic", "rocks" };

	for(const auto& word : wordList)
		sampleTrie.insertWord(word);

	vector<string> prefixList = { "p", "pe", "pet", "pete", "peter", "m", "r" };

	/*
	for(const auto& prefix : prefixList)
		cout << "prefix = " << prefix << ", wordCount = " << sampleTrie.getWordCountByPrefix(prefix) << endl;
	*/

	cout << "prefix = " << "pete" << ", wordCount = " << sampleTrie.getWordCountByPrefix("pete") << endl;
	vector<string> prefixWordList;
	prefixWordList.reserve(10);
	sampleTrie.getWordsByPrefix("pete", prefixWordList);
	cout << "size = " << prefixWordList.size() << endl;

	/*
	sampleTrie.deleteWord("peter");

	for(const auto& prefix : prefixList)
		cout << "prefix = " << prefix << ", wordCount = " << sampleTrie.getWordCountByPrefix(prefix) << endl;

	sampleTrie.deleteWord("peterson");

	for(const auto& prefix : prefixList)
			cout << "prefix = " << prefix << ", wordCount = " << sampleTrie.getWordCountByPrefix(prefix) << endl;


	vector<string> allTrieWords;
	allTrieWords.reserve(10);

	sampleTrie.getAllTrieWords(allTrieWords);
	for(const auto& word : allTrieWords)
		cout << word << endl;
	*/

	return(0);
}
