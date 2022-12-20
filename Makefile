ERROR = -Wvla -Werror
WARNING = -Wall -Wshadow --pedantic
GPP = g++ -g $(WARNING) $(ERROR)

SRCS = main.cpp llist.cpp btree.cpp
OBJS = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	$(GPP) $(OBJS) -o main

.cpp.o:
	$(GPP) -c $*.cpp

testall: test1 test2 test3 test4

test1: all
	@echo "Delete a Node with no children"
	./main ./inputs/input1.txt > ./outputs/output1.txt
	diff ./outputs/output1.txt ./expected/expected1.txt

test2: all
	@echo "Delete a Node with only left child children"
	./main ./inputs/input2.txt > ./outputs/output2.txt
	diff ./outputs/output2.txt ./expected/expected2.txt
	
test3: all
	@echo "Delete a Node with only right child children"
	./main ./inputs/input3.txt > ./outputs/output3.txt
	diff ./outputs/output3.txt ./expected/expected3.txt

test4: all
	@echo "Delete a Node with two children"
	./main ./inputs/input4.txt > ./outputs/output4.txt
	diff ./outputs/output4.txt ./expected/expected4.txt


clean:
	rm -f main *.o
	rm ./outputs/*