CC=gcc
CFLAGS=-g
SRC=Launch.c
OBJ=Launch.o
SRCT=Tube.c
OBJT=Tube.o
all:
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) -o launch $(OBJ)
		$(CC) $(CFLAGS) -c $(SRCT)
		$(CC) $(CFLAGS) -o tube $(OBJT)
launch:
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) -o launch $(OBJ)
tube:
		$(CC) $(CFLAGS) -c $(SRCT)
		$(CC) $(CFLAGS) -o tube $(OBJT)
clean:
		rm -f launch tube $(OBJT) $(SRCT) $(OBJT) $(SRCT)