#include <bits/stdc++.h>

using namespace std;

struct random_class {
	random_device rd;
	mt19937 engine;
	ostream& os;
	random_class(ostream& o) : rd(), engine(rd()), os(o) {}
	int make_random(int min_v, int max_v) { return uniform_int_distribution<int>(min_v, max_v)(engine);}
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
			int t = u(engine);
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
		dup = false; // 重複を許すか
		inc = false; // 増加列か
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