TARGET	= main
CFLAGS	= 
LDFLAGS	=

build:
	chcp 65001 > NUL& gcc main.c -I Anaconda3\include -LAnaconda3\libs -lpython37 -o main.exe
	./main

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.dSYM
