#include <bits/stdc++.h>

using namespace std;

struct has_il_impl {
	template <class T>
	static std::true_type check(decltype(T::il)*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_il :
	public decltype(has_il_impl::check<T>(nullptr)) {};

struct has_dataclass_impl {
	template <class T>
	static std::true_type check(typename T::dataclass_tag*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_dataclass_tag :
	public decltype(has_dataclass_impl::check<T>(nullptr)) {};

template<class T, class Enable = void>
struct base_dataclass;

template<class T>
struct base_dataclass<T, enable_if_t<is_arithmetic<T>::value>> {
	using value_type = T;
	struct dataclass_tag {};
	T min_v, max_v;
	base_dataclass(T min_value, T max_value) : min_v(min_value), max_v(max_value) {assert(min_v <= max_v);}
};

template<class T>
struct random_select_class : public base_dataclass<size_t> {
	vector<T> il;
	random_select_class(initializer_list<T> il_) : base_dataclass(size_t(0), il_.size()-1), il{il_} {}
};

template<class T>
struct dataclass : public base_dataclass<T> {
	template<class... Args>
	dataclass(Args... args) : base_dataclass<T>(args...) {}
};

struct random_class {
	random_device rd;
	mt19937 engine;
	random_class() : rd(), engine(rd()) {}
	template<class T>
	enable_if_t<is_arithmetic<T>::value, T> make_random(T min_v, T max_v) {
		return make_random_number(min_v, max_v);
	}
	template<class T>
	enable_if_t<has_dataclass_tag<T>::value && has_il<T>::value, typename T::value_type> make_random(const T& dc) {
		return dc.il[make_random_number(dc.min_v, dc.max_v)];
	}
	template<class T>
	enable_if_t<has_dataclass_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, typename T::value_type> make_random(const T& dc) {
		return make_random_number(dc.min_v, dc.max_v);
	}
	template<class T>
	enable_if_t<has_dataclass_tag<T>::value, vector<typename T::value_type>> make_random_vector(size_t vector_size, T& dc, bool dup = true, bool inc = false, bool dec = false) {
		vector<typename T::value_type> v;
		assert(!(inc && dec));
		unordered_set<typename T::value_type> s;
		for (size_t i = 0; i < vector_size; i++) {
			typename T::value_type t = make_random(dc);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
		return v;
	}
private:
	template<class T>
	T make_random_number(T min_v, T max_v) { return uniform_int_distribution<T>(min_v, max_v)(engine);}
};
template<> double random_class::make_random_number<double>(double min_v, double max_v) { return uniform_real_distribution<double>(min_v, max_v)(engine);}
template<> long double random_class::make_random_number<long double>(long double min_v, long double max_v) { return uniform_real_distribution<long double>(min_v, max_v)(engine);}
template<> float random_class::make_random_number<float>(float min_v, float max_v) { return uniform_real_distribution<float>(min_v, max_v)(engine);}

template<class T>
random_select_class<T> make_data(initializer_list<T> il) {
	return random_select_class<T>(il);
}

template<class T>
enable_if_t<is_arithmetic<T>::value, dataclass<T>> make_data(T min_v, T max_v) {
	return dataclass<T>(min_v, max_v);
}

void make_random(const string& output) {
	ofstream os(output);
	random_class rc;
	// auto X = make_data({3, 4, 5});
	// random_select_class<int> X{3, 4, 5};
	auto X = make_data(3, 5);
	auto Y = make_data({1, 2, 4, 5, 6, 9});
	int N = rc.make_random(X);
	auto A = rc.make_random_vector(N, Y);
	os << N << endl;
	for (auto x : A) os << x << " ";
	os << endl;
}