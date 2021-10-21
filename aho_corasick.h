#pragma once
/*#include <string>
#include <vector>

using namespace std;

class ac_trie {
public:
	ac_trie(vector <string> words);

	void process(string s);
private:
	struct node {
		bool word;
		int data;
		node* closest_suffix;
		node* closest_word;
		node* parent;
		node* next[26];

		node();
		node(node* p, int d);
	};

	node* head;
};*/