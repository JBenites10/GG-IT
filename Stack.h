#pragma once
#pragma warning(disable:4996)
#include<stack>
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Stack_T {
    stack<T> sta;
public:
    Stack_T() {}
    void stash(T v) {
        sta.push(v);
    }
    void _pop() {
        sta.pop();
    }
    void list() {
        stack<T> aux;
        int size_T = sta.size();
        for (int i = 0; i < size_T; ++i) {
            cout << sta.top() << "\n";
            aux.push(sta.top());
            sta.pop();
        }
        for (int i = 0; i < size_T; ++i) {
            sta.push(aux.top());
            aux.pop();
        }
    }
    void stash_pop(string direc) {
        string s(sta.top());
        string aux = direc + "/A.Trabajo/" + s;
        ifstream datos(aux.c_str());
        string linea;
        while (datos >> linea) {
            cout << linea << "\n";
        }
        datos.close();
    }
    void stash_drop() {
        if (!sta.empty()) {
            int n = sta.size();
            for (int i = 0; i < n; ++i) {
                sta.pop();
            }
        }
    }
};