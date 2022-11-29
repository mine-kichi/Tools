TARGET = test
OBJS = test.o ImRGB.o
SRCS = test.c ImRGB.c

CFLAGS =  -O3

CC = gcc


$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

.c.o:	
	$(CC) -c $(CFLAGS) $< 

clean:
	rm -f $(TARGET) *.o core *.core core.* *~

