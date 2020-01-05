#include<bits/stdc++.h>
using namespace std;

#define cin cannot use cin and cout in solve function
#define cout cannot use cin and cout in solve function

bool solve(ifstream in, ifstream out) {
	int res; out >> res;
	int N; in >> N;
	int sum = 0;
	for (int i = 0; i < N; i++) {
		int t; in >> t; sum += t;
	}
	return res == sum;
}

#undef cin
#undef cout

int main(int argc, char** argv) {
	assert(argc == 3);
	if (solve(ifstream(string(argv[1])), ifstream(string(argv[2])))) cout << "AC" << endl;
	else cout << "WA" << endl;
}