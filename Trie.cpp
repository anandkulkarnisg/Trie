/*
 * Trie.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: anand
 */

#include<iostream>
#include<string>
#include<map>

#include "Trie.h"

using namespace std;

Trie::Trie() : m_root(new TrieNode()) 
{
}

void Trie::insertWord(const std::string& word) 
{
	if (word.empty())
		return;

	shared_ptr<TrieNode> currNode = m_root;
	shared_ptr<TrieNode> newNode;
	for (unsigned int i = 0; i < word.length(); ++i) 
	{
		if (currNode->m_children.empty()) 
		{
			newNode = shared_ptr<TrieNode>(new TrieNode());
			++m_counter;
			currNode->m_children[word[i]] = newNode;
		} 
		else 
		{
			const auto& iter = currNode->m_children.find(word[i]);
			if (iter == currNode->m_children.end()) 
			{
				newNode = shared_ptr<TrieNode>(new TrieNode());
				++m_counter;
				currNode->m_children[word[i]] = newNode;
			} 
			else
				newNode = iter->second;
		}
		currNode = newNode;
	}
	newNode->m_isComplete = true;
}

bool Trie::isWord(const std::string& word) 
{
	if (word.empty())
		return (false);

	shared_ptr<TrieNode> currNode = m_root;
	for (unsigned int i = 0; i < word.size(); ++i) 
	{
		const auto& iter = currNode->m_children.find(word[i]);
		if (iter == currNode->m_children.end())
			return (false);
		else
			currNode = iter->second;
	}
	return (currNode->m_isComplete);
}

pair<bool, size_t> Trie::deleteWord(const std::string& word) 
{
	size_t modifyCounter=0;
	recursiveDelete(m_root, word, modifyCounter);
	if(modifyCounter>0)
		return(make_pair(true, modifyCounter));
	return(make_pair(false, modifyCounter));
}

bool Trie::recursiveDelete(shared_ptr<TrieNode> current, const std::string& word, size_t& modifyCounter, const size_t& index)
{
	if (index == word.length()) 
	{
		if (!current->m_isComplete)
			return (false);

		current->m_isComplete = false;
		++modifyCounter;
		return (current->m_children.empty());
	}

	char ch = word[index];
	const auto& iter = current->m_children.find(ch);
	if (iter == current->m_children.end())
		return (false);

	bool shouldDeleteCurrentNode = recursiveDelete(iter->second, word, modifyCounter, index + 1);
	if (shouldDeleteCurrentNode) 
	{
		current->m_children.erase(iter);
		--m_counter;
		++modifyCounter;
		//return true if no mappings are left in the map.
		return (current->m_children.empty());
	}
	return (false);
}

bool Trie::isEmpty()
{
	return(m_root->m_children.empty());
}

long Trie::getTrieSize()
{
	//cout << sizeof(char) << " , " << sizeof(TrieNode) << "," << sizeof(shared_ptr<TrieNode>) << '\n';
	return(m_counter*sizeof(TrieNode));	
}

Trie::~Trie()
{
}
