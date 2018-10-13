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
	if (word.size() == 0)
		return;

	TrieNode* currNode = m_root;
	TrieNode* newNode;
	for (unsigned int i = 0; i < word.length(); ++i) 
	{
		if (currNode->m_children.size() == 0) 
		{
			newNode = new TrieNode();
			currNode->m_children[word[i]] = newNode;
		} 
		else 
		{
			const auto& iter = currNode->m_children.find(word[i]);
			if (iter == currNode->m_children.end()) 
			{
				newNode = new TrieNode();
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
	if (word.size() == 0)
		return (false);

	TrieNode* currNode = m_root;
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

bool Trie::recursiveDelete(TrieNode* current, const std::string& word, size_t& modifyCounter, const size_t& index)
{
	if (index == word.length()) 
	{
		if (!current->m_isComplete)
			return (false);

		current->m_isComplete = false;
		++modifyCounter;
		return (current->m_children.size() == 0);
	}

	char ch = word[index];
	const auto& iter = current->m_children.find(ch);
	if (iter == current->m_children.end())
		return (false);

	bool shouldDeleteCurrentNode = recursiveDelete(iter->second, word, modifyCounter, index + 1);
	if (shouldDeleteCurrentNode) 
	{
		current->m_children.erase(iter);
		++modifyCounter;
		//return true if no mappings are left in the map.
		return (current->m_children.size() == 0);
	}
	return (false);
}
