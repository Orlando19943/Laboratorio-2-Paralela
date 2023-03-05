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

#define OUTFILE "numeros_desordenados.csv"
#define INFILE "numeros_ordenados.csv"

using namespace std;

void writeFile(int *numbers, int N, string filename){
    ofstream writeNumber(filename, ios::out);
    if( writeNumber.bad() ) {
        cerr<<"Fail to create the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<N;i++){
        writeNumber<<numbers[i]<<",";
    }
    writeNumber.close();
}

void readFile(int *numbers, int N, string filename){
    ifstream readNumbers(filename, ios::in);
    if( readNumbers.bad() ) {
        cerr<<"Fail to open the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }
    string ch;
    int number;
    int i = 0;
    while(getline(readNumbers,ch,',')) {
        numero = stoi(ch);
        numbers[i] = numero;
        i++;
    }

    readNumbers.close();
    
}

void par_qsort(int *data, int lo, int hi) //}, int (*compare)(const int *, const int*))
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  //recursive call
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}

int main(int argc, char * argv[]) {

//  initial default values
    int j, N;
    srand(80);

    if(argc > 1) {
        N = strtol(argv[1], NULL, 10);
    }

    int *x = new int[N], *y = new int[N];

    for (j=0; j<N; j++){
        x[j] = rand()%(N)+1;
    }

//  write into the file
    writeFile(x, N, OUTFILE);
//  memory free
    delete[] x;

//  read the numbers from the file
    readFile(y, N, OUTFILE);

    for (j=0; j<N; j++){
        cout<<y[j]<<endl;
    }

//  order the numbers
    par_qsort(y, 0, N-1);
//  write the ordered numbers
    writeFile(y, N, INFILE);
    delete[] y;

    return 0;
}
