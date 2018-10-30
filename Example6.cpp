#include<iostream>
#include<string>
#include<vector>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	vector<string> wordList = { "pet", "peter", "peterson", "petrol" };

	for(const auto& word : wordList)
		sampleTrie.insertWord(word);

	const string testPrefix = "pe";
	cout << sampleTrie.getWordCountByPrefix(testPrefix) << endl;

	for(const auto& deleteWord : wordList)
	{
		sampleTrie.deleteWord(deleteWord);
		cout << sampleTrie.getWordCountByPrefix(testPrefix) << endl;
	}

	return(0);
}
