#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<fstream>
#include<algorithm>
#include<set>

#include "Trie.h"

using namespace std;

Trie sampleTrie;

void insertIntoTrie(const vector<string>& inputDataSource, const int& startIdx)
{
	size_t start = startIdx * 10;
	size_t end = start + 9;

	for (unsigned int i = start; i <= end; ++i)
		sampleTrie.insertWord(inputDataSource[i]);
}

int main(int argc, char* argv[])
{
	const string inputFileName = "Example13.data.txt";
	ifstream fileStream(inputFileName);
	vector<string> inputWordList;
	string textLine;
	inputWordList.reserve(100);

	// Part 1 : Load the data into vector.
	while (!fileStream.eof())
	{
		getline(fileStream, textLine);
		inputWordList.emplace_back(textLine);
	}

	// Part 2 : spin off the threads which will try to insert the specific 10 items as per their id into the Trie. At end the Trie must have 100 words in it.
	// This is to test and prove that it is threadsafe and has no loss of data.

	const unsigned int numTestRuns = 100;
	const unsigned int threadPoolSize = 10;

	set<int> trieCounts;
	vector<thread> testThreadPool;
	testThreadPool.reserve(threadPoolSize);

	// Part 3 : Join the worker threads and verify the results.
	for (unsigned int i = 0; i <numTestRuns; ++i)
	{
		// spin off the threads.
		for (unsigned int j = 0; j < threadPoolSize; ++j)
			testThreadPool.emplace_back(thread(&insertIntoTrie, cref(inputWordList), j));

		// Join the threads.
		for_each(testThreadPool.begin(), testThreadPool.end(), [&](thread& threadItem){threadItem.join();});

		// store the result into set.
		trieCounts.insert(sampleTrie.getTrieWordCount());

		// clear the Trie and thread pool.
		sampleTrie.resetTrie();
		testThreadPool.clear();
	}

	// Print the results.
	cout << "The size of trieCounts set is = " << trieCounts.size() << endl;
	cout << "The size of trie in each insertion is = " << *trieCounts.begin() << endl;
	return (0);
}
