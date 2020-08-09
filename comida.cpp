#include "comida.hpp"
#include "datos.hpp"
comida::comida(RenderWindow &a) : app(a)
//Pre: inicializa valores
//Post: true
{
    
    srand(time(NULL));
    x=1;
    y=1;
    while (x%20!=0){
        x=rand()%(tam_x);
    }
    while (y%20!=0){
        y=rand()%(tam_y);
    }
}
void comida::reaparecer(int n){
    //Pre: entero n 
    //Post: True
    
    srand(n);
    x=1;
    y=1;
    bool trobat=false;
    while (x%20!=0){
        x=rand()%(tam_x);
    }
    while (y%20!=0){
        y=rand()%(tam_y);
    }
    

}
void comida::actualiza(){
    //Pre: True
    //Post: pinta en pantalla
    CircleShape shape(10.f);
    shape.setFillColor(Color::Blue);
    shape.setPosition(x,y);
    app.draw(shape);

}
pair <int, int> comida::posicion(){
    //Pre: True
    //Post: devuelve un pair con la posicion de enteros x, y
    pair <int,int> par;
    par=make_pair (x,y);
    return par;

}