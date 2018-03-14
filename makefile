CC = gcc
CFLAGS = -Wall -Wextra -g -O0
CLIBS =
COBJS = test_sim_device.o sim_device.o log.o
TARGET = test_sim_device

$(TARGET): $(TARGET).o sim_device.o log.o
	$(CC) -o $(TARGET) $(CFLAGS) $(COBJS)
test_sim_device.o: test_sim_device.c
	$(CC) $(CFLAGS) -c $<
log.o: log.c log.h
	$(CC) $(CFLAGS) -c $<
sim_device.o: sim_device.c sim_device.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o $(TARGET)

