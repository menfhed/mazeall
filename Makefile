all:
	g++ test1.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf  app *.o