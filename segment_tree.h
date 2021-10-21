#pragma once
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

	int log_2(long long n);
	long long pow2(int n);
};

class seg_tree {
public:
	seg_tree(int n);
	void update(int pos, long long val);
	long long query(int l, int r);

protected:
	vector <long long> tree;
	int p2;

	void upd(int pos, long long val);
	long long qr(int node, int start, int end, int l, int r);

	int log_2(long long n);
	long long pow2(int n);

	virtual long long operate(long long x, long long y) = 0;
};

class sum_seg_tree : public seg_tree {
public:
	sum_seg_tree(int n);
private:
	long long operate(long long x, long long y) override;
};

class min_seg_tree : public seg_tree {
public:
	min_seg_tree(int n);
private:
	long long operate(long long x, long long y) override;
};

class max_seg_tree : public seg_tree {
public:
	max_seg_tree(int n);
private:
	long long operate(long long x, long long y) override;
};

class xor_seg_tree : public seg_tree {
public:
	xor_seg_tree(int n);
private:
	long long operate(long long x, long long y) override;
};