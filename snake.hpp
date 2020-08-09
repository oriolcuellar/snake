#ifndef snake_HPP
#define snake_HPP
#include <SFML/Graphics.hpp>
#include "comida.hpp"

#include <iostream>
#include <vector>
using namespace std;
using namespace sf;
struct casilla{
    int dir;//derecha, abajo, izquierda, arriba
    int cost;//-1 inexplorado, distancia hasta el origen
    string soy;//suelo, manzana, cuerpo
};
typedef  vector < vector < casilla > > matriz;//mapa
struct body{
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    int x4;
    int y4;

};
class snake{
    public:
    //constructor
        snake(RenderWindow&);
    //modificador
        bool automatico(comida);
        void movimiento();
        void actualiza();
        void comer();
    //consultor
        pair <int,int> posicion();
        vector <body> posiciones();
        bool choque();
        int size();
    private:
        body head;
        vector <body> vec;
        RenderWindow& app;
        int mov;//1 derecha, 2 abajo, 3 izquierda, 4 arriba
        int quiero;
};
#endif
