CC = gcc
CFLAGS = -g $(shell pkg-config --cflags gtk4)
LDFLAGS = $(shell pkg-config --libs gtk4) -lusb-1.0
SRC = main.c gui.c usb.c
OBJ = $(SRC:.c=.o)
TARGET = main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
