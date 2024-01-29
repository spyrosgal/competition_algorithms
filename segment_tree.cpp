#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class seg_tree {
public:
	seg_tree(int n);
	void update(int pos, long long val);
	long long query(int l, int r);
	void fill(long long *a, int n);

protected:
	vector <long long> tree;
	int p2;

	void upd(int pos, long long val);
	long long qr(int node, int start, int end, int l, int r);

	long long neutral_element = 0;
	long long operate(long long x, long long y) {
		return x + y;
	}
};

seg_tree::seg_tree(int n) {
	p2 = 1;
	while(p2 < n) p2 *= 2;
	p2 *= 2;
	tree.resize(p2);
}

void seg_tree::update(int pos, long long val) {
	upd(p2 / 2 + pos, val);
}

void seg_tree::upd(int pos, long long val) {
	if (pos == 0) return;
	tree[pos] = operate(tree[pos], val);
	upd(pos / 2, val);
}

long long seg_tree::query(int l, int r) {
	return qr(1, 1, p2 / 2, l + 1, r + 1);
}

long long seg_tree::qr(int node, int start, int end, int l, int r) {
	if (end < l || start > r) return neutral_element;
	if (end <= r && start >= l) return tree[node];

	int mid = (start + end) / 2;
	long long res1 = qr(2 * node, start, mid, l, r);
	long long res2 = qr(2 * node + 1, mid + 1, end, l, r);
	return operate(res1, res2);
}

void seg_tree::fill(long long *a, int n) {
	for(int i = 0; i < n; i++) {
		tree[p2 / 2 + i] = a[i];
	}

	for(int i = n; i < p2 / 2; i++) {
		tree[p2 / 2 + i] = neutral_element;
	}

	for(int i = p2 / 2 - 1; i >= 1; i--) {
		tree[i] = operate(tree[2 * i], tree[2 * i + 1]);
	}
}
