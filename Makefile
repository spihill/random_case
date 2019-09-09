CXX = g++
OBJS = check.o random_case.o main.o correct.o
CXXFLAGS = -Wall -std=c++14 -DCHECK_CPP
TARGET = check.out

.PHONY: main check clean clean_txt

main: main.out
	./main.out
main.out: main.cpp
	g++ -Wall -std=c++14 main.cpp -o main.out

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

check: check.out
	./check.out

clean:
	rm *.o
	rm *.out

clean_txt:
	rm random_*_in.txt
	rm random_*_out.txt
	rm random_*_ans.txt
