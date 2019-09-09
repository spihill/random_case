#include <bits/stdc++.h>

using namespace std;

#define cin input
#define cout output

void solve(istream& input, ostream& output) {
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