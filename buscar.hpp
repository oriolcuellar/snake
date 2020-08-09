#ifndef BUSCAR_HPP
#define BUSCAR_HPP
#include "snake.hpp"
using namespace std;
    void camino(bool &trobat, bool &posible, matriz &mat, int x, int y){
        //Pre: trobat y bool son 2 boleanos, mat es matriz de structs casilla, x e y son enteros
        //Post: Pinta el mapa entero con distancias y direcciones desde la salida (unica que tiene dist 0 al  empezar)
        //hasta el objetivov x y
        int cont=0;
        while (trobat==false and posible==true){//mapa de distancias y camino mas corto hasta x, y
            int aux=0;
            for (int j=0;j<casillas;j++){
                for (int i=0;i<casillas;i++){
                    if (mat[i][j].cost==cont){
                        if (j!=casillas-1 and mat[i][j+1].soy!="cuerpo" and (mat[i][j+1].cost+1>mat[i][j].cost or mat[i][j+1].cost==-1) and mat[i][j].dir!=2){
                            mat[i][(j+1)].dir=4;
                            mat[i][(j+1)].cost=mat[i][j].cost+1;
                        }
                        if (j!=0 and mat[i][j-1].soy!="cuerpo" and (mat[i][j-1].cost+1>mat[i][j].cost or mat[i][j-1].cost==-1) and mat[i][j].dir!=4){            
                            mat[i][j-1].dir=2;
                            mat[i][j-1].cost=mat[i][j].cost+1;
                            }
                        if (i!=casillas-1 and mat[i+1][j].soy!="cuerpo" and (mat[i+1][j].cost+1>mat[i][j].cost or mat[i+1][j].cost==-1) and mat[i][j].dir!=1){
                            mat[i+1][j].dir=3;
                            mat[i+1][j].cost=mat[i][j].cost+1;
                        }
                        if (i!=0 and mat[i-1][j].soy!="cuerpo" and (mat[i-1][j].cost+1>mat[i][j].cost or mat[i-1][j].cost==-1) and mat[i][j].dir!=3){
                            mat[i-1][j].dir=1;
                            mat[i-1][j].cost=mat[i][j].cost+1;
                        }
                        aux++;
                    }
                }
            }
            if (aux==0) posible=false; //si recorres todos los caminos posibles para

            if (mat[x/20][y/20].cost!=-1) trobat=true;//para cuando lo encuentres
            cont++;
        }
    }

#endif