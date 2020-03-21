VPATH = src
OUT_PATH=./bin

CC=g++
CFLAGS=-I include
LDFLAGS=-framework CoreServices

main: watchs.o clean_bin
	$(CC) $(CFLAGS) $< -o $(OUT_PATH)/watchs $(LDFLAGS)

main.o: watchs.cpp
	$(CC) $(CFLAGS) -c $<

clean_bin:
	mkdir -p bin
	rm -rf bin/*
