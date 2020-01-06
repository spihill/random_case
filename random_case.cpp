#include <bits/stdc++.h>

using namespace std;
using u64 = uint_fast64_t;
using u32 = uint_fast32_t;

struct has_il_impl {
	template <class T>
	static std::true_type check(decltype(T::il)*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_il :
	public decltype(has_il_impl::check<T>(nullptr)) {};

struct has_data_class_impl {
	template <class T>
	static std::true_type check(typename T::data_class_tag*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_data_class_tag :
	public decltype(has_data_class_impl::check<T>(nullptr)) {};

template<class T, class Enable = void>
struct base_data_class;

template<class T>
struct base_data_class<T, enable_if_t<is_arithmetic<T>::value>> {
	using value_type = T;
	struct data_class_tag {};
	T min_v, max_v;
	base_data_class(T min_value, T max_value) : min_v(min_value), max_v(max_value) {assert(min_v <= max_v);}
};

template<class T>
struct random_select_class : public base_data_class<size_t> {
	vector<T> il;
	random_select_class(initializer_list<T> il_) : base_data_class(size_t(0), il_.size()-1), il{il_} {}
};

template<class T>
struct data_class : public base_data_class<T> {
	template<class... Args>
	data_class(Args... args) : base_data_class<T>(args...) {}
};

u32 seed;

struct random_class {
	mt19937 engine;
	random_class() : engine(seed) {}
	// min_v : 生成する乱数の最小値
	// max_v : 生成する乱数の最大値
	template<class T>
	enable_if_t<is_arithmetic<T>::value, T> make_random(T min_v, T max_v) {
		return make_random_number(min_v, max_v);
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && has_il<T>::value, typename T::value_type> make_random(const T& dc) {
		return dc.il[make_random_number(dc.min_v, dc.max_v)];
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, typename T::value_type> make_random(const T& dc) {
		return make_random_number(dc.min_v, dc.max_v);
	}
	// vector_size : 生成するvectorの長さ
	// dc : data_class
	// dup : 要素の重複を許容するならtrue (default : true)
	// inc : 昇順にソートするならtrue (default : false)
	// dec : 降順にソートするならtrue (default : false)
	// 0-indexed で生成
	template<class T>
	enable_if_t<has_data_class_tag<T>::value, vector<typename T::value_type>> make_random_vector(size_t vector_size, T& dc, bool dup = true, bool inc = false, bool dec = false) {
		vector<typename T::value_type> v;
		assert(!(inc && dec));
		set<typename T::value_type> s;
		for (size_t i = 0; i < vector_size; i++) {
			typename T::value_type t = make_random(dc);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
		return v;
	}
	// dc : data_class
	// data_class が持つ値域を参照し、すべての要素の random な permutation を生成する。
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && is_integral<typename T::value_type>::value, vector<typename T::value_type>> make_random_permutation(T& dc) {
		uint32_t vector_size = dc.max_v - dc.min_v + 1;
		vector<typename T::value_type> v;
		set<typename T::value_type> s;
		for (size_t i = 0; i < vector_size; i++) {
			typename T::value_type t = make_random(dc);
			if (s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		return v;
	}
	// V : 頂点数
	// E : 辺の数
	// connected : 連結なグラフを生成させるか (default : true)
	// DAG が生成される(頂点番号でトポロジカルソート可能)
	// 0-indexed で生成
	vector<vector<size_t>> make_random_graph(size_t V, size_t E, bool connected = true) {
		assert(V > 0);
		assert(!connected || V - 1 <= E);
		u64 MAX_E = V * (V - 1) / 2;
		assert(E <= MAX_E);
		size_t e = size_t(min<u64>(MAX_E - E, E));
		vector<unordered_set<size_t>> vs_origin = connected ? make_random_tree_sub(V) : vector<unordered_set<size_t>>(V);
		auto vs = vs_origin;
		e -= (connected && E == e) ? V - 1 : 0;
		make_random_graph_sub(V, e, vs);
		vector<vector<size_t>> res(V);
		if (E <= MAX_E - E) {
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs[i]) {
					res[i].push_back(x);
				}
			}
		} else {
			for (size_t i = 0; i < V; i++) {
				for (size_t j = i+1; j < V; j++) {
					if (!vs[i].count(j)) res[i].push_back(j);
				}
			}
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs_origin[i]) {
					res[i].push_back(x);
				}
			}
		}
		return res;
	}
	// V : 頂点数
	// DAG が生成される(頂点番号でトポロジカルソート可能)
	vector<vector<size_t>> make_random_tree(size_t V) {
		auto v = make_random_tree_sub(V);
		vector<vector<size_t>> res(V);
		for (size_t i = 0; i < V; i++) {
			for (auto x : v[i]) res[i].push_back(x);
		}
		return res;
	}
private:
	vector<unordered_set<size_t>> make_random_tree_sub(size_t V) {
		vector<unordered_set<size_t>> g(V);
		for (size_t i = 1; i < V; i++) {
			g[make_random<size_t>(0, i-1)].insert(i);
		}
		return g;
	}
	void make_random_graph_sub(size_t V, size_t E, vector<unordered_set<size_t>>& used) {
		size_t from, to;
		for (size_t i = 0; i < E; i++) {
			make_random_simple_edge_(V, from, to);
			if (used[from].count(to)) i--;
			else used[from].insert(to);
		}
	}
	template<class T>
	T make_random_number(T min_v, T max_v) { return uniform_int_distribution<T>(min_v, max_v)(engine);}
	vector<u64> make_random_divide(size_t len, u64 sum, u64 min_v = 0) {
		assert(len);
		if (min_v) {
			assert(min_v * len <= sum);
			auto res = make_random_divide(len, sum - min_v * len);
			for (auto& x : res) x += min_v;
			return res;
		}
		u64 N = sum + len - 1;
		vector<u64> pos{0, N+1};
		unordered_set<u64> s;
		for (size_t i = 1; i < len; i++) {
			u64 t = make_random<u64>(1, N);
			if (s.count(t)) i--;
			else pos.push_back(t), s.insert(t);
		}
		sort(pos.begin(), pos.end());
		vector<u64> res(len);
		for (size_t i = 0; i < len; i++) {
			res[i] = pos[i+1] - pos[i] - 1;
		}
		return res;
	}
	void make_random_simple_edge_(size_t V, size_t& from, size_t& to) {
		from = make_random<size_t>(0, V-1);
		while ((to = make_random<size_t>(0, V-1)) == from);
		if (from > to) swap(from, to);
	}
};
template<> double random_class::make_random_number<double>(double min_v, double max_v) { return uniform_real_distribution<double>(min_v, max_v)(engine);}
template<> long double random_class::make_random_number<long double>(long double min_v, long double max_v) { return uniform_real_distribution<long double>(min_v, max_v)(engine);}
template<> float random_class::make_random_number<float>(float min_v, float max_v) { return uniform_real_distribution<float>(min_v, max_v)(engine);}


template<class T>
random_select_class<T> make_data(initializer_list<T> il) {
	return random_select_class<T>(il);
}

template<class T>
enable_if_t<is_arithmetic<T>::value, data_class<T>> make_data(T min_v, T max_v) {
	return data_class<T>(min_v, max_v);
}

/* data_class と random_select_class について
  乱数生成する際に用いるクラス。
    auto X = make_data(3, 5)
  などのように生成する。
    auto X = make_data(5, 8)
    auto X = make_data({5, 6, 7, 8})
  はほぼ等価。(前者では data_class が生成され、後者では random_select_class が生成される。)
*/


int main(int argc, char** argv) {
	assert(argc == 2); seed = u32(atoi(argv[1]));
	random_class rc;
	auto X = make_data(3, 5);
	auto Y = make_data({1, 2, 4, 5, 6, 9});
	int N = rc.make_random(X);
	cout << N << endl;
	auto A = rc.make_random_vector(N, Y);
	assert(int(A.size()) == N);
	for (auto x : A) cout << x << " ";
	cout << endl;
	return 0;
}