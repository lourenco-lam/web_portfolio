# Makefile for Calculator

CC = gcc
CFLAGS = -Wall -g -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib
LDLIBS = -lpthread -lreadline

TARGET = calculator
OBJS = calculator.o operations.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

calculator.o: calculator.c calculator.h
	$(CC) $(CFLAGS) -c calculator.c

operations.o: operations.c calculator.h
	$(CC) $(CFLAGS) -c operations.c

clean:
	rm -f *.o $(TARGET)