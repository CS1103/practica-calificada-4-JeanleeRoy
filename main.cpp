#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;

template <class T>
void maximoDeHilo(vector<T> &vector, int inf, int sup, T &max) {
    max = vector[inf];
    for (int i = inf; i < sup ; ++i)
        if (vector[i] > max)
            max = vector[i];
}


template <typename T>
T valorMaximo(vector<T> &max){
    T maximo = max[0];
    for (auto i : max)
        if (max[i] > maximo)
            maximo = max[i];
    return maximo;
}

int main() {

    vector<thread> hilos;               //vector de hilos
    int inf, sup;                       //limite de hilos
    vector<int> numbers;                //vector de numeros
    int cantidad = 40;                  //cantidad de numeros

    srand(time(NULL));

    for (int j = 0; j < cantidad; ++j) {
        numbers.push_back(rand() % 100 + 1);
    }

    int num_hilos = 8;
    vector<int> valores_maximos;            //vector de valores maximos
    for (int i = 0; i < num_hilos; i++) {
        inf = i * (cantidad / num_hilos);
        sup = (i + 1) * (cantidad / num_hilos);
        hilos.emplace_back(maximoDeHilo, ref(numbers), inf, sup, ref(valores_maximos[i]));
    }

    for (int i = 0; i < num_hilos; i++) {
        hilos[i].join();
    }

    int max = valorMaximo(valores_maximos);          //el maximoDeHilo de los valores maximos

    for (auto i : valores_maximos) {                 //Prueba
        assert(max >= i);
    }

    cout << max;

    return 0;
}