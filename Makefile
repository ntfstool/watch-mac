VPATH = src
OUT_PATH=./bin

CC=g++
CFLAGS=-I include
LDFLAGS=-framework CoreServices

main: watch-mac.o clean_bin
	$(CC) $(CFLAGS) $< -o $(OUT_PATH)/watch-mac  $(LDFLAGS)
	cp $(OUT_PATH)/watch-mac  $(OUT_PATH)/../npm/bin/watch-mac

main.o: watch-mac.cpp
	$(CC) $(CFLAGS) -c $<

clean_bin:
	mkdir -p bin
	rm -rf bin/*
