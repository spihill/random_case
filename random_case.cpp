#include <bits/stdc++.h>

using namespace std;

struct random_class {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	ostream& os;
	random_class(ostream& o) : rd(), xor128(rd()), os(o) {}
	int make_random(int min_v, int max_v) { return uniform_int_distribution<int>(min_v, max_v)(xor128);}
};

struct array_int : public random_class {
	const int sz;
	uniform_int_distribution<int> u;
	bool dup;
	bool inc;
	bool dec;
	array_int(ostream& os, int n, int min_v, int max_v) : random_class(os), sz(n), u(min_v, max_v) {constrains();}
	void print() {
		assert(!(inc && dec));
		assert(dup || (sz <= (u.max() - u.min() + 1)));
		unordered_set<int> s;
		vector<int> v;
		for (int i = 0; i < sz; i++) {
			int t = u(random_class::xor128);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
		for (int i = 0; i < sz; i++) {
			if (i) os << " ";
			os << v[i];
		}
		os << endl;
	}
	void constrains() {
		dup = true; // 重複を許すか
		inc = true; // 増加列か
		dec = false; // 減少列か
	}
};

void make_random(const string& output) {
	ofstream os(output);
	random_class rc(os);
	auto N = rc.make_random(3, 5);
	os << N << endl;
	array_int A(os, N, 1, 10);
	A.print();
}