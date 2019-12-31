RANDOM_DIR = ./generate_cases
CXX = g++
OBJS = check.o random_case.o
CXXFLAGS = -Wall -std=c++14 -DCHECK_CPP -DRANDOM_DIR="$(RANDOM_DIR)"
TARGET = check.out
RM = rm -f

.PHONY: main check clean clean_txt

main: main.out
	./main.out
main.out: main.cpp
	g++ -Wall -std=c++14 $^ -o $@
correct.out: correct.cpp
	g++ -Wall -std=c++14 $^ -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

check: main.out correct.out $(TARGET)
	mkdir -p $(RANDOM_DIR)
	make clean_txt
	./$(TARGET)

clean:
	$(RM) *.o
	$(RM) *.out

clean_txt:
	$(RM) -r $(RANDOM_DIR)/case*

clean_all:
	make clean
	make clean_txt
