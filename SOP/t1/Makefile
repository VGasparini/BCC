OBJS1	= ex1.o
OBJS2	= ex2.o matrix.o
SOURCE	= ex1.c ex2.c matrix.c
HEADER	= matrix.h
OUT1	= ex1
OUT2	= ex2
CC	 	= gcc
FLAGS	= -g -c
LFLAGS	= -lpthread

all: clean $(OBJS1) $(OBJS2)
	$(CC) -g $(OBJS1) -o $(OUT1) $(LFLAGS)
	$(CC) -g $(OBJS2) -o $(OUT2) $(LFLAGS)

ex1.o: ex1.c
	$(CC) $(FLAGS) ex1.c 

ex2.o: ex2.c
	$(CC) $(FLAGS) ex2.c 

matrix.o: matrix.c
	$(CC) $(FLAGS) matrix.c 

clean:
	rm -f $(OBJS1) $(OBJS2) $(OUT1) $(OUT2)
