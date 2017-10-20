all:
	g++ generator.c main.cpp -o start -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fPIC

clean:
	rm -rf  start *.o
