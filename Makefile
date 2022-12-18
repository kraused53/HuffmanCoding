ERROR = -Wvla -Werror
WARNING = -Wall -Wshadow --pedantic
GPP = g++ -g $(WARNING) $(ERROR)

SRCS = main.cpp llist.cpp btree.cpp
OBJS = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	$(GPP) $(OBJS) -o main

.cpp.o:
	$(GPP) -c $*.cpp

testall: test1 test2

test1: all
	@seq 0 29 > ./inputs/input1.txt
	@shuf ./inputs/input1.txt -o ./inputs/input1.txt
	@echo "Test a small sequence"
	./main ./inputs/input1.txt > ./outputs/output1.txt
	diff ./outputs/output1.txt ./expected/expected1.txt

test2: all
	@seq 0 100000 > ./inputs/input2.txt
	@shuf ./inputs/input2.txt -o ./inputs/input2.txt
	@echo "Test a large sequence"
	./main ./inputs/input2.txt > ./outputs/output2.txt
	diff ./outputs/output2.txt ./expected/expected2.txt

clean:
	rm -f main *.o