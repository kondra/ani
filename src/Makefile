CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags --libs gtk+-2.0 libsoup-2.4`

OBJ1 = main.o ani-net.o ani-parser.o main-window.o

TARGET1 = main

$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $(TARGET1)

main.o: ani-net.o ani-parser.o main-window.o
main-window.o: ani-net.o ani-parser.o

clean:
	rm -f $(TARGET1) *.o 
