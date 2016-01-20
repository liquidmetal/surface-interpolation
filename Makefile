CC = g++
CFLAGS  = -g -Wall
TARGET = rbf

 all: $(TARGET).cpp
	 			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
