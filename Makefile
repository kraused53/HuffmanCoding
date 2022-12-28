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
	valgrind --leak-check=yes ./main ./inputs/input1.bin ./outputs/valgrind.log

testall: test1 test2 test3 test4 test5 test6 test7 test8

test1: all
	./main ./inputs/input1.bin ./outputs/output1.txt
	diff ./outputs/output1.txt ./expected/expected1.txt

test2: all
	./main ./inputs/input2.bin ./outputs/output2.txt
	diff ./outputs/output2.txt ./expected/expected2.txt

test3: all
	./main ./inputs/input3.bin ./outputs/output3.txt
	diff ./outputs/output3.txt ./expected/expected3.txt

test4: all
	./main ./inputs/input4.bin ./outputs/output4.txt
	diff ./outputs/output4.txt ./expected/expected4.txt

test5: all
	./main ./inputs/input5.bin ./outputs/output5.txt
	diff ./outputs/output5.txt ./expected/expected5.txt

test6: all
	./main ./inputs/input6.bin ./outputs/output6.txt
	diff ./outputs/output6.txt ./expected/expected6.txt

test7: all
	./main ./inputs/input7.bin ./outputs/output7.txt
	diff ./outputs/output7.txt ./expected/expected7.txt

test8: all
	./main ./inputs/input8.bin ./outputs/output8.txt
	diff ./outputs/output8.txt ./expected/expected8.txt

clean:
	rm -f main *.o
	rm ./outputs/*