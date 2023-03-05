//
// Created by Zaray Corado on 3/4/2023.
//

/*
* Computación Paralela y Distribuida
* Laboratorio 2 - Paralelización de QuickSort
* Autores:
*   - Orlando Cabrera #19943
*   - Diana Zaray Corado #191025
*/

#include <unistd.h>     //std lib
#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string
#include <vector>
#include <omp.h>

#define OUTFILE "numeros_desordenados.csv"
#define INFILE "numeros_ordenados.csv"

using namespace std;

void writeFile(int *numbers, int N, const string& filename){
    ofstream file(filename, ios::out);

    if(file.bad()) {
        cerr<<"Fail to create the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<N; i++){
        file<<numbers[i]<<",";
    }

    file.close();
}

void readFile(int *numbers, const string& filename){
    ifstream read(filename, ios::in);

    if(read.bad()) {
        cerr<<"Fail to open the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    string ch;
    int number;
    int i = 0;
    while(getline(read,ch,',')) {
        number = stoi(ch);
        numbers[i] = number;
        i++;
    }

    read.close();
}

void qsort(int *data, int lo, int hi){
    if(lo > hi) return;
    int l = lo;
    int h = hi;
//  the pivot is the half of the array
    int p = data[(hi + lo)/2];

    while(l <= h){
        while(data[l] < p) l++;
        while(data[h] > p) h--;
        if(l <= h){
//          swap
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++; h--;
        }
    }
//  recursive call
#pragma omp parallel sections num_threads(4)
{
    #pragma omp section
        qsort(data, lo, h);
    #pragma omp section
        qsort(data, l, hi);
    }

}

int main(int argc, char * argv[]) {

//  initial default values
    int j, N=50;
    int *x = new int[N];
    int *y = new int[N];
//  random variables
    srand(80);

    if(argc > 1) {
        N = strtol(argv[1], nullptr, 10);
    }

    for (j=0; j<N; j++){
//      generate random numbers from 1 to N
        x[j] = 1 + (rand() % N);
    }

//  write into the file
    writeFile(x, N, OUTFILE);
//  memory free
    delete[] x;

//  read the numbers from the file
    readFile(y, OUTFILE);

//  order the numbers
    qsort(y, 0, N-1);
//  write the ordered numbers
    writeFile(y, N, INFILE);
    delete[] y;

    return 0;
}

