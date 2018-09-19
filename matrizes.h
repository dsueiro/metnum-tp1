//
// Created by mgrynberg on 18/09/18.
//

#ifndef PAGERANK_MATRIZES_H
#define PAGERANK_MATRIZES_H


#include <iostream>
#include <vector>
#include <map>

using namespace std;
using Matriz = map<int,map<int,float>>;
using vectorReal = vector<float>;

extern int ELEMENTOS;
extern float PROBABILIDAD;

vectorReal aVector(map<int,float> a);
map<int,float> aMap(vectorReal a);

void imprimirVector(vectorReal v);

Matriz unos(int N);
Matriz ceros(int N);

vectorReal suma(vectorReal A , vectorReal B);
vectorReal multiplicar(vectorReal a, float b);

Matriz identidad (int N);
Matriz traspuesta (Matriz A);
Matriz darColumna (Matriz A , int columna_i);
Matriz darFila(Matriz A , int fila_i);

Matriz suma(Matriz A , Matriz B);
Matriz multiplicar(Matriz A, float c);
Matriz multiplicar(Matriz A, Matriz B);

void triangular(Matriz &A, Matriz &b);
Matriz resolverTriangulado(Matriz A, Matriz b);
void imprimirMatriz (Matriz A);



#endif //PAGERANK_MATRIZES_H
