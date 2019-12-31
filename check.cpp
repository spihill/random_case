#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define quote(x) quote_sub(x)
#define quote_sub(x) #x

void make_random(const string& output);

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

ofstream open_file_append(const string& file_name) {
	return ofstream(file_name, ios::app);
}

int execute(const string& exe_filename, const vector<string>& args, const string& input_file, const string& output_file, const string& error_file, const string& RE_message) {
	pid_t pid;
	int status;
	if ((pid = fork()) == -1) {
		cerr << "fork() failed" << endl;
		abort();
	} else if (pid > 0){
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 0) return 0;
			open_file_append(RE_message) << "Exited with code " << WEXITSTATUS(status) << "." << endl;
		} else if (WIFSIGNALED(status)) {
			int signal = WTERMSIG(status);
			open_file_append(RE_message) << "Exited with SIGNAL " << signal << "." << endl;
			if (signal == SIGSEGV) open_file_append(RE_message) << "Segmentation fault." << endl;
			else if (signal == SIGFPE) open_file_append(RE_message) << "Floating point exception." << endl;
		}
		return 1;
	} else {
		char** arg = new char*[args.size() + 1];
		for (size_t i = 0; i < args.size(); i++) {
			arg[i] = (char*) args[i].c_str();
		}
		arg[args.size()] = nullptr;
		int in = open(input_file.c_str(), O_RDONLY, S_IRUSR | S_IWUSR);
		int out = open(output_file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		int error = open(error_file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(in, 0);
		dup2(out, 1);
		dup2(error, 2);
		close(in);
		close(out);
		close(error);
		execvp(exe_filename.c_str(), (char* const*) arg);
		perror("execute");
		abort();
	}
}

void case_check(int& WA, int& RE) {
	int id = WA + RE;
	const string random_dir = string(quote(RANDOM_DIR)) + "/case" + to_string(id) + '/';
	mkdir(random_dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	const string suff = ".txt";
	const string input = random_dir + "input" + suff;
	const string output = random_dir + "output" + suff;
	const string error = random_dir + "error" + suff;
	const string answer = random_dir + "answer" + suff;
	const string re_message = random_dir + "RE" + suff;
	const string answer_error = random_dir + "answer_error" + suff;
	const string answer_re_message = random_dir + "answer_RE" + suff;
	make_random(input);
	if (execute("./correct.out", {"./correct.out"}, input, answer, answer_error, answer_re_message) != 0) {
		cerr << "Runtime Error(corect.cpp) on case " << id << "." << endl;
		abort();
	}
	if (execute("./main.out", {"./main.out"}, input, output, error, re_message) != 0) RE++;
	else if (!check_diff(output, answer)) WA++;
}

int main() {
	int WA = 0;
	int RE = 0;
	int count = 0;
	vector<int> wa, re;
	while (WA + RE < 10 && count < 10000) {
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
	return 0;
}