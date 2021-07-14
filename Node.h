#pragma once
#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Node {
public:
    T value;
    Node<T>* next;
    Node(T v, Node* n = nullptr) { value = v; next = n; }
};