//
// Created by Usuario on 11/11/2022.
//

#ifndef PROYECTO_RECURSOS_H
#define PROYECTO_RECURSOS_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class figura_t{

    int ubicacion_x=0;
    int ubicacion_y=0;
    string orientacion;  //Solo aplica en el caso de lineas
    string estado;  //Indica si la linea o cuadrante ya esta usado
    string tipo;  //El tipo define si es punto, linea o cuadrante
    char pertenencia;  //Solo para cuadrantes, indica a que jugador le pertenece
    vector<figura_t>puntos;  //Las lineas contienen 2 puntos y los cuadrantes contienen 4 puntos
    vector<figura_t>aristas;  //Solo los cuadrantes tienen 4 aristas

public:
//Constructores
    figura_t()=default;
    figura_t(int x,int y):ubicacion_x(x),ubicacion_y(y){}
//Metodos setters y getters para obtener atributos de la figura
    void set_estado(string status){estado=status;}
    void set_orientacion(string o){orientacion=o;}
    void set_tipo(string type){tipo=type;}
    void set_pertenencia(char possession){pertenencia=possession;}
    string get_estado()  {return estado;}
    string get_orientacion(){return orientacion;}
    void agregar_punto(figura_t p){puntos.push_back(p);}
    void agregar_linea(figura_t l){aristas.push_back(l);}
//El metodo imprimir imprime un caracter en base a su estado (abierto o cerrado) y el tipo de figura
    void imprimir(){
        if (estado=="abierto" && orientacion=="horizontal"){
            cout<<"   ";
        }
        else if (estado=="abierto" && tipo=="cuadrante"){
            cout<<"   ";
        }
        else if (estado=="abierto" && orientacion=="vertical"){
            cout<<" ";
        }
        else if (estado=="cerrado") {
            if (tipo=="linea"){
                if (orientacion=="vertical"){
                    cout<<"|";
                }
                else if (orientacion=="horizontal") {
                    cout<<"---";
                }
            }
            else if (tipo=="punto"){
                cout<< "+";
            }
            else if (tipo=="cuadrante") {
                cout<<" "<<pertenencia<<" ";
            }
        }
    }
    ~figura_t(){}
};


class jugador_t {
    char nombre;
    int cuadrados_obtenidos = 0;
public:
    void operator<<(char c){
        nombre=c;
    }
    jugador_t() = default;
    jugador_t(char _n) : nombre(_n){}

    char get_nombre(){return nombre;}

    int get_cuadrados_obtenidos(){return cuadrados_obtenidos;}

    void cuadrado_obtenido(int n){
        cuadrados_obtenidos=cuadrados_obtenidos+n;
    }

    ~jugador_t(){}
};


//Se crea objeto tablero donde estan las figuras y se realizan los movimientos
class tablero_t{
public:
    jugador_t jug1;
    jugador_t jug2;
    int filas=0;
    int columnas=0;
    int cuadrantes=0;
    figura_t** matriz= new figura_t *[filas];
//Constructor que recibe filas y columnas
    tablero_t(){}
//El metodo crear sirve para definir la matriz de figuras_t
    void set_dimensions(int n){
        filas=2*n+1;
        columnas=2*n+1;
        cuadrantes=n*n;
    }
    void set_jugadores(jugador_t j1,jugador_t j2){
        jug1=j1;
        jug2=j2;
    }
    void crear(){
        for (int i=0;i<filas;++i){
            matriz[i]=new figura_t [columnas];
            for (int j=0;j<columnas;++j){
                matriz[i][j]=figura_t(i,j);
            }
        }
    }
//El metodo sirve para especificar el tipo de figura y su estado inicial (puntos cerrados, lineas abiertas y cuadrantes abiertos sin pertenencia)
    void rellenar_tab(){
        for (int i=0;i<filas;i=i+2){
            for (int j=0;j<columnas;j=j+2){
                //Las figuras en este tipo de coordenadas seran puntos
                matriz[i][j].set_tipo("punto");
                matriz[i][j].set_estado("cerrado");
            }
        }
        for (int i=0;i<filas;++i){
            for (int j=0;j<columnas;++j){
                if (i%2==0){//Las figuras con este tipo de condicion seran lineas
                    if (j%2!=0){//Las lineas con este tipo de condicion seran horizontales
                        matriz[i][j].set_tipo("linea");
                        matriz[i][j].set_orientacion("horizontal");
                        matriz[i][j].set_estado("abierto");
                        //Las lineas horizontales tienen 2 puntos a sus lados
                        matriz[i][j].agregar_punto(matriz[i][j-1]);
                        matriz[i][j].agregar_punto(matriz[i][j+1]);
                    }
                }
                else {
                    if (j%2==0){//Las lineas con este tipo de condicion seran verticales
                        matriz[i][j].set_tipo("linea");
                        matriz[i][j].set_orientacion("vertical");
                        matriz[i][j].set_estado("abierto");
                        //Las lineas verticales tienen 2 puntos arriba y abajo
                        matriz[i][j].agregar_punto(matriz[i-1][j]);
                        matriz[i][j].agregar_punto(matriz[i+1][j]);
                    }
                }
            }
        }
        for (int i=0;i<filas;++i){
            for (int j=0;j<columnas;++j){
                if (i%2!=0 && j%2!=0){//Las figuras que cumplan con la condicion seran cuadrantes
                    matriz[i][j].set_tipo("cuadrante");
                    matriz[i][j].set_estado("abierto");
                    //Los cuadrantes contienen 4 puntos en sus esquinas
                    matriz[i][j].agregar_punto(matriz[i+1][j+1]);
                    matriz[i][j].agregar_punto(matriz[i-1][j-1]);
                    matriz[i][j].agregar_punto(matriz[i+1][j-1]);
                    matriz[i][j].agregar_punto(matriz[i-1][j+1]);
                    //Los cuadrantes contienen 4 lineas en sus lados
                    matriz[i][j].agregar_linea(matriz[i][j+1]);
                    matriz[i][j].agregar_linea(matriz[i][j-1]);
                    matriz[i][j].agregar_linea(matriz[i+1][j]);
                    matriz[i][j].agregar_linea(matriz[i-1][j]);
                }
            }
        }
    }
//Metodo para imprimir el tablero con sus figuras segun su tipo y estado
    void imprimir_tab(){
        for (int i=0;i<filas;++i){
            for (int j=0;j<columnas;++j){
                matriz[i][j].imprimir();
            }
            cout<<endl;
        }
    }
    void trazar_linea(int lin_x,int lin_y){
        matriz[lin_x][lin_y].set_estado("cerrado");
    }
    bool cierra_cuadrante(int lin_x,int lin_y,char c,int& cuadrante_obtenido){
        int n=0;
        if (lin_x==0){
            if (matriz[lin_x+1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x+2][lin_y].get_estado()=="cerrado" && matriz[lin_x+1][lin_y+1].get_estado()=="cerrado"){
                matriz[lin_x+1][lin_y].set_estado("cerrado");
                matriz[lin_x+1][lin_y].set_pertenencia(c);
                n=n+1;
                cuadrante_obtenido=cuadrante_obtenido+n;
                return true;
            }
        }
        else if (lin_x==filas-1){
            if (matriz[lin_x-1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x-2][lin_y].get_estado()=="cerrado" && matriz[lin_x-1][lin_y+1].get_estado()=="cerrado"){
                matriz[lin_x+1][lin_y].set_estado("cerrado");
                matriz[lin_x+1][lin_y].set_pertenencia(c);
                n=n+1;
                cuadrante_obtenido=cuadrante_obtenido+n;
                return true;
            }
        }
        else if (lin_y==0){
            if (matriz[lin_x-1][lin_y+1].get_estado()=="cerrado" && matriz[lin_x][lin_y+2].get_estado()=="cerrado" && matriz[lin_x+1][lin_y+1].get_estado()=="cerrado"){
                matriz[lin_x+1][lin_y].set_estado("cerrado");
                matriz[lin_x+1][lin_y].set_pertenencia(c);
                n=n+1;
                cuadrante_obtenido=cuadrante_obtenido+n;
                return true;
            }
        }
        else if (lin_y==columnas-1){
            if (matriz[lin_x-1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x][lin_y-2].get_estado()=="cerrado" && matriz[lin_x+1][lin_y-1].get_estado()=="cerrado"){
                matriz[lin_x+1][lin_y].set_estado("cerrado");
                matriz[lin_x+1][lin_y].set_pertenencia(c);
                n=n+1;
                cuadrante_obtenido=cuadrante_obtenido+n;
                return true;
            }
        }
        else {
            if (matriz[lin_x][lin_y].get_orientacion()=="horizontal"){
                if (matriz[lin_x-1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x-2][lin_y].get_estado()=="cerrado" && matriz[lin_x-1][lin_y+1].get_estado()=="cerrado"){
                    matriz[lin_x-1][lin_y].set_estado("cerrado");
                    matriz[lin_x-1][lin_y].set_pertenencia(c);
                    n=n+1;
                }
                if (matriz[lin_x+1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x+2][lin_y].get_estado()=="cerrado" && matriz[lin_x+1][lin_y+1].get_estado()=="cerrado"){
                    matriz[lin_x+1][lin_y].set_estado("cerrado");
                    matriz[lin_x+1][lin_y].set_pertenencia(c);
                    n=n+1;
                }
                if (n!=0){
                    cuadrante_obtenido=cuadrante_obtenido+n;
                    return true;
                }
            }
            else if (matriz[lin_x][lin_y].get_orientacion()=="vertical"){
                if (matriz[lin_x-1][lin_y-1].get_estado()=="cerrado" && matriz[lin_x][lin_y-2].get_estado()=="cerrado" && matriz[lin_x+1][lin_y-1].get_estado()=="cerrado"){
                    matriz[lin_x][lin_y-1].set_estado("cerrado");
                    matriz[lin_x][lin_y-1].set_pertenencia(c);
                    n=n+1;
                }
                if (matriz[lin_x-1][lin_y+1].get_estado()=="cerrado" && matriz[lin_x][lin_y+2].get_estado()=="cerrado" && matriz[lin_x+1][lin_y+1].get_estado()=="cerrado"){
                    matriz[lin_x][lin_y+1].set_estado("cerrado");
                    matriz[lin_x][lin_y+1].set_pertenencia(c);
                    n=n+1;
                }
                if (n!=0){
                    cuadrante_obtenido=cuadrante_obtenido+n;
                    return true;
                }
            }
        }
        return false;
    }
    void turno_jugador(int& turno,jugador_t& j){
        int cuadrante_obtenido=0;
        char c=j.get_nombre();
        int x1;
        int y1;
        int x2;
        int y2;
        cout << endl << "Ingrese las coordenadas del punto origen: " << endl;
        cin >> x1;
        cin >> y1;
        cout << endl << "Ingrese las coordenadas del punto llegada: " << endl;
        cin >> x2;
        cin >> y2;
        while ((x2+y2!=x1+y1-1)&&(x2+y2!=x1+y1+1)){
            cout << endl << "Destino no valido. Ingrese las coordenadas del punto llegada: " << endl;
            cin >> x2;
            cin >> y2;
        }
        int lin_x;
        int lin_y;
        if (x1==x2){
            lin_x=(x1-1)*2;
            lin_y=((2*(y1-1))+(2*(y2-1)))/2;
        }
        else if (y1==y2){
            lin_y=(y1-1)*2;
            lin_x=((2*(x1-1))+(2*(x2-1)))/2;;
        }
        trazar_linea(lin_x,lin_y);
        if (not cierra_cuadrante(lin_x,lin_y,c,cuadrante_obtenido)){
            turno=turno+1;
            j.cuadrado_obtenido(cuadrante_obtenido);
        }

    }
    ~tablero_t(){}
};





#endif //PROYECTO_RECURSOS_H
