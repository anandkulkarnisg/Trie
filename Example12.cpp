#include<iostream>
#include<string>
#include<vector>

#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Test case 1 : Attempt a duplicate word insertion.
	{
		Trie sampleTrie;
		pair<bool, size_t> insertionStatus;

		// Insert the word first time.
		insertionStatus = sampleTrie.insertWord("anand");
		cout << "insertion status = " << insertionStatus.first << " , no of amends made to Trie = " << insertionStatus.second << endl;

		// Attempt a duplicate insertion.
		insertionStatus = sampleTrie.insertWord("anand");
		cout << "insertion status = " << insertionStatus.first << " , no of amends made to Trie = " << insertionStatus.second << endl;

		// Defend against duplicate insertion.
		cout << sampleTrie.getWordCountByPrefix("an") << endl;
	}

	// Test case 2 : insertion of two words with same prefix.
	{
		Trie sampleTrie;
		pair<bool, size_t> insertionStatus, deletionStatus;
		vector<string> wordList = { "peter", "peterson" };

		for (const auto& word : wordList)
		{
			insertionStatus = sampleTrie.insertWord(word);
			cout << "inserting the word = " << word << endl;
			cout << "insertion status = " << insertionStatus.first << " , no of amends made to Trie = " << insertionStatus.second << endl;
		}

		for (const auto& word : wordList)
		{
			cout << "attempting to delete word = " << word << endl;
			deletionStatus = sampleTrie.deleteWord(word);
			cout << "deletion status = " << deletionStatus.first << " , no of amends made to Trie = " << deletionStatus.second << endl;
		}

		cout << "Trie empty status = " << sampleTrie.isEmpty() << endl;
	}
	return (0);
}

