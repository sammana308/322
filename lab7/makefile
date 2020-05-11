EXEC1: matrix_add
EXEC2: matrix_gen 
S1: matrix_add.c
S2: matrix_gen.c
OBJ1: matrix_add.o
OBJ2: matrix_gen.o

CC:gcc
CFLAGS: -Wall -Wextra

all:$(EXEC1) $(EXEC2)

$(EXEC1):
	$(CC) -c $(CFLAGS) $(S1) 
	$(CC) -o $(CFLAGS) $(OBJ1) -lrt
$(EXEC2):
	$(CC) -c $(CFLAGS) $(S2)
	$(CC) -o $(CFLAGS) $(OBJ2) -lrt

clean:
	rm -f $(EXEC1)
	rm -f $(EXEC2)
	rm -f $(OBJ1)
	rm -f $(OBJ2)