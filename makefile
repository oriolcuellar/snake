all:snake

snake:main.cpp
	g++ main.cpp -o sfml comida.cpp snake.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o
