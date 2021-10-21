#include <iostream>
#include "segment_tree.h"

using namespace std;

lazy_seg_tree::lazy_seg_tree(int n) {
	int l = log_2(n);
	p2 = pow2(l);
	if (p2 != n) {
		p2 *= 2;
	}
	p2 *= 2;
	tree.resize(p2);
	lazy.resize(p2);
}

void lazy_seg_tree::update(int l, int r, long long val) {
	upd(1, 1, p2 / 2, l, r, val);
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

int lazy_seg_tree::log_2(long long n) {
	int res = 0;
	while (n > 1) {
		n /= 2;
		res++;
	}

	return res;
}
long long lazy_seg_tree::pow2(int n) {
	if (n == 0) return 1;
	long long res = 1;
	if (n % 2 == 1) res *= 2;
	int temp = pow2(n / 2);
	return res * temp * temp;

}

seg_tree::seg_tree(int n) {
	int l = log_2(n);
	p2 = pow2(l);
	if (p2 != n) {
		p2 *= 2;
	}
	p2 *= 2;
	tree.resize(p2);
}

int seg_tree::log_2(long long n) {
	int res = 0;
	while (n > 1) {
		n /= 2;
		res++;
	}

	return res;
}
long long seg_tree::pow2(int n) {
	if (n == 0) return 1;
	long long res = 1;
	if (n % 2 == 1) res *= 2;
	int temp = pow2(n / 2);
	return res * temp * temp;
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
	if (end < l || start > r) return 0;
	if (end <= r && start >= l) return tree[node];

	int mid = (start + end) / 2;
	long long res1 = qr(2 * node, start, mid, l, r);
	long long res2 = qr(2 * node + 1, mid + 1, end, l, r);
	return operate(res1, res2);
}

long long sum_seg_tree::operate(long long x, long long y) {
	return x+y;
}

long long min_seg_tree::operate(long long x, long long y) {
	return min(x, y);
}

long long max_seg_tree::operate(long long x, long long y) {
	return max(x, y);
}

long long xor_seg_tree::operate(long long x, long long y) {
	return x ^ y;
}

sum_seg_tree::sum_seg_tree(int n) : seg_tree(n) {}

min_seg_tree::min_seg_tree(int n) : seg_tree(n) {}

max_seg_tree::max_seg_tree(int n) : seg_tree(n) {
	for (int i = 1; i < tree.size(); i++) {
		tree[i] = LLONG_MAX;
	}
}

xor_seg_tree::xor_seg_tree(int n) : seg_tree(n) {}