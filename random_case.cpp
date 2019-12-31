#include <bits/stdc++.h>

using namespace std;

struct random_class {
	random_device rd;
	mt19937 engine;
	random_class() : rd(), engine(rd()) {}
	int make_random(int min_v, int max_v) { return uniform_int_distribution<int>(min_v, max_v)(engine);}
};

template<class T = long long>
struct array_int : public random_class {
	const int sz;
	uniform_int_distribution<T> u;
	vector<T> v;
	bool dup;
	bool inc;
	bool dec;
	array_int(int n, T min_v, T max_v) : random_class(), sz(n), u(min_v, max_v) {constrains(); generate();}
	void generate() {
		assert(!(inc && dec));
		assert(dup || (sz <= (u.max() - u.min() + 1)));
		unordered_set<T> s;
		for (int i = 0; i < sz; i++) {
			int t = u(engine);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
	}
	void constrains() {
		dup = false; // 重複を許すか
		inc = false; // 増加列か
		dec = false; // 減少列か
	}
	friend ostream& operator<<(ostream& os, const array_int& ar) {
		for (size_t i = 0; i < ar.v.size(); i++) {
			if (i) os << " ";
			os << ar.v[i];
		}
		return os;
	}
};

void make_random(const string& output) {
	ofstream os(output);
	random_class rc;
	auto N = rc.make_random(3, 5);
	array_int<> A(N, 1, 10);
	os << N << endl;
	os << A << endl;
}