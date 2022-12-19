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
	./main ./inputs/input1.txt > ./outputs/output1.txt
	diff ./outputs/output1.txt ./expected/expected1.txt

test2: all
	@echo "No second test yet"

clean:
	rm -f main *.o
	rm ./outputs/*