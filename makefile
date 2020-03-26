CC=gcc
CFLAGS=-g
SRC=launch.c
OBJ=launch.o
SRCT=tube.c
OBJT=tube.o
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