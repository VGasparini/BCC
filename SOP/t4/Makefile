OBJS1	= ex3.o
OBJS2	= requests.o
SOURCE	= ex3.c requests.c
HEADER	= requests.h
OUT1	= ex3
CC	 	= gcc
FLAGS	= -g -c

all: clean $(OBJS1) $(OBJS2)
	$(CC) -g $(OBJS1) $(OBJS2) -o $(OUT1) $(LFLAGS)

ex3.o: ex3.c
	$(CC) $(FLAGS) ex3.c

requests.o: requests.c
	$(CC) $(FLAGS) requests.c 

clean:
	rm -f $(OBJS1) $(OBJS2) $(OUT1)
