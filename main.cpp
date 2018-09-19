#include <fstream>
#include "matrizes.h"



//Devuelve W*D
Matriz leerMatriz(string direccion){
    Matriz W;
    Matriz D;

    ifstream ifs;
    ifs.open(direccion);
    ifs >> ELEMENTOS;

    float a;
    ifs >> a;

    while (!ifs.eof()){
        float de; float a;
        ifs >> de; ifs >> a;
        W[a][de] = 1;
        D[de][de] += 1;
     }
    ifs.close();


    for (pair<int , map<int ,float>> fila : W) {
        int i = fila.first;
        for (pair<int ,float> valor : W[fila.first]) {
            int j = valor.first;
            if (D[j][j]!=0) {W[i][j] = W[i][j]/D[j][j];}
        }

    }


    return W;
}

void guardarResultado(Matriz resultado, string archivo){
    ofstream ouf;
    ouf.open(archivo);
    ouf << PROBABILIDAD << endl;
    for (int i = 1; i <= ELEMENTOS; ++i) {
        ouf << resultado[i][1] << endl;
    }
}


Matriz resolverSistema (Matriz W){
    W = multiplicar(W, -PROBABILIDAD);
    W = suma(W,identidad(ELEMENTOS));

    Matriz b = unos(ELEMENTOS);
    Matriz c = traspuesta(b);
    W[ELEMENTOS+1] = c[1];
    b[ELEMENTOS+1][1] = 1;


    triangular(W,b);

    Matriz x = resolverTriangulado(W,b);
    float factor = multiplicar(traspuesta(unos(ELEMENTOS)),x)[1][1];
    cout << endl;
    cout << endl;
    x = multiplicar(x,1.0/factor);

    return x;

}

void medirError(string respuestaEstimada, string respuestaCorrecta){
    ifstream ifs1;
    ifs1.open(respuestaEstimada);
    ifstream ifs2;
    ifs2.open(respuestaCorrecta);
     while (!ifs2.eof()) {
         float tolerancia = 0.0001;
         double x1; double x2;
         ifs1 >> x1; ifs2 >> x2;
         float diferencia =  x1-x2;
         if(diferencia>tolerancia || diferencia<(-tolerancia)) {
             cout << x1 << endl;
             cout << "No es suficientemente bueno" << endl;
             break;
         }
     };
}

int main(float probabilidad) {
    cin >> PROBABILIDAD;

    string archivo = "tests/test_completo.txt";
    //archivo = "tests/test_15_segundos.txt";

    Matriz W = leerMatriz(archivo);
    Matriz  v = resolverSistema(W);
    imprimirMatriz(v);
    guardarResultado(v,"resultado.txt");



    return 0;
}