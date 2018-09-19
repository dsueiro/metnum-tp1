int ELEMENTOS = 2;
float PROBABILIDAD = 0.8;

void imprimirVector(vector<float> v){
    for (int i = 0; i < v.size(); ++i) {
    }
}

vector<float> unos(int N){
    vector<float> un;
    for (int i = 0; i < N; ++i) {
        un.push_back(1);
    }
    return un;
}


vector<float> ceros(int N){
    vector<float> os;
    for (int i = 0; i < N; ++i) {
        os.push_back(0);
    }
    return os;
}

vector<float> suma(vector<float> A , vector<float> B){
    vector<float> C;
    for (int i = 0; i < A.size(); ++i) {
        C.push_back(A[i]+B[i]);
    }
    return C;
}

vector<float> multiplicar(vector<float> a, float b){
    for (int i = 0; i <a.size(); ++i) {
        a[i] = a[i]*b;
    }
    return a;
}

float productoEscalar (vector<float> a , vector<float> b){
    float c = 0;
    for (int i = 0; i < a.size(); ++i) {
        c+= a[i]*b[i];
    }
    return c;
}

vector<float> aVector(map<int,float> a){
    vector<float> c = ceros(ELEMENTOS);
    for (pair<int ,float> fila : a) {
        int i = fila.first;
        c[i] = fila.second;
    }
    return c;
}

map<int,float> aMap(vector<float> a){
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

vector<float> darColumna (Matriz A , int columna_i){
    A = traspuesta(A);
    return darFila(A,columna_i);
}

vector<float> darFila(Matriz A , int fila_i){
    vector<float> v = aVector(A[fila_i]);
    return v;
}





Matriz suma(Matriz A , Matriz B) {
    for (pair<int , map<int ,float>> fila : B) {
        int i = fila.first;
        for (pair<int ,float> valor : B[fila.first]) {
            int j = valor.first;
            A[i][j] += valor.second;
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



//triangulacion matriz sin alterar orden, supone aii!=0
Matriz triangular(Matriz A){
    for (int i = 1; i <= ELEMENTOS; ++i) {
        float aii = A[i][i];
        vector<float> pivote = aVector(A[i]);
        for (int j = i+1; j <= ELEMENTOS; ++j) {
            vector<float> filaActual = aVector(A[j]);
            float c = -filaActual[i]/aii;
            vector<float> resultante = multiplicar(pivote,c);
            resultante = suma(resultante,filaActual);
            A[j] = aMap(resultante);
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
        vector<float> v1 = aVector(columna.second);

        for (pair<int , map<int ,float>> fila : A) {
            int i = fila.first;
            vector<float> v2 = aVector(fila.second);

            float valor = productoEscalar(v1,v2);
            if(valor!=0) {C[i][j] = valor;}
        }
    }
    return C;
}
