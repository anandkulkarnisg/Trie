#include<iostream>
#include<string>
#include<fstream>
#include<chrono>

#include "Trie.h"

using namespace std;

// Source file words.txt taken from https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt [ Had to run dos2unix coversion ].

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	ifstream filestream("words.txt");
	string text;

	auto startPoint=chrono::high_resolution_clock::now();

    while(!filestream.eof())
    {
      getline(filestream,text);
      sampleTrie.insertWord(text);
    }

    auto endPoint=chrono::high_resolution_clock::now();
    auto milliSecDuration = chrono::duration_cast<chrono::milliseconds>(endPoint - startPoint).count();
    cout << "Total Time Taken to insert " << sampleTrie.getTrieWordCount() << " is = " << milliSecDuration << " MilliSeconds." << endl;

    vector<string> allTrieWords;
    size_t size = sampleTrie.getTrieWordCount();
    allTrieWords.reserve(size);

    startPoint=chrono::high_resolution_clock::now();
    sampleTrie.getAllTrieWords(allTrieWords);
    endPoint=chrono::high_resolution_clock::now();
    milliSecDuration = chrono::duration_cast<chrono::milliseconds>(endPoint - startPoint).count();
    cout << "Total Time Taken to fetch all " << sampleTrie.getTrieWordCount() << " words is = " << milliSecDuration << " MilliSeconds." << endl;

    filestream.close();
    return(0);
}
