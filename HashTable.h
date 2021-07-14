#include <iostream>
#pragma warning(disable:4996)
#include <string>
#include <vector>
#include <list> 
#include"Dirent.h"
#include <Windows.h>
#include <fstream>
#include <functional>
using namespace std;
template <typename T>
class HashTable {
    vector<list<T>> hash;
    T* array;
    function<bool(string)> igual;
    function<bool(string)> inicia;
    function<bool(string)> finaliza;
    function<bool(string)> contiene;
    function<bool(string)> no_contiene;

public:
    HashTable() {
        hash = vector<list<T>>(1000);
        array = new T[1001];
        igual = [](string condicion) {if (condicion.compare("igual a") == 0) {
            return true;
        }};
        inicia = [](string condicion) {if (condicion.compare("inicia con") == 0) {
            return true;
        }};
        finaliza = [](string condicion) {if (condicion.compare("finaliza con") == 0) {
            return true;
        }};
        contiene = [](string condicion) {if (condicion.compare("contiene") == 0) {
            return true;
        }};
        no_contiene = [](string condicion) {if (condicion.compare("no contiene") == 0) {
            return true;
        }};
    }
    void busqueda(string key) {
        for (const T& value : hash[_hashFunction(key)]) {
            cout << value << "\n";
        }
    }
    void insert(string key, T value) {
        hash[_hashFunction(key)].push_back(value);
    }
    int _hashFunction(string key) {
        int temp = stoi(key);
        int data;
        if (temp >= 100) {
            data = 100;
        }
        else if (temp >= 1000) {
            data = 1000;
        }
        else
            data = 10;
        while (temp > data) {
            temp /= 10;
        }
        return temp;
    }
    void _sortM(int start, int index, int end, T* a) {
        int size = end - start + 1;
        T* newArray = new T[size];
        int l = start;
        int r = index + 1;
        int k = 0;
        while (l <= index && r <= end) {
            if (stoi(a[l]) < stoi(a[r]))
                newArray[k++] = a[l++];
            else
                newArray[k++] = a[r++];
        }
        while (l <= index) {
            newArray[k++] = a[l++];
        }
        while (r <= end) {
            newArray[k++] = a[r++];
        }
        for (int i = 0; i < size; ++i) {
            a[i + start] = newArray[i];
        }
        delete[] newArray;
    }
    void _mergesort(int start, int end, string* a) {
        if (end <= start) { return; }
        int index = (start + end) / 2;
        _mergesort(start, index, a);
        _mergesort(index + 1, end, a);
        _sortM(start, index, end, a);
    }
    void print() {
        for (const auto List : hash) {
            for (const T& value : List) {
                cout << value << "\n";
            }
        }
    }
    void leer_existente(string direc) {
        int contador = 0;
        DIR* dir;
        struct dirent* ent;
        string temp;
        T* arreglo_temporal = new T[1003];
        string tmp = direc + "/A.Trabajo";
        char* path = new char[tmp.size() + 1];
        strcpy(path, tmp.c_str());
        if ((dir = opendir(path)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (contador >= 2) {
                    arreglo_temporal[contador] = string(ent->d_name);
                }
                ++contador;
            }
            closedir(dir);
        }
        _mergesort(2, contador - 1, arreglo_temporal);
        for (int i = 2; i < contador; ++i) {
            temp = to_string(i - 2);
            array[i - 2] = arreglo_temporal[i];
            insert(temp, arreglo_temporal[i]);
        }
    }
    void crear(string direc, int i, T v) {
        string _dat = to_string(i);
        string dat = direc + "/A.Trabajo/" + to_string(i);
        wstring stemp = wstring(dat.begin(), dat.end());
        LPCWSTR data = stemp.c_str();
        CreateDirectory(data, NULL);
        string file = direc + "/A.Trabajo/" + _dat + "/" + to_string(i) + ".txt";
        ofstream datos;
        datos.open(file.c_str());
        datos << to_string(i) << "\n";
        datos << to_string(i) << "\n";
        datos << to_string(i) << "\n";
        datos.close();
        string name = to_string(i);
        insert(name, v);
    }
    void show(string key, string direc) {
        string data, temp, linea;
        for (const T& value : hash[_hashFunction(key)]) {
            if (key.compare((string)value) == 0) {
                ifstream file;
                temp = value;
                data = direc + "/A.Trabajo/" + temp + ".txt";
                file.open(data.c_str());
                cout << value << ".txt \n";
                while (file >> linea) {
                    cout << linea << "\n";
                }
                cout << "\n";
            }
        }
        getch();
    }
    void search_by(string key, string condicion) {
        int cont = 0;
        for (const auto& List : hash) {
            for (const T& value : List) {
                string temp(value);
                if (igual(condicion)) {
                    if (temp.compare(key) == 0) {
                        cout << "Archivo encontrado! \n" << temp << "\n";
                        break;
                    }
                }
                else if (inicia(condicion)) {
                    if (cont == 0)
                        cout << "Archivo encontrado! \n";
                    ++cont;
                    if (strncmp(temp.c_str(), key.c_str(), key.size()) == 0) {
                        cout << value << "\n";
                    }
                }
                else if (finaliza(condicion)) {
                    if (temp.size() >= key.size()) {
                        //temp.erase(temp.size() - 4, 4);
                        string tempo(key);
                        //tempo.erase(tempo.size() - 4, 4);
                        if (temp.compare(temp.length() - tempo.length(), tempo.length(), tempo) == 0) {
                            if (cont == 0)
                                cout << "Archivo encontrado! \n";
                            cout << value << "\n";
                            ++cont;
                        }
                    }
                }
                else if (contiene(condicion)) {
                    if (temp.find(key) != string::npos) {
                        if (cont == 0)
                            cout << "Archivo encontrado! \n";
                        cout << value << "\n";
                        ++cont;
                    }
                }
                else if (no_contiene(condicion)) {
                    if (temp.find(key) == string::npos) {
                        if (cont == 0)
                            cout << "Archivo encontrado! \n";
                        cout << value << "\n";
                        ++cont;
                    }
                }
            }
        }
    }
};