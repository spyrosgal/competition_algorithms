#pragma once
#include <vector>

using namespace std;

class bit {
public:
	int sum(int k);
	void add(int k, int x);
	bit(int n);

private:
	vector <int> v;
};