#include <iostream>
#include <string>
#include <vector>
#include "binary_indexed_tree.h"
#include "graph_algorithms.h"
#include "aho_corasick.cpp"
#include "segment_tree.h"

using namespace std;

vector <string> strs;

int main() {
	int n, q;
	cin >> n >> q;
	int temp;
	lazy_seg_tree sst(n);
	for (int i = 0; i < n; i++) {
		cin >> temp;
		sst.update(i + 1, i + 1, temp);
	}

	int l, r;
	for (int i = 0; i < q; i++) {
		cin >> l >> r;
		cout << sst.query(l, r) << endl;
	}

	return 0;
}