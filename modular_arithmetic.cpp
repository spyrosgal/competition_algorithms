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

long long factorial(int n, int mod) {
	long long res = 1;
	for (int i = 1; i <= n; i++) {
		res *= (long long)i;
		res %= mod;
	}

	return res;
}

long long choose(long long n, long long k, int mod) {
	if (k < n) return 0;
	else {
		long long num = factorial(n, mod);
		long long den = factorial(k, mod) * factorial(n-k, mod) %mod;
		den = mod_inverse(den, mod);
		return num * den % mod;
	}
}

class mint {
public:
	static int mod;
	long long val;

	mint(long long v) {
		val = v;
	}

	friend mint operator + (const mint& x, const mint& y) {
		return mint((x.val + y.val) % mod);
	}

	friend mint operator - (const mint& x, const mint& y) {
		if (x.val >= y.val) {
			return mint((x.val - y.val) % mod);
		}
		else {
			if ((y.val - x.val) % mod == 0) return mint(0);
			else return mint(mod - (y.val - x.val) % mod);
		}
	}

	friend mint operator * (const mint& x, const mint& y) {
		return mint((x.val * y.val) % mod);
	}

	friend mint operator /(const mint& x, const mint& y) {
		return mint(x.val * mod_inverse(y.val, mod));
	}
};

int main() {
	return 0;
}