#include "comida.hpp"
#include "snake.hpp"

#ifndef COLISION_HPP
#define COLISION_HPP

bool collide(comida &manzana, snake &serpiente){
    pair <int, int> mpar;
    pair <int, int> spar;
    mpar=manzana.posicion();
    spar=serpiente.posicion();
    bool trobat=false;
    if (mpar.first/20==spar.first/20 and mpar.second/20==spar.second/20){
        srand(time(NULL));
        int n=rand()%100000;
        while(trobat==false){
            n++;
            trobat=true;
            manzana.reaparecer(n);
            for (int i=0;i<serpiente.posiciones().size();i++){
                if (serpiente.posiciones()[i].x1==manzana.posicion().first and serpiente.posiciones()[i].y1==manzana.posicion().second) trobat=false;
                if (serpiente.posiciones()[i].x2==manzana.posicion().first and serpiente.posiciones()[i].y2==manzana.posicion().second) trobat=false;
                if (serpiente.posiciones()[i].x3==manzana.posicion().first and serpiente.posiciones()[i].y3==manzana.posicion().second) trobat=false;
                if (serpiente.posiciones()[i].x4==manzana.posicion().first and serpiente.posiciones()[i].y4==manzana.posicion().second) trobat=false;
            }
            if (serpiente.posicion().first==manzana.posicion().first and serpiente.posicion().second==manzana.posicion().second) trobat=false;
        }
        serpiente.comer();
        return true;
    }
    return false;

}



#endif