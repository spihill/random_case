RANDOM_DIR = ./generated_cases
CXX = g++
OBJS = check.o random_case.o
CXXFLAGS = -Wall -std=c++14 -O2 -DRANDOM_DIR="$(RANDOM_DIR)"
TARGET = check.out
RM = rm -f

.PHONY: main check clean clean_txt

main: main.out
	./main.out

check.out: random_case.out main.out correct.out

.cpp.out:
	$(CXX) $(CXXFLAGS) $< -o $@

check: main.out correct.out random_case.out $(TARGET)
	mkdir -p $(RANDOM_DIR)
	make clean_txt
	./$(TARGET)

clean:
	$(RM) *.o
	$(RM) *.out

clean_txt:
	$(RM) -r $(RANDOM_DIR)/case*

clean_all: clean clean_txt
