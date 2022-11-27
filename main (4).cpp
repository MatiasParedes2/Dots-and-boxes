#include <iostream>
#include <vector>

using namespace std;
//Se crea el objeto figura que componen el objeto tablero
#include <iostream>
#include "recursos.h"
using namespace std;

void delay(int secs) {
    for(int i = (time(nullptr) + secs); time(nullptr) != i; time(nullptr));
}




int main() {
    int opcion;
    char nombre;
    int turno = 1;
    int cuadrados_restantes_6x6 = 36, cuadrados_restantes_10x10 = 100;

    cout << "Dots & Boxes (Modo PvP)" << endl;
    cout << "~~~~";
    delay(1);
    cout << "~~~~";
    delay(1);
    cout << "~~~~";
    delay(1);
    cout << "~~~~";
    delay(1);
    cout << "~~~~";
    delay(1);
    cout << "~~~" << endl;
    delay(1);
    cout << endl << "Elija el tamanio de su tablero" << endl;
    cout << "1. Tablero 6 x 6" << endl;
    cout << "2. Tablero 10 x 10" << endl;
    cout << "0. Salir" << endl;
    auto* tablero = new tablero_t();
    cin>>opcion;
    while (opcion>2 || opcion<0){
        cout<<"Opcion no valida, vuelva a intentarlo"<<endl;cin>>opcion;
    }
    if (opcion==1){
        tablero->set_dimensions(6);
    }
    else if (opcion==2){
        tablero->set_dimensions(10);
    }
    else if (opcion==0){
        cout<<"Juego Terminado, hasta pronto"<<endl;
        return 0;
    }
    jugador_t jugador1;
    cout << endl << "Introduzca inicial de jugador 1 (solo un digito): "; cin >> nombre;
    jugador1<<nombre;
    cout << endl << "Introduzca inicial de jugador 2 (solo un digito): ";cin>>nombre;
    while (jugador1.get_nombre()==nombre){
        cout<<"Nombre del jugador 2 es igual al del jugar 1, intente otra vez: "<<endl;cin>>nombre;
    }
    jugador_t jugador2;
    jugador2<<nombre;
    cout << endl << "Registrando";
    delay(1);
    cout << ".";
    delay(1);
    cout << ".";
    delay(1);
    cout << ".";
    delay(1);
    cout << endl;
    delay(1);
    tablero->set_jugadores(jugador1,jugador2);
    cout << endl << "Tablero CREADO!!" << endl << endl;
    cout << endl << "INICIANDO PARTIDA"<<endl;
    tablero->crear();
    tablero->rellenar_tab();
    tablero->imprimir_tab();
    cout << endl;
    char c;
    while (jugador1.get_cuadrados_obtenidos()+jugador2.get_cuadrados_obtenidos()!=tablero->cuadrantes){
        if (turno%2==1){
            cout << endl << "Turno de jugador 1" << endl;
            tablero->turno_jugador(turno,jugador1);
            tablero->imprimir_tab();
        }
        else if (turno%2!=1){
            cout << endl << "Turno de jugador 2" << endl;
            tablero->turno_jugador(turno,jugador2);
            tablero->imprimir_tab();
        }
    }
}

