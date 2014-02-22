all: test.out
	./$<

test.out: gtest.cpp
	g++ $< -o $@ -lgtest ../../lib/libjjconfig.a -pthread

.PHONY: all