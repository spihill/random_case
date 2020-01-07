#include<bits/stdc++.h>
using namespace std;

#define main moin
#include "../random_case.cpp"
#undef main

void print_graph(const vector<vector<size_t>>& g) {
	for (size_t i = 0; i < g.size(); i++) {
		for (auto x : g[i]) cout << i << ' ' << x << endl;
	}
	cout << endl;
}

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
bool is_dag(const vector<vector<size_t>>& g) {
	vector<char> flag(g.size());
	auto dfs = [&](auto& f, int n) -> bool {
		if (flag[n] == 2) return true;
		if (flag[n] == 1) return false;
		flag[n] = 1;
		for (auto x : g[n]) if (!f(f, x)) return false;
		flag[n] = 2;
		return true;
	};
	for (size_t i = 0; i < g.size(); i++) if (!dfs(dfs, i)) return false;
	return true;
}
bool can_reach(const vector<vector<size_t>>& g, size_t from, size_t to) {
	vector<char> vis(g.size());
	auto dfs = [&](auto& f, size_t n) -> void {
		if (vis[n]) return;
		vis[n] = true;
		for (auto x : g[n]) f(f, x);
	};
	dfs(dfs, from);
	return vis[to];
}

void check_graph(size_t V, size_t E, bool connected, bool dag, bool randomized) {
	assert(V);
	if (connected && E < V - 1) return;
	u64 MAX_E = dag ? u64(V) * (V-1) / 2 : u64(V) * (V-1);
	if (MAX_E < E) return;
	random_class rc;
	size_t e = 0;
	auto g = rc.make_random_graph(V, E, connected, dag, randomized);
	assert(V == g.size());
	unordered_set<u64> st;
	for (size_t i = 0; i < V; i++) {
		for (size_t x : g[i]) {
			assert(x < V);
			u64 val = static_cast<u64>(i) << 32 | x;
			assert(st.count(val) == 0);
			st.insert(val);
			e++;
		}
	}
	if (E != st.size()) {
		cout << V << " " << E << " " << connected << " " << dag << endl;
		for (size_t i = 0; i < V; i++) {
			for (auto x : g[i]) {
				cout << i << " " << x << endl;
			}
		}
	}
	assert(E == st.size());
	assert(E == e);
	if (connected) assert(is_connected(g));
	if (dag) assert(is_dag(g));
	if (g.size() < 2 || E == 0) return;
	size_t from = rc.make_random<size_t>(0, g.size()-1);
	size_t to;
	while ((to = rc.make_random<size_t>(0, g.size()-1)) == from);
	rc.ensure_reach(g, from, to);
	assert(can_reach(g, from, to));
}

void check_graph(size_t V) {
	random_class rc;
	for (bool connected : {false, true}) {
		for (bool dag : {false, true}) {
			for (bool randomized : {false, true}) {
				check_graph(V, rc.make_random<size_t>(0, max<i32>(1, i32(V) - 2)), connected, dag, randomized);
				check_graph(V, V-1, connected, dag, randomized);
				check_graph(V, rc.make_random(V-1, V * (V - 1) / 2), connected, dag, randomized);
				check_graph(V, V*(V-1) / 2, connected, dag, randomized);
				check_graph(V, rc.make_random(V * (V - 1) / 2, V * (V - 1)), connected, dag, randomized);
				check_graph(V, V * (V-1), connected, dag, randomized);
			}
		}
	}
}

void Graph_test() {
	random_class rc;
	cerr << "Graph test" << endl;
	for (int i = 0; i < 100; i++) check_graph(rc.make_random(1, 10));
	for (int i = 0; i < 100; i++) check_graph(rc.make_random(11, 100));
	for (size_t V : {100, 250, 500}) for (int i = 0; i < 5; i++) check_graph(V);
	cerr << "OK" << endl;
}

void check_random_divide(size_t len, i64 sum, i64 min_v = 0) {
	random_class rc;
	auto res = rc.make_random_divide(len, sum, min_v);
	for (auto x : res) sum -= x;
	assert(sum == 0);
}

void Divide_test() {
	random_class rc;
	cerr << "Divide test" << endl;
	for (int i = 0; i < 1000; i++) check_random_divide(rc.make_random(1, 10), rc.make_random(0, 30));
	for (int i = 0; i < 1000; i++) check_random_divide(rc.make_random(1, 100), 0);
	for (int i = 0; i < 1000; i++) {
		i32 min_v = rc.make_random(-1000, 1000);
		u32 len = rc.make_random(100, 1000);
		if (min_v < 0) check_random_divide(len, rc.make_random<i64>(min_v * len, 0), min_v);
		else check_random_divide(len, rc.make_random<i64>(min_v * len, min_v * len + 10000), min_v);
		check_random_divide(len, min_v * len, min_v);
	}
	cerr << "OK" << endl;
}

int main() {
	Divide_test();
	Graph_test();
}