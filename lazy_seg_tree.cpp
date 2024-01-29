#include <iostream>
#include <vector>

using namespace std;

class lazy_seg_tree {
public:
	lazy_seg_tree(int n);
	void update(int l, int r, long long val);
	long long query(int l, int r);

private:
	vector <long long> tree;
	vector <long long> lazy;
	int p2;

	void upd(int node, int start, int end, int l, int r, long long val);
	long long qr(int node, int start, int end, int l, int r);
};

lazy_seg_tree::lazy_seg_tree(int n) {
	p2 = 1;
	while(p2 < n) p2 *= 2;
	p2 *= 2;
	tree.resize(p2);
	lazy.resize(p2);
}

void lazy_seg_tree::update(int l, int r, long long val) {
	upd(1, 1, p2 / 2, l + 1, r + 1, val);
}

long long lazy_seg_tree::query(int l, int r) {
	return qr(1, 1, p2 / 2, l + 1, r + 1);
}

void lazy_seg_tree::upd(int node, int start, int end, int l, int r, long long val) {
	if (lazy[node] != 0) {
		tree[node] += (((long long)end - start + 1)) * lazy[node];

		if (start != end) {
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	if (end < l || start > r) return;
	if (end <= r && start >= l) {
		tree[node] += ((long long)end - start + 1)* (long long)val;
		if (start != end) {
			lazy[2 * node] += (long long)val;
			lazy[2 * node + 1] += (long long)val;
		}

		return;
	}

	int mid = (start + end) / 2;
	upd(2 * node, start, mid, l, r, val);
	upd(2 * node + 1, mid + 1, end, l, r, val);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long lazy_seg_tree::qr(int node, int start, int end, int l, int r) {
	if (lazy[node] != 0) {
		tree[node] += ((long long)end - start + 1) * lazy[node];

		if (start != end) {
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	if (end < l || start > r) return 0;
	if (end <= r && start >= l) return tree[node];

	int mid = (start + end) / 2;
	long long res1 = qr(2 * node, start, mid, l, r);
	long long res2 = qr(2 * node + 1, mid + 1, end, l, r);
	return res1 + res2;
}
