#pragma once
using namespace std;
template <typename T>

class Node {
public:
    T value;
    Node<T>* next;
    Node(T v, Node* n = nullptr) { value = v; next = n; }
};
template <class T>
class ListD {
private:
    Node<T>* inicio;
    Node<T>* fin;
    unsigned long size;
public:
    ListD() {
        inicio = fin = nullptr;
        size = 0;
    }
    void push_front(T v) {

        Node<T>* nuevo = new Node<T>(v);

        if (size == 0) {
            fin = nuevo;
        }
        else {
            nuevo->next = inicio;
            inicio->back = nuevo;
        }

        inicio = nuevo;
        ++size;
    }
    void print() {

        Node<T>* aux = inicio;
        while (aux != nullptr) {
            switch (aux->value)
            {
            case 1:
                cout << "config - "; break;
            case 2:
                cout << "init - "; break;
            case 3:
                cout << "clone - "; break;
            case 4:
                cout << "status - "; break;
            case 5:
                cout << "add - "; break;
            case 6:
                cout << "reset - "; break;
            case 7://commit-m
                cout << "commit - "; break;
            case 8:
                cout << "diff - "; getch(); break;
            case 9:
                cout << "log - "; break;
            case 10://hash
                cout << "hash - "; break;
            case 11:
                cout << "show - "; break;
            case 12:
                cout << "rm - "; break;
            case 13:
                cout << "mv - "; break;
            case 14://stash
                cout << "stash - "; break;
            case 15://stashlist
                cout << "stashlist - "; break;
            case 16:
                cout << "stashpop - "; break;
            case 17:
                cout << "stashdrop - ";; break;
            case 18://busqueda
                cout << "busqueda - "; break;
            case 19://POP
                cout << "POP - "; break;
            case 20:
                cout << "checkout - "; break;
            case 21:
                cout << "Creacion de archivos - ";
                break;
            case 22:
                cout << "print - "; break;
            default:
                break;
            }
            cout << "end";
            aux = aux->next;
        }
        getch();
    }
    void push_back(T v) {
        Node<T>* nuevo = new Node<T>(v);
        if (size == 0) {
            inicio = nuevo;
        }
        else {
            fin->next = nuevo;
        }
        fin = nuevo;
        ++size;

    }
};