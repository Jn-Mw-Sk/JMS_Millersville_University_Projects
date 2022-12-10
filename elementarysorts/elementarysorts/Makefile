CXXFLAGS := -Wall -std=c++17

.PHONY: all clean handin

driver : driver.cpp

driver.cpp : sort.hpp

handin : handin.tar

handin.tar : driver.cpp sort.hpp
	tar cvf $@ $^

all : driver handin

clean :
	rm -f driver handin.tar
