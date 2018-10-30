#include<iostream>
#include<string>
#include<vector>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	vector<string> wordList = { "peter", "peterson" };

	for(const auto& word : wordList)
		sampleTrie.insertWord(word);

	const string testPrefix = "peter";
	cout << sampleTrie.getWordCountByPrefix(testPrefix) << endl;
	pair<bool, size_t> resultPair = sampleTrie.deleteWord("peter");
	cout << resultPair.first << " , " << resultPair.second << endl;
	cout << "after deletion status\n" << endl;
	cout << sampleTrie.getWordCountByPrefix(testPrefix) << endl;
	return(0);
}
