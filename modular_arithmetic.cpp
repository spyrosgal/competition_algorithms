#include <iostream>

using namespace std;

int phi(int n) {
	int res = n;
	for (int p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			while (n % p == 0) n /= p;
		}

		res -= res / n;
	}

	if (n > 1) res -= res / n;

	return res;
}

long long gcd(long long a, long long b) {
	if (a == 0) return b;
	else return gcd(b % a, a);
}

long long lcm(long long a, long long b) {
	return a / gcd(a, b) * b;
}

long long mod_pow(long long base, int exp, int mod) {
	if (exp == 0) return (long long)1;
	else {
		long long t = mod_pow(base, exp / 2, mod);
		if (exp % 2 == 0) return (t * t) % mod;
		else return ((t * t) % mod) * base % mod;
	}
}

long long mod_inverse(int base, int mod) {
	return mod_pow(base, phi(mod) - 1, mod);
}

class mint {
public:
	static int mod;
	long long val;

	mint() {
		val = 0;
	}
 
	mint(long long v) {
		val = v % mod;
	}
 
	static mint pw(mint a, int b);
	static mint inv(mint a);
 
	friend mint operator + (const mint& x, const mint& y) {
		return mint((x.val + y.val) % mod);
	}
 
	friend mint operator - (const mint& x, const mint& y) {
		return (x.val >= y.val) ? x.val - y.val : ((mod + x.val - y.val) % mod);
	}
 
	friend mint operator * (const mint& x, const mint& y) {
		return mint((x.val * y.val) % mod);
	}
 
	friend mint operator /(const mint& x, const mint& y) {
		return mint(x.val * inv(y.val));
	}

	friend ostream& operator<<(ostream& os, const mint& x) {
		os << x.val;
		return os;
	}

};
 
mint mint::pw(mint a, int b) {
	if(!b) return 1;
	mint t = pw(a, b / 2);
	t = t * t;
	if(b % 2) t = t * mint(a);
	return t;
}
 
mint mint::inv(mint a) {
	return mint::pw(a, mod - 2);
}
 
int mint::mod = 999999893;

mint factorial(int n) {
	mint res = 1;
	for (int i = 1; i <= n; i++) {
		res = res * i;
	}

	return res;
}

mint choose(int n, int k) {
	if (k > n) return 0;
	else {
		mint num = factorial(n);
		mint den = factorial(k) * factorial(n-k);
		return num / den;
	}
}