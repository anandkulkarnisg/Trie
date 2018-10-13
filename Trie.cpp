/*
 * Trie.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: anand
 */

#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class Trie
{
private:
	class TrieNode
	{
	public:
		map<char, TrieNode*> m_children;
		bool m_isComplete;
		TrieNode()
		{
			m_children = map<char, TrieNode*>();
			m_isComplete = false;
		}
	};

// Root node of the Trie Data Structure.
	TrieNode* m_root;

public:
	Trie()
	{
		m_root = new TrieNode();
	}

	void insertWord(const std::string& word)
	{
		if(word.size() == 0)
			return;

		TrieNode* currNode = m_root;
		TrieNode* newNode;
		for(unsigned int i=0; i<word.length(); ++i)
		{
			if(currNode->m_children.size()==0)
			{
				newNode = new TrieNode();
				currNode->m_children[word[i]] = newNode;
			}
			else
			{
			   const auto& iter = currNode->m_children.find(word[i]);
			   if(iter==currNode->m_children.end())
			   {
				   newNode = new TrieNode();
				   currNode->m_children[word[i]] = newNode;
			   }
			   else
				  newNode = iter->second;
			}
			currNode = newNode;
		}
		newNode->m_isComplete=true;
	}

	bool isWord(const std::string& word)
	{
		if(word.size()==0)
			return(false);

		TrieNode* currNode = m_root;
		for(unsigned int i=0; i<word.size(); ++i)
		{
			const auto& iter = currNode->m_children.find(word[i]);
			if(iter == currNode->m_children.end())
				return(false);
			else
				currNode = iter->second;
		}
		return(currNode->m_isComplete);
	}

	bool deleteWord(const std::string& word)
	{
		bool deleteStatus=recursiveDelete(m_root, word);
		return(deleteStatus);
	}

	bool recursiveDelete(TrieNode* current, const std::string& word, const size_t& index=0)
	{
		if( index == word.length())
		{
			if(!current->m_isComplete)
				return(false);

			current->m_isComplete=false;
			return(current->m_children.size()==0);
		}

		char ch = word[index];
		const auto& iter = current->m_children.find(ch);
		if(iter == current->m_children.end())
			return(false);

		bool shouldDeleteCurrentNode = recursiveDelete(iter->second, word, index+1);
	    if(shouldDeleteCurrentNode)
	    {
	      cout << "performing deletion at " << word[index] << endl;
	      current->m_children.erase(ch);
	      //return true if no mappings are left in the map.
	      return (current->m_children.size() == 0);
	    }
	    return(false);
	}
};

int main(int argc, char* argv[])
{
	std::vector<std::string> wordList = { "anand" , "anant", "deepti", "robert", "zebra" };
	Trie sampleTrie;

	for(const auto& word : wordList)
		sampleTrie.insertWord(word);

	std::vector<std::string> invalidWordList = { "magic", "tickle", "trickster", "buggy" };
	for(const auto& word : wordList )
	{
		if(sampleTrie.isWord(word))
			cout << "word = " << word << " is a valid Word as per Trie." << endl;
		else
			cout << "word = " << word << " is an invalid Word as per Trie." << endl;
	}

	for(const auto& word : invalidWordList )
	{
		if(sampleTrie.isWord(word))
			cout << "word = " << word << " is a valid Word as per Trie." << endl;
		else
			cout << "word = " << word << " is an invalid Word as per Trie." << endl;
	}

	const std::string testWord = "anand";
	bool isWordStatus = sampleTrie.isWord(testWord);
	cout << "The isWord status for " << testWord << " = " << isWordStatus << endl;
	bool deleteStatus = sampleTrie.deleteWord(testWord);
	cout << "The deletionStatus = " << deleteStatus << endl;
	isWordStatus = sampleTrie.isWord(testWord);
	cout << "The isWord status for " << testWord << " = " << isWordStatus << endl;
	return(0);
}

