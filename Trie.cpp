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

	unique_lock<shared_mutex> exclusiveLock(m_mutex);
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

	shared_lock<shared_mutex> readLock(m_mutex);
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
	{
		unique_lock<shared_mutex> exclusiveLock(m_mutex);
		recursiveDelete(m_root, word, modifyCounter);
	}
	if(modifyCounter>0)
		return(make_pair(true, modifyCounter));
	return(make_pair(false, modifyCounter));
}

bool Trie::recursiveDelete(shared_ptr<TrieNode> current, const std::string& word, size_t& modifyCounter, const size_t& index)
{
	// Do not take any locks inside this method. This method is called from deleteWord which is already protected via write Lock!
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
	shared_lock<shared_mutex> readLock(m_mutex);
	return(m_root->m_children.empty());
}

long Trie::getTrieSize()
{
	shared_lock<shared_mutex> readLock(m_mutex);
	return(m_counter*sizeof(TrieNode));	
}

Trie::~Trie()
{
	// We dont need to release anything here since shared_ptr will destroy the nodes that are allocated on heap!
}
