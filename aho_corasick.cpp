#include "aho_corasick.h"
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class ac_trie {
public:
	ac_trie(vector <string> words) {
		head = new node();
		head->closest_suffix = head;
		head->closest_word = nullptr;
		head->parent = head;
		head->data = 0;

		//create trie and mark the appropriate nodes as words
		node* t;
		for (auto s : words) {
			t = head;
			for(int i = 0; i < s.length(); i++){
				if (t->next[s[i]-'a'] == nullptr) {
					t->next[s[i]-'a'] = new node(t, s[i]-'a');
				}

				t = t->next[s[i]-'a'];
			}

			t->word = true;
		}

		//determine biggest suffix that appears in trie for each node
		queue <node *> q;
		q.push(head);
		node* candidate_suffix;
		while (!q.empty()) {
			t = q.front();
			q.pop();
			if (t == head || t->parent == head) {
				t->closest_suffix = head;
			}
			else {
				candidate_suffix = t->parent->closest_suffix;
				while (candidate_suffix->next[t->data] == nullptr) {
					if (candidate_suffix == head) break;
					candidate_suffix = candidate_suffix->closest_suffix;
				}

				t->closest_suffix = candidate_suffix->next[t->data];
			}

			for (int i = 0; i < 26; i++) {
				if (t->next[i] != nullptr) {
					q.push(t->next[i]);
				}
			}
		}

		//determine closest words
		for (int i = 0; i < 26; i++) {
			if (head->next[i] != nullptr) {
				q.push(head->next[i]);
			}
		}
		while (!q.empty()) {
			t = q.front();
			q.pop();
			if (t->closest_suffix->word) {
				t->closest_word = t->closest_suffix;
			}
			else {
				t->closest_word = t->closest_suffix->closest_word;
			}

			for (int i = 0; i < 26; i++) {
				if (t->next[i] != nullptr) {
					q.push(t->next[i]);
				}
			}
		}

	}

	void process(string s) {
		node* curr = head;
		for (int i = 0; i < s.length(); i++) {
			while(curr->next[s[i] - 'a'] == nullptr) {
				if (curr == head) break;
				curr = curr->closest_suffix;
			}

			node* temp;
			if (curr->next[s[i] - 'a'] != nullptr) {
				curr = curr->next[s[i] - 'a'];
				if (curr->word) {
					cout << curr->total_data << " ";
				}
				temp = curr->closest_word;
				while (temp != nullptr) {
					cout << temp->total_data << " ";
					temp = temp->closest_word;
				}
			}

			cout << endl;
		}
	}
private:
	struct node {
		bool word;
		int data;
		string total_data;
		node* closest_suffix;
		node* closest_word;
		node* parent;
		node* next[26];

		node() {
			total_data = "";
			word = false;
			data = 0;
			closest_suffix = nullptr;
			closest_word = nullptr;
			for (int i = 0; i < 26; i++) {
				next[i] = nullptr;
			}
		}

		node(node* p, int d) {
			total_data = p->total_data;
			total_data += ('a'+d);
			word = false;
			data = d;
			closest_suffix = nullptr;
			closest_word = nullptr;
			for (int i = 0; i < 26; i++) {
				next[i] = nullptr;
			}

			parent = p;
		}
	};

	node* head;

};