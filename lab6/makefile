EXECUTABLE1=spirit
EXECUTABLE2=mole
SOURCE1=spiritd.c
SOURCE2=mole.c
OBJ1=spiritd.o
OBJ2=mole.o

CC=gcc
CFLAGS=-g

all: $(EXECUTABLE1) $(EXECUTABLE2)


$(EXECUTABLE1): $(SOURCE1)
	$(CC) $(CFLAGS) -c $(SOURCE1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)

$(EXECUTABLE-T): $(SOURCE2)
	$(CC) $(CFLAGS) -c $(SOURCE2)
	$(CC) $(CFLAGS) -o $@ $(OBJ2)

clean:
	rm -f $(EXECUTABLE1) $(EXECUTABLE2) $(OBJ1) $(OBJ2) *~
