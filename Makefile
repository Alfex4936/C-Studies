TARGET	= main
CFLAGS	= 
LDFLAGS	=

build:
	gcc main.c -I C:\Users\ccjoo\Anaconda3\include -LC:\Users\ccjoo\Anaconda3\libs -lpython37 -o main.exe

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.dSYM
