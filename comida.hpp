#ifndef COMIDA_HPP
#define COMIDA_HPP
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace sf;
class comida{
    public:
    //constructor
        comida(RenderWindow&);
    //modificador
        void reaparecer(int);
        void actualiza();
    //consultor
        pair <int,int> posicion();
    private:
        RenderWindow &app;
        int x;
        int y;


};
#endif