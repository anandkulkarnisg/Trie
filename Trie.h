#include<iostream>
#include<string>
#include<map>
#include<utility>
#include<memory>

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
		TrieNode() : m_isComplete(false)
		{
		}
	};

	// Root node of the Trie Data Structure.
	std::shared_ptr<TrieNode> m_root;

public:
	Trie();
	Trie(const Trie&)=delete;
	Trie& operator=(const Trie&)=delete;

	void insertWord(const std::string&);
	bool isWord(const std::string&);
	std::pair<bool, size_t> deleteWord(const std::string&);
	bool recursiveDelete(std::shared_ptr<TrieNode>, const std::string&, size_t& , const size_t& = 0);
	bool isEmpty();
	~Trie();
};

#endif
