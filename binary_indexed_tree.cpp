#include <iostream>
#include "binary_indexed_tree.h"

using namespace std;

int bit::sum(int k) {
	int s = 0;
	while (k > 0) {
		s += v[k];
		k -= k & -k;
	}

	return s;
}

void bit::add(int k, int x) {
	while (k <= v.size()-1) {
		v[k] += x;
		k += k & -k;
	}
}

bit::bit(int n) {
	v.resize(n+1);
}