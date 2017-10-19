all:
	g++ main.cpp -o start -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf  start *.o
