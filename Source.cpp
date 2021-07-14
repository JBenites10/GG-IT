#include <iostream>
#pragma warning(disable:4996)
#include <string>
#include<filesystem>
#include <fstream>
#include "Dirent.h"
#include <process.h>
#include <windows.h>;
#include <conio.h>
#include"Stack.h"
#include"HashTable.h"
#include<stdio.h>
#include<Windows.h>
#include"List.h"
using namespace std;

int status_size(string direc) {
    DIR* dir;
    int size = 0;
    struct dirent* ent;
    string temp = direc + "/A.Preparacion/Temporal";
    char* path = new char[temp.size()];
    strcpy(path, temp.c_str());
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            ++size;
        }
    }
    closedir(dir);
    return size;
}
string config() {
    string user, mail, password;
    string cmd = "mkdir ";
    cout << "Ingrese el nombre de usuario: ";
    cin >> user;
    cmd += "user";
    system(cmd.c_str());
    ofstream datos("user/cuenta.txt");
    cout << "Ingrese su direccion de mail: ";
    cin >> mail;
    datos << mail << "\n";
    cout << "Ingrese su contraseña: ";
    cin >> password;
    datos << password;
    datos.close();
    rename("user", user.c_str());
    return user;
}
void init(string direc) {
    string repos0 = "Repositorio", repos1 = "A.Preparacion", repos2 = "A.Trabajo", repos3 = "A.Preparacion/Temporal";
    string dat = direc + "/" + repos0;
    wstring stemp = wstring(dat.begin(), dat.end());
    LPCWSTR data = stemp.c_str();
    CreateDirectory(data, NULL);
    dat = direc + "/" + repos1;
    stemp = wstring(dat.begin(), dat.end());
    data = stemp.c_str();
    CreateDirectory(data, NULL);
    dat = direc + "/" + repos3;
    stemp = wstring(dat.begin(), dat.end());
    data = stemp.c_str();
    CreateDirectory(data, NULL);
    dat = direc + "/" + repos2;
    stemp = wstring(dat.begin(), dat.end());
    data = stemp.c_str();
    CreateDirectory(data, NULL);
}
void clone(string direc) {
    string direction_1, nombre_nuevo_carpeta;
    cout << "Ingrese la direccion de la carpeta que desea clonar: ";
    cin >> direction_1;
    string temp = direc + "\\" + direction_1;
    cout << "Ingres el nombre de la carpeta clonada: ";
    cin >> nombre_nuevo_carpeta;
    string dat = direc + "\\" + nombre_nuevo_carpeta;
    wstring stemp = wstring(dat.begin(), dat.end());
    LPCWSTR data = stemp.c_str();
    CreateDirectory(data, NULL);
    string cmd = "copy " + temp + " " + dat;
    system(cmd.c_str());
}
void status(string direc) {
    DIR* dir;
    struct dirent* ent;
    int x = 0;
    string temp = direc + "/A.Preparacion/Temporal";
    char* path = new char[temp.size()];
    strcpy(path, temp.c_str());
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            ++x;
            if (x > 2) {
                cout << ent->d_name << "\n";
            }
        }
        closedir(dir);
    }
    getch();
}
char* status_(string direc, int i) {
    DIR* dir;
    struct dirent* ent;
    int x = 0;
    string temp = direc + "/A.Preparacion/Temporal";
    char* path = new char[temp.size() + 1];
    strcpy(path, temp.c_str());
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            ++x;
            if (x > i) {
                return ent->d_name;
                closedir(dir);
            }
        }
    }
}
void add(string direc) {
    string  cmd = direc + "/A.Trabajo/", file, cmd2 = direc + "/A.Preparacion/Temporal/", directory;
    cout << "Ingrese el nombre de la carpeta donde se encuentra su archivo: ";
    cin >> directory;
    cout << "Ingrese el nombre del archivo que desea añadir: ";
    cin >> file;
    cmd += directory + "/" + file;
    cmd2 += file;
    rename(cmd.c_str(), cmd2.c_str());
}
void reset(string direc) {
    string cmd = direc + "/Repositorio/", file, cmd2 = direc + "/A.Preparacion/";
    cout << "Ingrese el nombre del archivo que desea añadir: ";
    cin >> file;
    cmd += file;
    cmd2 += file;
    rename(cmd.c_str(), cmd2.c_str());
}

void commit(string direc) {
    string  cmd = direc + "/A.Preparacion/Temporal/", file, cmd2 = direc + "/Repositorio/";
    cout << "Ingrese el nombre del archivo que desea añadir: ";
    cin >> file;
    cmd += file;
    cmd2 += file;
    rename(cmd.c_str(), cmd2.c_str());
}
void Create_File(string direc) {
    string dir_name, file, file2;
    cout << "Ingrese el nombre de su carpeta contenedora: ";
    cin >> dir_name;
    cout << "Ingrese el nombre de su archivo: ";
    cin >> file;
    string dat = direc + "/A.Trabajo/" + dir_name;
    DWORD file_attributes = GetFileAttributesA(dat.c_str());
    if ((file_attributes == INVALID_FILE_ATTRIBUTES) == true) {
        wstring stemp = wstring(dat.begin(), dat.end());
        LPCWSTR data = stemp.c_str();
        CreateDirectory(data, NULL);
    }
    ofstream datos;
    string linea;
    cout << "Desea modificar alguna version? Y/N: ";
    char opt;
    cin >> opt;
    if (opt == 'Y' || opt == 'y') {
        cout << "Seleccione la version que desea modificar: ";
        cin >> file2;
        ifstream _file;
        datos.open((dat + "/" + file).c_str(), ios::out);
        _file.open((dat + "/" + file2).c_str(), ios::in);
        while (getline(_file, linea)) {
            datos << linea << "\n";
        }
        _file.close();
        datos.close();
    }
    getch();
    linea = "";
    datos.open((dat + "/" + file).c_str(), ios::app);
    while (1) {
        cout << "Ingrese una nueva linea: ";
        cin.ignore();
        getline(cin, linea);
        if (linea.compare("...") == 0) {
            break;
        }
        datos << linea << "\n";
    }
}
void diff(string user) {
    ifstream archAT, arch2;
    string st1, st2;
    //Area de Trabajo
    string tempAT;
    cout << "===AREA DE TRABAJO===" << endl;
    cout << "ingrese el nombre de su archivo: ";
    cin.ignore();
    getline(cin, tempAT);
    string direccion = user + "/a.Trabajo/" + tempAT;
    archAT.open(direccion);

    //Area de preparacion
    string tempAP;
    cout << "===AREA DE PREPARACION===" << endl;
    cout << "ingrese el nombre de su archivo: ";
    cin.ignore();
    getline(cin, tempAP);
    string direccion1 = user + "/a.Preparacion/Temporal/" + tempAP;
    arch2.open(direccion1);

    while (archAT >> st1)
    {
        arch2 >> st2;
        if (st1.compare(st2) != 0) {
            cout << "[!=]" << st1 << endl;
        }

    }
}
void log(string direc) {
    DIR* dir;
    struct dirent* ent;
    int x = 0;
    string temp = direc + "/A.Preparacion/Temporal";
    char* path = new char[temp.size()];
    strcpy(path, temp.c_str());
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            ++x;
            if (x > 2) {
                cout << ent->d_name << "\n";
            }
        }
        closedir(dir);
    }
    getch();
}

void rm(string directory) {
    string file, type;
    cout << "Ingrese el nombre del archivo que desea eliminar: ";
    cin >> file;
    cout << "Ingrese el tipo de archivo: ";
    cin >> type;
    string cmd = directory + "/Repositorio/" + file + "." + type;
    remove(cmd.c_str());
}
void mv(string direc) {
    string file;
    string  directory1, directory2, cmd = direc + "/", cmd2 = direc + "/";
    cout << "Ingrese la ruta de donde desea mover: ";
    cin >> directory1;
    cout << "Ingrese el nombre del archivo: ";
    cin >> file;
    cout << "Ingrese la ruta a donde desea moverlo: ";
    cin >> directory2;
    cmd += directory1 + "/" + file;
    cmd2 += directory2 + "/" + file;
    rename(cmd.c_str(), cmd2.c_str());
}
void check_out(string direc) {
    string directory = direc + "/A.Preparacion/", file, directory2 = direc + "/A.Trabajo/", directory1;
    cout << "Ingrese la carpeta contenedora a donde quiere mover su archivo: ";
    cin >> directory1;
    cout << "Ingrese el nombre del archivo que desea mover: ";
    cin >> file;
    directory += file;
    directory2 += directory1 + "/" + file;
    rename(directory.c_str(), directory2.c_str());
}

// MOVER LOS ARCHIVOS DE LAS ZONAS TEMPORALES
void MV_A_PREPARACION(string direc) {
    string directory2, cmd = direc + "/A.Preparacion/Temporal/", cmd2 = direc + "/A.Preparacion/";
    DIR* dir;
    struct dirent* ent;
    int x = 0;
    string temp = direc + "/A.Trabajo";
    char* path = new char[temp.size()];
    strcpy(path, temp.c_str());
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            ++x;
            if (x > 2) {
                cmd += ent->d_name + ent->d_type;
                cmd2 += ent->d_name + ent->d_type;
                rename(cmd.c_str(), cmd2.c_str());
            }
        }
        closedir(dir);
    }
}
void hash_(ListD<int> obj_hash) {
    obj_hash.print();
}
int menu() {
    string tecla;
    string line;
    ifstream myfile("logo.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            cout << line << endl;
        }
        myfile.close();
    }
    cout << "Accion: ";
    cin >> tecla;
    return stoi(tecla);
}

int main() {
    setlocale(LC_ALL, "esp");
    char tmp;
    int i, case_;
    string directory, temp, condicion;
    string temporal = directory + "/A.Trabajo";
    DWORD file = GetFileAttributesA(temporal.c_str());
    Stack_T<char*> obje;
    HashTable<string> objeto;
    ListD<int> obj_hash;
    while (true)

    {
        int tam = status_size(directory);
        case_ = menu();
        obj_hash.push_back(case_);
        switch (case_)
        {
        case 1:
            cout << "¿Tiene un usario creado? Y|N: ";
            cin >> tmp;
            if (tmp == 'Y' || tmp == 'y') {
                cout << "Ingrese el nombre de su usuario: ";
                cin >> directory;
                break;
            }
            else {
                directory = config(); break;
            }
        case 2:
            init(directory); break;
        case 3:
            clone(directory); break;
        case 4:
            status(directory); break;
        case 5:
            add(directory); break;
        case 6:
            reset(directory); break;
        case 7:
            commit(directory); break;
        case 8:
            diff(directory); getch(); break;
        case 9:
            log(directory); break;
        case 10:
            hash_(obj_hash); break;
        case 11:
            cout << "Ingrese el nombre del archivo: ";
            cin >> temp;
            objeto.show(temp, directory);
            break;
        case 12:
            rm(directory); break;
        case 13:
            mv(directory); break;
        case 14:
            for (int i = 2; i < tam; ++i) {
                obje.stash(status_(directory, i));
            }
            break;
        case 15:
            obje.list();
            getch(); break;
        case 16:
            obje.stash_pop(directory);
            getch();
            break;
        case 17:
            obje.stash_drop(); break;
        case 18:
            cout << "===CONDICIONES===\n-igual a \n-inicia con\n-finaliza con\n-contiene\n-no contiene\n";
            cout << "Ingrese la condicion: ";
            cin.ignore();
            getline(cin, condicion);
            cout << "Ingrese el valor de busqueda: ";
            cin >> temp;
            objeto.search_by(temp, condicion);
            getch();
            break;
        case 19:
            obje._pop(); break;
        case 20:
            check_out(directory); break;
        case 21:
            Create_File(directory);
            break;
        case 22:
            if ((file == INVALID_FILE_ATTRIBUTES) == true) {
                init(directory);
                for (int i = 0; i < 1001; ++i) {
                    temp = to_string(i);
                    objeto.crear(directory, i, temp);
                }
            }
            else {
                objeto.leer_existente(directory);
            }
            break;
        case 23:
            objeto.print();
            getch();
            break;
        default:
            break;
        }
        system("cls");
    }
    system("pause");
    return 0;

}
