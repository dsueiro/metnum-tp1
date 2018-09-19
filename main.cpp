#include <fstream>
#include "matrizes.h"


//metodo iterativo para aprximar x en Ax = b partiendo de una aproximacion inicial
vector<float> GaussSeidel (Matriz A , vector<float> b, vector<float> aproximacion, int PASOS,float tolerancia){
    vector<float> nuevaAproximacion = ceros(ELEMENTOS);
    int N=0;


    while (N<PASOS){
        cout << N << endl;
        vector<float> copia = nuevaAproximacion;

        for (int i = 1; i <= ELEMENTOS; ++i) {
            float aii = A[i][i];
            float nuevo_valor = 0;
            //aproximacion utilizando x(N)
            for (int j = 1; j < i; ++j) {
                nuevo_valor +=A[i][j]*nuevaAproximacion[j-1];
            }
            //aproximacion utilizando x(N-1)
            for (int j = ELEMENTOS; j > i; --j) {
                nuevo_valor +=A[i][j]*aproximacion[j-1];
            }
            nuevo_valor-=b[i];
            nuevo_valor = nuevo_valor*aii;
            nuevaAproximacion[i-1]=nuevo_valor;
        }

        aproximacion = copia;
        N++;

    }
    return nuevaAproximacion;
}

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
        float i; float j;
        ifs >> i; ifs >> j;
        W[i][j] = 1;
        D[i][i] += 1;
     }
    ifs.close();

    for (pair<int , map<int ,float>> fila : W) {
        // Accessing KEY from element
        int i = fila.first;
        // Accessing VALUE from element.
        for (pair<int ,float> valor : W[fila.first]) {
            // Accessing KEY from element
            int j = valor.first;

            cout << i << " " << j << endl;

            W[i][j] = W[i][j]/D[i][i];
            // Accessing VALUE from element.

        }

    }

    return W;
}

void guardarResultado(vector<float> resultado, string archivo){
    ofstream ouf;
    ouf.open(archivo);
    ouf << PROBABILIDAD << endl;
    for (int i = 0; i < resultado.size(); ++i) {
        ouf << resultado[i] << endl;
    }

}



vector<float> resolverSistema (Matriz W){

    W = multiplicar(W,-PROBABILIDAD);
    W = suma(W, identidad(ELEMENTOS));

    vector<float> resultado = GaussSeidel(W,unos(ELEMENTOS),ceros(ELEMENTOS),10,0.000001);
    float total = productoEscalar(unos(ELEMENTOS),resultado);
    resultado = multiplicar(resultado,1.0/total);

    return resultado;

}

int main() {

    Matriz W = leerMatriz("test_completo.txt");
    imprimirVector(aVector(W[1]));
    cout << ELEMENTOS << " " << PROBABILIDAD << endl;

    vector<float> v = resolverSistema(W);
    guardarResultado(v,"respuesta2.txt");


    return 0;
}
