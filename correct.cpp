#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int res = 0;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		res += t;
	}
	cout << res << endl;
}