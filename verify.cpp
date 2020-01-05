#include<bits/stdc++.h>
using namespace std;

#define main moin
#include "random_case.cpp"
#undef main

bool is_connected(const vector<vector<size_t>>& g) {
	vector<set<size_t>> g2(g.size());
	for (size_t i = 0; i < g.size(); i++) {
		for (auto x : g[i]) {
			g2[i].insert(x);
			g2[x].insert(i);
		}
	}
	queue<size_t> q;
	vector<bool> used(g.size(), false);
	q.push(0); used[0] = true;
	while (q.size()) {
		size_t i = q.front(); q.pop();
		for (auto x : g2[i]) {
			if (used[x]) continue;
			used[x] = true;
			q.push(x);
		}
	}
	for (size_t i = 0; i < g2.size(); i++) if (!used[i]) return false;
	return true;
}

void check_graph(size_t V, size_t E, bool connected) {
	random_class rc;
	size_t e = 0;
	auto g = rc.make_random_graph(V, E, connected);
	assert(V == g.size());
	set<pair<size_t, size_t>> st;
	for (size_t i = 0; i < V; i++) {
		for (size_t x : g[i]) {
			assert(x < V);
			st.insert({i, x});
			e++;
		}
	}
	assert(E == st.size());
	assert(E == e);
	for (auto p : st) {
		assert(st.count({p.second, p.first}) == 0);
	}
	if (connected) assert(is_connected(g));
}

int main() {
	random_class rc;
	for (int i = 100; i--; ) {
		size_t V = rc.make_random(21, 40);
		size_t E = rc.make_random(V-1, V * (V - 1) / 2);
		check_graph(V, E, true);
		// check_graph(V, V-1, true);
		// check_graph(V, V*(V-1) / 2, true);
	}
	cout << "OK" << endl;
}