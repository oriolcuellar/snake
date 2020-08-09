
#include "comida.hpp"
#include "snake.hpp"
#include <SFML/Graphics.hpp>
#include "colision.hpp"
#include "datos.hpp"
RenderWindow window(VideoMode(tam_x, tam_y), "snake"); //ventana
void contador(snake serpiente){
    Text texto;
    String cadena=to_string(serpiente.size());
    texto.setString(cadena);
    texto.setPosition(10, 10);
    texto.setCharacterSize(30);
    texto.setFillColor(Color::White);
	Font fuente;
	if (!fuente.loadFromFile("explosive.ttf"))
	{
		//return EXIT_FAILURE;
	}    
    texto.setFont(fuente);
    window.draw(texto);
}

int main()
{
    int n=60;
    window.setFramerateLimit(60);
    snake serp(window);
    comida manzana(window);
    while (window.isOpen() and serp.choque()==false and serp.size()!=casillas*casillas){//bucle del juego
    //mientras pantalla esta abierta, no ha chocado y no ha completado el juego

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)//si cierras la ventana, el la cierra del todo
                window.close();
        }

        window.clear();//borra pantalla

        //poner automatico con comentario para control manual
        serp.automatico(manzana);//decide donde se mueve

        for (int i=0;i<4;i++){//mover 4 pixeles hasta la siguiente casilla
            window.clear();//limpia pantalla
            serp.movimiento();//movimiento
            serp.actualiza();//pinta en pantalla serpiente
            manzana.actualiza();//pinta en pantalla serpiente
            contador(serp);//pinta el contador
            window.display();//actualiza pantalla
        }
        collide(manzana, serp);//comprueba si ha chocado o comido
        contador(serp);//pinta el contador
        manzana.actualiza();//pinta en pantalla manzana
        window.display();//actualiza pantalla
    }
    if (serp.size()==casillas*casillas){
        cout<<endl<<endl<<"te has pasado el juego";
    }
    cout<<endl<<"tamaño "<<serp.size()<<endl;
    return 0;
}
