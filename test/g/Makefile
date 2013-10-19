#INC = -I /home/johny/.local/include/
#LIB = -L /home/johny/.local/lib/

all: test.out
	./$<

test.out: gtest.cpp
	g++ $< -o $@ -lgtest ../../lib/libjjconfig.a -pthread

.PHONY: all