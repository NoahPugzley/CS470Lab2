CC=gcc
CFLAGS=-Wall -g
TARGET=process_management

all: $(TARGET)

$(TARGET): $(TARGET).c
		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm -f $(TARGET)
