#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

void make_random(const string& output);
void solve(istream& is, ostream& os);
void correct(istream& is, ostream& os);

string itos(unsigned int x) {
	if (x == 0) return "0";
	string res = "";
	while (x) {
		res += (char) (x % 10 + '0');
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

void case_solve(const string& in, const string& out) {
	ifstream input(in);
	ofstream output(out);
	solve(input, output);
}

void case_correct(const string& in, const string& out) {
	ifstream input(in);
	ofstream output(out);
	correct(input, output);
}

bool check_diff(const string& out, const string& ans) {
	ifstream output(out);
	ifstream answer(ans);
	string s, t;
	while (true) {
		char o = output.get();
		char a = answer.get();
		if (o != a) return false;
		if (o == EOF && a == EOF) return true;
	}
}

void case_check(int& WA, int& RE) {
	using namespace chrono;
	int id = WA + RE;
	const string input = "random_" + itos(id) + "_in.txt";
	const string output = "random_" + itos(id) + "_out.txt";
	const string answer = "random_" + itos(id) + "_ans.txt";
	make_random(input);
	case_solve(input, output);
	case_correct(input, answer);
	if (!check_diff(output, answer)) WA++;
}

int main() {
	int WA = 0;
	int RE = 0;
	int count = 0;
	vector<int> wa, re;
	while (WA + RE < 3 && count < 100) {
		int w = WA, r = RE;
		case_check(WA, RE);
		if (w != WA) wa.push_back(WA + RE - 1);
		if (r != RE) re.push_back(WA + RE - 1);
		cout << '\r' << "Running case number : " << count++ << ", WA: " << WA << " RE: "<< RE ; cout.flush();
	}
	cout << endl;
	if (!wa.empty()) {
		cout << "WA on case";
		for (auto x : wa) cout << " " << x;
		cout << endl;
	}
	if (!re.empty()) {
		cout << "RE on case";
		for (auto x : re) cout << " " << x;
		cout << endl;
	}
	return WA + RE;
}