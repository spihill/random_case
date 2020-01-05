#include<bits/stdc++.h>
using namespace std;

#define main moin
#include "../random_case.cpp"
#undef main

bool is_connected(const vector<vector<size_t>>& g) {
	vector<vector<size_t>> g2(g.size());
	for (size_t i = 0; i < g.size(); i++) {
		for (auto x : g[i]) {
			g2[i].push_back(x);
			g2[x].push_back(i);
		}
	}
	queue<size_t> q;
	vector<char> used(g.size(), false);
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
	unordered_set<u64> st;
	for (size_t i = 0; i < V; i++) {
		for (size_t x : g[i]) {
			assert(x < V);
			assert(i < x);
			u64 val = static_cast<u64>(i) << 32 | x;
			assert(st.count(val) == 0);
			st.insert(val);
			e++;
		}
	}
	assert(E == st.size());
	assert(E == e);
	if (connected) assert(is_connected(g));
}

void Graph_test() {
	random_class rc;
	cerr << "Graph test" << endl;
	for (int i = 0; i < 100; i++) {
		size_t V = rc.make_random(1, 10);
		size_t E = rc.make_random(V-1, V * (V - 1) / 2);
		check_graph(V, E, true);
		check_graph(V, V-1, true);
		check_graph(V, V*(V-1) / 2, true);
	}
	for (int i = 0; i < 100; i++) {
		size_t V = rc.make_random(11, 100);
		size_t E = rc.make_random(V-1, V * (V - 1) / 2);
		check_graph(V, E, true);
		check_graph(V, V-1, true);
		check_graph(V, V*(V-1) / 2, true);
	}
	for (auto V : {500, 1000, 1500}) {
		for (int i = 0; i < 5; i++) {
			check_graph(V, V-1, true);
			check_graph(V, V*(V-1) / 2, true);
			check_graph(V, V*(V-1) / 4, true);
		}
	}
	cerr << "OK" << endl;
}

int main() {
	Graph_test();
}