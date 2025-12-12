CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = device_manager
OBJS    = main.o UI.o method.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c UI.h
	$(CC) $(CFLAGS) -c main.c

UI.o: UI.c UI.h method.h struct.h
	$(CC) $(CFLAGS) -c UI.c

method.o: method.c method.h struct.h
	$(CC) $(CFLAGS) -c method.c

clean:
	rm -f $(OBJS) $(TARGET)
