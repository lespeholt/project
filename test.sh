#!/bin/bash
if /usr/local/bin/g++-4.8 -Wall -Wa,-q -std=c++11 src/gtest.cpp src/*_test.cpp -I src/ -lGtest -lGtest_main -DGTEST_USE_OWN_TR1_TUPLE=1 -o test.out ; then
	./test.out
fi
