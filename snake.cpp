#include "snake.hpp"
#include "datos.hpp"
#include "buscar.hpp"
snake::snake(RenderWindow &a) : app(a)
//pre: ventana tipo render window
//Post: Inicializa los valores
{
    
    vector <body> vect;
    vec=vect;
    head.x1=0;
    head.y1=0;
    head.x2=0;
    head.y2=0;
    head.x3=0;
    head.y3=0;
    head.x4=0;
    head.y4=0;
    mov=0;
    quiero=0;
}
bool snake::automatico(comida manzana){ 
    //pre: objeto tipo manzana
    //Post: Buscara camino a manzana, si encuentra revisara si una vez cogida la manzana puedes ir a la cola (para no encerrarte)
    //si alguna de las dos no se cumple, buscas el camino mas lejano a la cola
    pair <int, int> par=manzana.posicion();//posicion de la manzana
    bool ultimo=false;
    if (vec.size()+2==casillas*casillas){//solo me queda 1
        ultimo=true;
    }
    bool encima=false;
    if (par.first/20==head.x1/20 and par.second/20==head.y1/20){//si estas encima de la manzana acaba
         return true;
    }

    matriz mat (casillas, vector < casilla > (casillas));//mapa 1
    for (int j=0;j<casillas;j++){//rellenar con suelo y distancias inexploradas
        for (int i=0;i<casillas;i++){
            mat[i][j].soy="suelo";
            mat[i][j].cost=-1;
            
        }
    }
    mat[par.first/20][par.second/20].soy="manzana";//manzana, objetivo
    int n=vec.size();
    for (int i=0;i<n;i++){//marcar cuerpo en el mapa
        mat[vec[i].x4/20][vec[i].y4/20].soy="cuerpo";
    }     
    
    mat[head.x1/20][head.y1/20].cost=0;//cabeza, buscador

    bool trobat=false;
    
    bool posible=true;
    camino(trobat, posible, mat, par.first, par.second);
    if (posible==false) ultimo=false; //si solo queda una manzana no hay que comprobar que te encierres

    int x=par.first/20;
    int y=par.second/20;
    int aux1=x;
    int aux2=y;
    cout<<endl;
    trobat=false;
    int cont=0;
    while (trobat==false and posible==true){//calcular camino a manzana y marcarlo con cuerpo
        cont++;
        aux1=x;
        aux2=y;
        mat[x][y].soy="cuerpo";
        if (mat[x][y].dir==1) x+=1;
        else if (mat[x][y].dir==2) y+=1;
        else if (mat[x][y].dir==3) x-=1;
        else if (mat[x][y].dir==4) y-=1;
        if (mat[x][y].cost==0){
            trobat=true;
            mat[x][y].cost=-1;
            mat[x][y].soy="cuerpo";
        }
    }
    for (int j=0;j<casillas;j++){ //imprimir mapa i limpiarlo de distancias i direcciones
        for (int i=0;i<casillas;i++){
            cout<<mat[i][j].cost;
            if (mat[i][j].cost!=-1 and mat[i][j].cost<10) cout<<" ";
            mat[i][j].cost=-1;
            mat[i][j].dir=0;
        }
        cout<<endl;
    }
    trobat=false;
    int cx=0;
    int cy=0;
    if(vec.size()>1){
        cx=vec[vec.size()-1].x4;//posiciones de la cola
        cy=vec[vec.size()-1].y4;
    }
    else {trobat=true;}
    if (vec.size()!=0 and posible==true and trobat==false){
        mat[par.first/20][par.second/20].cost=0;//poner a 0 la manzana (para buscar la cola) 
        mat[cx/20][cy/20].soy="manzana";
        cont=0;
        camino(trobat, posible, mat, cx, cy);
    }
    if ((posible==true and trobat==true) or ultimo==true){//se puede ir a la manzana y despues a la cola
        if (aux1<x) quiero =3;
        if (aux1>x) quiero =1;
        if (aux2<y) quiero =4;
        if (aux2>y) quiero =2;
    }
    else{//tiene que hacer el camino largo
        //borrar cuerpo y volver a poner
        for (int j=0;j<casillas;j++){//mapa
            for (int i=0;i<casillas;i++){
                mat[i][j].soy="suelo";
                mat[i][j].cost=-1;
            }
        }
        mat[head.x1/20][head.y1/20].soy="cuerpo";
        for (int j=0;j<vec.size();j++){//cuerpo
            mat[vec[j].x4/20][vec[j].y4/20].soy="cuerpo";
        }
        int cx=0;
        int cy=0;
        if(vec.size()>1){
            cx=vec[vec.size()-1].x4;//posiciones de la cola
            cy=vec[vec.size()-1].y4;
            mat[cx/20][cy/20].cost=0;
            //mat[cx/20][cy/20].soy="manzana";
        }
        trobat=false;
        posible=true;
        cont=0;
        while (trobat==false){//mapa de distancias de cola a resto del mapa
            int aux=0;

            for (int j=0;j<casillas;j++){
                for (int i=0;i<casillas;i++){
                    if (mat[i][j].cost==cont){
                        if (j!=casillas-1 and mat[i][j+1].soy!="cuerpo" and (mat[i][j+1].cost+1>mat[i][j].cost or mat[i][j+1].cost==-1) and mat[i][j].dir!=2){
                            mat[i][(j+1)].cost=mat[i][j].cost+1;
                        }
                        if (j!=0 and mat[i][j-1].soy!="cuerpo" and (mat[i][j-1].cost+1>mat[i][j].cost or mat[i][j-1].cost==-1) and mat[i][j].dir!=4){            
                            mat[i][j-1].cost=mat[i][j].cost+1;
                            }
                        if (i!=casillas-1 and mat[i+1][j].soy!="cuerpo" and (mat[i+1][j].cost+1>mat[i][j].cost or mat[i+1][j].cost==-1) and mat[i][j].dir!=1){
                            mat[i+1][j].cost=mat[i][j].cost+1;
                        }
                        if (i!=0 and mat[i-1][j].soy!="cuerpo" and (mat[i-1][j].cost+1>mat[i][j].cost or mat[i-1][j].cost==-1) and mat[i][j].dir!=3){
                            mat[i-1][j].cost=mat[i][j].cost+1;
                        }
                        aux++;
                    }
                }
            }
            if (aux==0) trobat=true;
            cont++;
        }
        trobat=false;
        int dist=0;
        string direc="";
        if (head.x1/20>0){//moverte a la posicion mas lejana de la cola
            if (mat[(head.x1/20)-1][head.y1/20].cost>dist and mat[(head.x1/20)-1][head.y1/20].soy!="cuerpo" and (mov==3 or mov==2 or mov==4)){
                dist=mat[(head.x1/20)-1][head.y1/20].cost;
                direc="izquierda";
            }
        }
        if (head.x1/20<casillas-1){
            if (mat[(head.x1/20)+1][head.y1/20].cost>dist and mat[(head.x1/20)+1][head.y1/20].soy!="cuerpo" and (mov==1 or mov==4 or mov==2)){
                dist=mat[(head.x1/20)+1][head.y1/20].cost;
                direc="derecha";
            }
        }
        if (head.y1/20>0){
            if (mat[head.x1/20][(head.y1/20)-1].cost>dist and mat[head.x1/20][(head.y1/20)-1].soy!="cuerpo" and (mov==1 or mov==3 or mov==4)){
                dist=mat[head.x1/20][(head.y1/20)-1].cost;
                direc="arriba";
            }
        }
        if (head.y1/20<casillas-1){
            if (mat[head.x1/20][(head.y1/20)+1].cost>dist and mat[head.x1/20][(head.y1/20)+1].soy!="cuerpo" and (mov==1 or mov==2 or mov==3)){
                dist=mat[head.x1/20][(head.y1/20)+1].cost;
                direc="abajo";
            }
        }
        if (direc=="izquierda") quiero=3;
        if (direc=="derecha") quiero=1;
        if (direc=="arriba") quiero=4;
        if (direc=="abajo") quiero=2;
        if (direc==""){//estas en la misma casilla que la manzana, espera a que aparezca
            if (head.x1<vec[vec.size()-1].x4) quiero=1;
            if (head.x1>vec[vec.size()-1].x4) quiero=3;
            if (head.y1<vec[vec.size()-1].y4) quiero=2;
            if (head.y1>vec[vec.size()-1].y4) quiero=4;
        }
        
    }
    return true;

}
void snake::movimiento(){
    //Pre: true
    //Post: actualiza las posiciones de la serpiente y su cuerpo y decide donde ir en caso de que el control sea manual
    if (vec.size()!=0){
        for (unsigned int i=vec.size()-1;i!=0;i--){
            vec[i].x4=vec[i].x3;
            vec[i].x3=vec[i].x2;
            vec[i].x2=vec[i].x1;
            vec[i].x1=vec[i-1].x4;
            vec[i].y4=vec[i].y3;
            vec[i].y3=vec[i].y2;
            vec[i].y2=vec[i].y1;
            vec[i].y1=vec[i-1].y4;
        }
        vec[0].x4=vec[0].x3;
        vec[0].x3=vec[0].x2;
        vec[0].x2=vec[0].x1;
        vec[0].x1=head.x1;
        vec[0].y4=vec[0].y3;
        vec[0].y3=vec[0].y2;
        vec[0].y2=vec[0].y1;
        vec[0].y1=head.y1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) and (mov!=1 and mov!=3))
    {
        quiero=3;
    }
        if (Keyboard::isKeyPressed(Keyboard::Right) and (mov!=1 and mov!=3))
    {
        quiero=1;
    }
        if (Keyboard::isKeyPressed(Keyboard::Up) and (mov!=2 and mov!=4))
    {
        quiero=4;
    }
        if (Keyboard::isKeyPressed(Keyboard::Down) and (mov!=2 and mov!=4))
    {
        quiero=2;
    }
        if (Keyboard::isKeyPressed(Keyboard::P))//parar
    {
        bool trobat=true;
        while (trobat==true){
            if (Keyboard::isKeyPressed(Keyboard::C)){//continuar
                trobat=false;
            }
        }
    }
    if (quiero==1 and head.y1%20==0){
        mov=1;
        quiero=0;
    }
    if (quiero==2 and head.x1%20==0){
        mov=2;
        quiero=0;
    }
    if (quiero==3 and head.y1%20==0){
        mov=3;
        quiero=0;
    }
    if (quiero==4 and head.x1%20==0){
        mov=4;
        quiero=0;
    }
    if (mov==1) head.x1+=5;
    if (mov==2) head.y1+=5;
    if (mov==3) head.x1-=5;
    if (mov==4) head.y1-=5;
}
void snake::actualiza(){
    //Pre: pinta en el mapa la serpiente y su cuerpo
    //Post: true
    CircleShape shape(10.f);
    shape.setFillColor(Color::Green);
    if (vec.size()!=0){
        for (unsigned int i=0;i<vec.size();i++){
        shape.setPosition(vec[i].x4, vec[i].y4);
        if (i==vec.size()-1) shape.setFillColor(Color::White);
        app.draw(shape);            
        }
    }
    shape.setFillColor(Color::Red);
    shape.setPosition(head.x1,head.y1);
    app.draw(shape);


}
void snake::comer(){
    //Pre: true
    //Post: aumenta el tamaño de la serpiente
    int tam=vec.size();
    vector <body> nou(tam+1);
    for (int i=0;i<tam;i++){
        nou[i]=vec[i];
    }
    nou[tam]=nou[tam-1];
    vec=nou;

}
pair <int, int> snake::posicion(){
    //Pre:true
    //Post: devuelve un pair de enteros con la posicion de la cabeza
    pair <int,int> par;
    par=make_pair (head.x1,head.y1);
    return par;

}
bool snake::choque(){
    //Pre: true
    //Post: mira si las posiciones de la cola coinciden con la cabeza
    for (unsigned int i=0;i<vec.size();i++){
        if ((head.x1==vec[i].x1 and head.y1==vec[i].y1) or (head.x1==vec[i].x2 and head.y1==vec[i].y2) or (head.x1==vec[i].x3 and head.y1==vec[i].y3) or (head.x1==vec[i].x4 and head.y1==vec[i].y4)){
            cout<<"choque"<<endl;
            return true;
        }
    }
    if (head.x1>tam_x-20 or head.x1<0) return true;
    if (head.y1>tam_y-20 or head.y1<0) return true;
    return false;
}
int snake::size(){
    //Pre: true
    //Post: numero de casillas que ocupa
    int tam= vec.size()+1;
    return tam;

}
vector <body> snake::posiciones(){
    //Pre: true
    //Post: Un pair con las posiciones x y de la cabeza

    return vec;
}

