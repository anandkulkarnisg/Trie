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
			newNode->m_prefixCount++;
			++m_counter;
			currNode->m_children[word[i]] = newNode;
		} 
		else 
		{
			const auto& iter = currNode->m_children.find(word[i]);
			if (iter == currNode->m_children.end()) 
			{
				newNode = shared_ptr<TrieNode>(new TrieNode());
				newNode->m_prefixCount++;
				++m_counter;
				currNode->m_children[word[i]] = newNode;
			} 
			else
			{
				newNode = iter->second;
				newNode->m_prefixCount++;
			}
		}
		currNode = newNode;
	}

	newNode->m_isComplete = true;
	++m_wordCount;
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

	bool returnStatus=false;
	if(modifyCounter>0)
		returnStatus=true;
	return(make_pair(returnStatus, modifyCounter));
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

	size_t beforeModifyCounter=modifyCounter;
	bool shouldDeleteCurrentNode = recursiveDelete(iter->second, word, modifyCounter, index + 1);
	if (shouldDeleteCurrentNode) 
	{
		current->m_children.erase(iter);
		current->m_prefixCount--;
		--m_counter;
		++modifyCounter;
		//return true if no mappings are left in the map.
		return (current->m_children.empty());
	}
	else
	{
		if(beforeModifyCounter!=modifyCounter)
			current->m_prefixCount--;
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

bool Trie::isValidPrefixInternal(const string& prefix, shared_ptr<TrieNode>& nodeRef)
{
	shared_lock<shared_mutex> readLock(m_mutex);
	string wordItem;
	std::shared_ptr<TrieNode> current = m_root;

	for(unsigned int i=0; i<prefix.length(); ++i)
	{
		const auto& iter = current->m_children.find(prefix[i]);
		if(iter != current->m_children.end())
		{
			wordItem+=prefix[i];
			current = iter->second;
		}
		else
			return(false);
	}

	if(wordItem!=prefix)
		return(false);

	nodeRef=current;
	return(true);
}

bool Trie::isValidPrefix(const string& prefix)
{
	shared_ptr<TrieNode> nodeRef;
	bool returnStatus = isValidPrefixInternal(prefix, nodeRef);
	return(returnStatus);
}

void Trie::getWordsByPrefix(const string& prefix, vector<string>& wordList)
{
	// This method searches for all valid strings and returns a vector containing those words in the Trie which are having supplied prefix.
	// if none found the vector will be empty.

	shared_lock<shared_mutex> readLock(m_mutex);

	// Check if the prefix is valid only then proceed.
	shared_ptr<TrieNode> prefixNode;
	bool prefixStatus = isValidPrefixInternal(prefix, prefixNode);

	if(!prefixStatus)
		return;

	// Now we have prefix which is valid then all we need to is recursively search all words from this prefix onwards.
	recursiveWordSearch(prefixNode, prefix, wordList);
}

void Trie::recursiveWordSearch(const shared_ptr<TrieNode> node, const string& passedWord, vector<string>& wordList)
{
	if(node->m_isComplete)
		wordList.push_back(passedWord);

	if(node->m_children.size()==0)
		return;

	for(const auto& iter : node->m_children)
		recursiveWordSearch(iter.second, passedWord+iter.first, wordList);
}


// This is a heavy word search algorithm and must not be used frequently. It has only a rare requirment for debugging purpose.
void Trie::getAllTrieWords(vector<string>& wordList)
{
	 // We identify all the characters in the root map as prefixes and then search all words starting with them.
	shared_lock<shared_mutex> readLock(m_mutex);

	 if(m_root->m_children.size()==0)
		 return;

	 vector<string> prefixList;
	 prefixList.reserve(m_root->m_children.size());
	 for(const auto& iter : m_root->m_children)
		 prefixList.emplace_back(string(1,iter.first));

	 vector<string> prefixWordList;
	 prefixWordList.reserve(m_wordCount);

	 for(const auto& iter : prefixList)
	 {
		 prefixWordList.clear();
		 getWordsByPrefix(iter,prefixWordList);
		 copy(prefixWordList.begin(), prefixWordList.end(), back_inserter(wordList));

	 }
}

long Trie::getWordCountByPrefix(const std::string& prefix)
{
	shared_lock<shared_mutex> readLock(m_mutex);
	shared_ptr<TrieNode> nodeRef;
	bool returnStatus = isValidPrefixInternal(prefix, nodeRef);
	if(returnStatus)
		return(nodeRef->m_prefixCount);
	else
		return(0);
}

// Return the number of words inserted in the Trie so far.
long Trie::getTrieWordCount()
{
	shared_lock<shared_mutex> readLock(m_mutex);
	return(m_wordCount);
}


Trie::~Trie()
{
	// We dont need to release anything here since shared_ptr will destroy the nodes that are allocated on heap!
}
