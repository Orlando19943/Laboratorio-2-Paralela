/*
* Computación Paralela y Distribuida
* Laboratorio 2 - Paralelización de QuickSort
* Autores:
*   - Orlando Cabrera #19943
*   - Diana Zaray Corado # 191025
*/

#include <unistd.h>     //std lib
#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string
#include <vector>

#define OUTFILE "numeros_desordenados.csv"
#define INFILE "numeros_ordenados.csv"

using namespace std;

void writeFile(int *numbers, int N){
    ofstream escribirNumeros(OUTFILE,ios::out);
    if( escribirNumeros.bad() ) {
        cerr<<"Falló la creación del archivo "<<OUTFILE<<endl;
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<N;i++){
        escribirNumeros<<numbers[i]<<",";
    }
    escribirNumeros.close();
}

void readFile(int *numbers, int N){
    ifstream leerNumeros(OUTFILE,ios::in);
    if( leerNumeros.bad() ) {
        cerr<<"Falló la lectura del archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }
    string ch;
    while(getline(leerNumeros,ch,',')) {
        int i;
        int numero = stoi(ch);
        numbers[i] = numero;
        i++;
    }

    leerNumeros.close();
    
}

int main(int argc, char * argv[]) {

    //Valores iniciales default
    int j;
    int N = 50;
    srand(79);

    if(argc > 1) {
        N = strtol(argv[1], NULL, 10);
    }

    int * x = new int[N];
    int * y = new int[N];
    for (j=0; j<N; j++){
        x[j] = rand()%(N)+1;
    }
    // ESCRIBIR EN ARCHIVO
    writeFile(x, N);
    delete x;
    // LEER ARCHIVO
    readFile(y, N);

    for (j=0; j<N; j++){
        cout<<y[j]<<endl;
    }

    delete y;

    return 0;
}
