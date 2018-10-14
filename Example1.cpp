#include<iostream>
#include<string>
#include<vector>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> wordList = { "anand", "anant", "deepti", "robert", "zebra" };
	Trie sampleTrie;

	for (const auto& word : wordList)
		sampleTrie.insertWord(word);

	vector<string> invalidWordList = { "magic", "tickle", "trickster", "buggy" };
	for (const auto& word : wordList)
	{
		if(sampleTrie.isWord(word))
			cout << "word = " << word << " is a valid Word as per Trie." << endl;
		else
			cout << "word = " << word << " is an invalid Word as per Trie." << endl;
	}

	for (const auto& word : invalidWordList)
	{
		if(sampleTrie.isWord(word))
			cout << "word = " << word << " is a valid Word as per Trie." << endl;
		else
			cout << "word = " << word << " is an invalid Word as per Trie." << endl;
	}

	vector<string> testWords = { "anand", "AbraCaDabra" };
	for(const auto& testWord : testWords)
	{
		bool isWordStatus = sampleTrie.isWord(testWord);
		cout << "The isWord status for " << testWord << " = " << isWordStatus << endl;
		pair<bool, size_t> deleteStatus = sampleTrie.deleteWord(testWord);
		cout << "The deletionStatus = " << deleteStatus.first << endl;
		if(deleteStatus.first)
			cout << "The number of TrieNodes deleted were = " << deleteStatus.second << endl;
		else
			cout << "Nothing was delete as indicated by " << deleteStatus.second << endl;
		isWordStatus = sampleTrie.isWord(testWord);
		cout << "The isWord status for " << testWord << " = " << isWordStatus << endl;
	}

	return (0);
}
