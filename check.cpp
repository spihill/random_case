#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include<cassert>
#include <sys/stat.h>

using namespace std;

#define quote(x) quote_sub(x)
#define quote_sub(x) #x

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

#define CONNECT_FD(file, to, option) do { \
	if (file != "") { \
		int fd = open((file).c_str(), (option), S_IRUSR | S_IWUSR); \
		dup2(fd, (to)); \
		close(fd); \
	} \
} while (0)

int execute(const string& exe_filename, const vector<string>& args, const string& input_file, const string& output_file, const string& error_file, const string& RE_message) {
	pid_t pid;
	int status;
	if ((pid = fork()) == -1) {
		cerr << "fork() failed" << endl;
		abort();
	} else if (pid > 0){
		pid_t r = waitpid(pid, &status, 0);
		assert(pid == r);
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
		CONNECT_FD(input_file, 0, O_RDONLY);
		CONNECT_FD(output_file, 1, O_RDWR | O_CREAT | O_TRUNC);
		CONNECT_FD(error_file, 2, O_RDWR | O_CREAT | O_TRUNC);
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
	const string random_re_message = random_dir + "makerandom_RE" + suff;
	const string dummy = "";
	if (execute("./random_case.out", {"./random_case.out"}, dummy, input, dummy, random_re_message) != 0) {
		cerr << "Runtime Error(random_case.cpp) on case " << id << "." << endl;
		abort();
	}
	if (execute("./correct.out", {"./correct.out"}, input, answer, answer_error, answer_re_message) != 0) {
		cerr << "Runtime Error(corect.cpp) on case " << id << "." << endl;
		abort();
	}
	if (execute("./main.out", {"./main.out"}, input, output, error, re_message) != 0) RE++;
	else if (!check_diff(output, answer)) WA++;
}

constexpr int NUM_OF_TESTCASES = 10;
constexpr int MAX_LOOP = 10000;

int main() {
	int WA = 0;
	int RE = 0;
	int count = 0;
	vector<int> wa, re;
	while (WA + RE < NUM_OF_TESTCASES && count < MAX_LOOP) {
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