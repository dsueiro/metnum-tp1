//
// Created by mgrynberg on 18/09/18.
//

#include "matrizes.h"

int ELEMENTOS = 2;
float PROBABILIDAD = 0.76;

void imprimirVector(vectorReal v){
    for (int i = 0; i < v.size(); ++i) {
    }
}

void imprimirMatriz (Matriz A) {
    cout << endl;
    for (int i = 1; i <= (ELEMENTOS); ++i) {
        for (int j = 1; j <= (ELEMENTOS); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

//matriz de unos columna
Matriz unos(int N){
    Matriz un;
    for (int i = 1; i <= N; ++i) {
        un[i][1]= 1;
    }
    return un;
}

//matriz de ceros columna
Matriz ceros(int N){
    Matriz os;
    for (int i = 1; i <= N; ++i) {
        os[i][1]=0;
    }
    return os;
}

vectorReal suma(vectorReal A , vectorReal B){
    vectorReal C;
    for (int i = 0; i < A.size(); ++i) {
        C.push_back(A[i]+B[i]);
    }
    return C;
}

vectorReal multiplicar(vectorReal a, float b){
    for (int i = 0; i <a.size(); ++i) {
        a[i] = a[i]*b;
    }
    return a;
}


map<int,float> aMap(vectorReal a){
    map<int,float> c;
    for (int i = 0; i < a.size(); ++i) {
        if(a[i]!=0) {
            c[i+1] = a[i];
        }
    }
    return c;
}

Matriz identidad (int N){
    Matriz A;
    for (int i = 1; i <= N; ++i) {
        A[i][i] = 1;
    }
    return A;
}

Matriz traspuesta(Matriz A){
    Matriz  At;
    for (pair<int , map<int ,float>> fila : A) {
        int i = fila.first;
        for (pair<int ,float> valor : A[fila.first]) {
            int j = valor.first;
            At[j][i] = A[i][j];
        }
    }
    return At;
}

Matriz darColumna (Matriz A , int columna_i){
    A = traspuesta(A);
    return traspuesta(darFila(A,columna_i));
}

Matriz darFila(Matriz A , int fila_i){
    Matriz v;
    for (pair<int ,float> columna : A[fila_i]) {
        int j = columna.first;
        v[1][j] = columna.second;
    }
    return v;
}



Matriz suma(Matriz A , Matriz B) {
    for (pair<int , map<int ,float>> fila : B) {
        int i = fila.first;
        for (pair<int ,float> valor : B[fila.first]) {
            int j = valor.first;
            A[i][j] = A[i][j] + valor.second;
        }
    }
    return A;
}


Matriz multiplicar(Matriz A, float c){
    for (pair<int , map<int ,float>> fila : A) {
        int i = fila.first;
        for (pair<int ,float> valor : A[fila.first]) {
            int j = valor.first;
            A[i][j] = valor.second*c;
        }
    }
    return A;
}


//multiplicacion de matrizes cuadradas de N = ELEMENTOS
Matriz multiplicar(Matriz A , Matriz B){
    B = traspuesta(B);
    Matriz C;
    for (pair<int , map<int ,float>> columna : B) {
        int j = columna.first;

        for (pair<int , map<int ,float>> fila : A) {
            int i = fila.first;

            float cij = 0;
            float c = 0.0;

            for (pair<int ,float> valor : fila.second) {
                float  y = valor.second*columna.second[valor.first]-c;
                float t = cij + y;
                c = (t - cij) - y;
                cij = t;
            }

            if(cij!=0) {C[i][j] = cij;}
        }
    }
    return C;
}

void triangular(Matriz &A , Matriz &b) {
    for (pair<int , map<int ,float>> pivote : A) {

        int i = pivote.first;
        cout << "Triangulando: PivoteActual  " << i << endl;

        float aii = pivote.second[i];
        if (aii == 0) { continue; }

        for (pair<int , map<int ,float>>  fila : A) {
            //j es la fila a la que se le va a restar el pivote
            int j = fila.first;

            if (j <= i) { continue; }
            if (A[j][i]==0) { continue; }


            float aij = A[j][i];
            float c = -aij / aii;


            Matriz nueva_filaA = darFila(A, i);
            Matriz nueva_filab = darFila(b, i);

            nueva_filaA = multiplicar(nueva_filaA, c);
            nueva_filaA = suma(nueva_filaA, darFila(A, j));

            nueva_filab = multiplicar(nueva_filab, c);
            nueva_filab = suma(nueva_filab, darFila(b, j));

            A[j] = nueva_filaA[1];
            b[j] = nueva_filab[1];

        }

    }


}

//resuelve A*x = b con A traingular superior y b matriz columna
Matriz resolverTriangulado(Matriz A, Matriz b) {
    Matriz x;
    x[ELEMENTOS][1] = 1;

    for (int i = ELEMENTOS; i > 0; --i) {
        cout << "Resolviendo al reves: X Actual " << i << endl;

        float aii = A[i][i];
        float xi = 0;
        float c = 0.0;

        for (int j = i+1; j <= ELEMENTOS; ++j) {
            float   y = -A[i][j]*x[j][1]-c;
            float t = xi + y;
            c = (t-xi) - y;
            xi = t;
        }
        xi += b[i][1];
        xi = xi/aii;

        x[i][1] = xi;

    }


    return x;
}