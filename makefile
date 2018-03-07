CC = gcc
CFLAGS = -Wall -Wextra -g -O0
CLIBS =
TARGET = sim_device

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(CFLAGS) $(TARGET).c

clean:
	-rm -f *.o $(TARGET)

