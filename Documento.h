#pragma once
#include"List.h"
#include<fstream>
using namespace std;
class documento {
	string nombre;
    int hora;
public:
	documento(string n,int h):nombre(n),hora(h){}
    friend ostream& operator << (ostream& o, documento& p) {
        o << p.nombre << " " << p.hora << endl;
        return o;
    }
    void print() {
        string direccion = nombre + ".txt";
        ifstream archivo(direccion);
        string linea;
        while (getline(archivo,linea))
        {
            cout << linea << endl;
        }

    }
};
