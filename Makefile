RANDOM_DIR = ./generated_cases
CXX = g++
CXXFLAGS = -Wall -std=c++14 -O2 -DRANDOM_DIR="$(RANDOM_DIR)"
RM = rm -f

.PHONY: main compare co verify ve clean cl clean_txt ct clean_all ca 
co: compare
ve: verify
cl: clean
ct: clean_txt
ca: clean_all

main: main.out
	./main.out

.cpp.out:
	$(CXX) $(CXXFLAGS) $< -o $@

compare: main.out correct.out random_case.out check.cpp
	$(CXX) $(CXXFLAGS) -DCOMPARE_RESULT check.cpp -o check.out
	mkdir -p $(RANDOM_DIR)
	make clean_txt
	./check.out

verify: main.out verify.out random_case.out check.cpp
	$(CXX) $(CXXFLAGS) -DVERIFY_RESULT check.cpp -o check.out
	mkdir -p $(RANDOM_DIR)
	make clean_txt
	./check.out

clean:
	$(RM) *.o
	$(RM) *.out

clean_txt:
	$(RM) -r $(RANDOM_DIR)/case*

clean_all: clean clean_txt
