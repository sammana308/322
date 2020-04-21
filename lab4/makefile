EXECUTABLE=dining-p launch-philosophers
SOURCE=dining-p.c

all:$(EXECUTABLE)

dining-p: $(SOURCE)
	gcc -c dining-p.c -lpthread -lrt -Wall -Wextra
	gcc -o dining-p dining-p.o -lpthread -lrt

launch-philosophers:
	chmod +x launch-philosophers.sh
clean:
	rm dining-p.c dining-p.o dining-p launch-philosophers launch-philosophers.sh
       
