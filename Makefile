ERROR = -Wvla -Werror
WARNING = -Wall -Wshadow --pedantic
GPP = g++ -g $(WARNING) $(ERROR)

SRCS = main.cpp list.cpp tree.cpp decode.cpp utilities.cpp
OBJS = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	$(GPP) $(OBJS) -o main

.cpp.o:
	$(GPP) -c $*.cpp

memcheck: all
	@echo "Check for memory leaks"
	valgrind --leak-check=yes ./main ./inputs/input1.txt ./outputs/output1.txt

testall: test1 test2

test1: all
	./main ./inputs/input1.txt ./outputs/output1.txt
	diff ./outputs/output1.txt ./expected/expected1.txt

test2: all
	./main ./inputs/input2.txt ./outputs/output2.txt
	diff ./outputs/output2.txt ./expected/expected2.txt

clean:
	rm -f main *.o
	rm ./outputs/*