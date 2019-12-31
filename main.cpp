#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int res = 0;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < n; i++) res += v[i];
	if (res == 10) res = 0;
	cout << res << endl;
}