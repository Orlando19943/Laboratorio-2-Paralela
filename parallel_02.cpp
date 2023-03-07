/*
* Computación Paralela y Distribuida
* Laboratorio 2 - Paralelización de QuickSort
* Autores:
*   - Orlando Cabrera #19943
*   - Diana Zaray Corado #191025
*/

#include <unistd.h>     
#include <iostream>
#include <cmath>
#include <fstream>      
#include <string>       
#include <vector>
#include <omp.h>

#define OUTFILE "unordered.csv"
#define INFILE "ordered.csv"
#define THREADS 10

using namespace std;

void generateRandom(int N, const string& filename){
    ofstream file(filename, ios::out);

    if(file.bad()) {
        cerr<<"Fail to create the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<N; i++){
        file<<1 + (rand() % N)<<",";
    }

    file.close();
}

void write(int* numbers, int N, const string& filename){
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

void read(int *numbers, const string& filename){
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
#pragma omp parallel sections
    {
        #pragma omp section 
            qsort(data, lo, h);
        #pragma omp section
            qsort(data, l, hi); 
    }
}

int main(int argc, char * argv[]) {

//  initial default values
    int N=1'000'000;
    int *y = new int[N];
    double start, end;

//  random variables
    srand(80);

    if(argc > 1) {
        N = strtol(argv[1], nullptr, 10);
    }

//  write into the file
    generateRandom(N, OUTFILE);
//  read the numbers from the file
    read(y, OUTFILE);

//  order the numbers
    start = omp_get_wtime();

    qsort(y, 0, N-1);

    end = omp_get_wtime();

    ofstream file("time.txt", ios::app);
    file << end - start << endl;
    file.close();

//  write the ordered numbers
    write(y, N, INFILE);
    delete[] y;

    return 0;
}

