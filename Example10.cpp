#include<iostream>
#include<string>

#include "Trie.h"

using namespace std;

char intToChar(const int& input)
{
	return (static_cast<char>(input));
}

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	std::string toPrint;
	for (unsigned int i = 97; i < 97 + 26; ++i)
	{
		toPrint += string(1, intToChar(i));
		sampleTrie.insertWord(toPrint);
	}

	toPrint.clear();
	for (unsigned int i = 97; i < 97 + 26; ++i)
	{
		toPrint += string(1, intToChar(i));
		cout << "The number of words with prefix = " << toPrint << " is = " << sampleTrie.getWordCountByPrefix(toPrint) << endl;
	}

	toPrint.clear();
	for (unsigned int i = 97; i < 97 + 26; ++i)
	{
		toPrint += string(1, intToChar(i));
		sampleTrie.deleteWord(toPrint);
		cout << "The number of words with prefix = " << toPrint << " is = " << sampleTrie.getWordCountByPrefix(toPrint) << endl;
	}
	return (0);
}

