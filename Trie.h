#include<iostream>
#include<string>
#include<map>
#include<utility>
#include<memory>
#include<shared_mutex>
#include<mutex>
#include<vector>

#ifndef Trie_H
#define Trie_H

class Trie
{
private:

	// TrieNode is a core node structure of the Trie.
	class TrieNode
	{
	public:
		std::map<char, std::shared_ptr<TrieNode>> m_children;
		bool m_isComplete;
		long m_prefixCount;		// This stores sum of all words at this point as a prefix. Helps in quicker answering of the question how many words are there with a given prefix much faster!
		TrieNode() : m_isComplete(false) , m_prefixCount(1)
		{
		}
	};

	// Root node of the Trie Data Structure.
	std::shared_ptr<TrieNode> m_root;
	std::shared_mutex m_mutex;

	size_t m_counter=0;
	size_t m_wordCount=0;

	bool recursiveDelete(std::shared_ptr<TrieNode>, const std::string&, size_t& , const size_t& = 0);
	void recursiveWordSearch(const std::shared_ptr<TrieNode>, const std::string&, std::vector<std::string>&);
	bool isValidPrefixInternal(const std::string&, std::shared_ptr<TrieNode>&);

	// debug func use sparingly for case by case basis.
	void debugFunc();

public:
	Trie();
	Trie(const Trie&)=delete;
	Trie& operator=(const Trie&)=delete;

	std::pair<bool, size_t> insertWord(const std::string&);
	bool isWord(const std::string&);
	std::pair<bool, size_t> deleteWord(const std::string&);
	bool isValidPrefix(const std::string&);
	void getWordsByPrefix(const std::string&, std::vector<std::string>&);
	long getWordCountByPrefix(const std::string& prefix);
	void getAllTrieWords(std::vector<std::string>&);
	bool isEmpty();
	long getTrieSize();
	long getTrieWordCount();
	void resetTrie();
	~Trie();
};

#endif
