#include<iostream>
#include<string>
#include<thread>
#include<vector>

#include "Trie.h"

using namespace std;

Trie sampleTrie;

void worker(const vector<string>& wordList, const bool& part)
{
	size_t lIdx=0;
	size_t uIdx=wordList.size()/2-1;

	if(part)
	{
		size_t size=wordList.size()/2;
		lIdx+=size;
		uIdx+=size;
	}
	
	for(unsigned int i=lIdx; i<=uIdx; ++i)
	{
		cout << "attempting to insert the word = " << wordList[i] << endl; 
		sampleTrie.insertWord(wordList[i]);	
	}
}


int main(int argc, char* argv[])
{
	vector<string> wordList = { "anand", "peter", "thomas", "robert", "Alex", "Jones", "david", "michael" };
	thread t1(&worker, cref(wordList), false);
	thread t2(&worker, cref(wordList),  true);
	
	t1.join();
	t2.join();

	for(const auto& word : wordList)
		cout << "The validation status of word = " << word << " is = " << sampleTrie.isWord(word) << endl;

	cout << "The Trie size = " << sampleTrie.getTrieSize() << " bytes." << endl;

	return(0);
}
