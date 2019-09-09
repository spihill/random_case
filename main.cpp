#include <bits/stdc++.h>

using namespace std;

#define cin is
#define cout os

void solve(istream& is, ostream& os) {
	int n;
	cin >> n;
	int res = 0;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		res += t;
	}
	cout << res + 1 << endl;
}

#undef cin
#undef cout

#ifndef CHECK_CPP

int main() {
	solve(cin, cout);
}

#endif