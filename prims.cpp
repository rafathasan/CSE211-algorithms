//============================================================================
// Name        : Prim's MST.cpp
// Author      : Rafat Hasan
// Github     : https://github.com/rafathasan/Algorithm-Project/blob/master/prims.cpp
// Copyright   : GPLv3
// Description : Prim's MST in C++, Ansi-style
//============================================================================

#include <iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;

void allocate(int ** & , int);
void populate(int ** X, int s, int low, int high);
void display(int ** X, int s, int mx);
int max(int ** matrix, int s);
void primsMST(int ** X, int s);
void insertVertex(int * mstSet, int s, int val);
bool isExist(int * mstSet, int s, int val);
int minKey(int * key, bool * mstSet, int s);
int printMST(int * parent, int s, int ** matrix);

int main() {
  int ** matrix;
  int n, p, low, high;
  cout << "Number of Vertex :";
  cin >> n;
  cout << "Lowest weight :";
  cin >> low;
  cout << "Highest weight :";
  cin >> high;
  allocate(matrix, n);
  populate(matrix, n, low, high);
  display(matrix, n, max(matrix, n));
  primsMST(matrix, n);
  return 0;
}

void primsMST(int ** X, int s) {
  int * parent = new int[s];            //stores terversing key by lowest cost
  int * key = new int[s];               //stores cost terversed by path
  bool * mstSet = new bool[s];          //store visited node boolean

  for (int i = 0; i < s; ++i) {
    key[i] = INT_MAX;
    mstSet[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int i = 0; i < s - 1; ++i) {
    int p = minKey(key, mstSet, s);
    mstSet[p] = true;

    for (int j = 0; j < s; ++j) {
      if (X[i][j] && mstSet[j] && X[i][j] < key[j])
        parent[j] = p;
      key[j] = X[i][j];
    }

  }
  printMST(parent, s, X);
}

int minKey(int * key, bool * mstSet, int s) {

  int min = INT_MAX, min_index;

  for (int i = 0; i < s; i++)
    if (mstSet[i] == false && key[i] < min)
      min = key[i], min_index = i;

  return min_index;
}

int printMST(int * parent, int s, int ** X) {
  cout << "Edge \tWeight" << endl;
  for (int i = 1; i < s; i++)
    cout << parent[i] << " - " << i << "\t" << X[i][parent[i]] << endl;
}


void populate(int ** X, int s, int low, int high) {   //populating 2d array with random value
    for (int i = 0; i < s; ++i){
        for (int j = 0; j < s; ++j){
            if(i==j)
              X[i][j] = 0;
            else
              X[i][j] = rand() % (high - low + 1) + low;

        }
    }
}

void allocate(int ** & X, int sz) {
  X = new int * [sz];
  for (int i = 0; i < sz; i++)                          //initializing 2d array with size
    X[i] = new int[sz];
}

int max(int ** matrix, int s) {
  int mx = matrix[0][0];                                //finding the maximum value from 2d array
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (matrix[i][j] > mx) mx = matrix[i][j];
    }
  }
  return mx;
}

int num_dig(int n) {
  if (n < 10) return 1;                                 //getting the digit count in a number
  return 1 + num_dig(n / 10);
}

void display(int ** X, int s, int mx) {
  cout << endl;
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      cout << setw(num_dig(mx) + 2) << X[i][j];         //displaying 2d array and allocating whitespace by using maximum digit length
    }
    cout << endl;
  }
}

// Number of Vertex :15
// Lowest weight :5
// Highest weight :40
//
//    0  10  40  39   9  22  33  35  23  39  25  22  34  30  20
//   30   0  28  12  31   8   5  32  29  19  14   9  39  38  37
//   31  28   0  16  23  16  23  38   9  40  24  12  35  16  20
//    7  26  38   0  25  26  12  34  33  28  37  15  38  26  12
//   16  26  30  27   0   9  16  19  11   5  15   9  19   9   9
//   19  14  19  38  39   0  19  35  38  26  25  14  28   5  15
//    5  37  39  37  40  33   0  29   8   7  24  34  15  31  35
//   38  22  14  16  36  35  29   0  35  14   7  34  35  22  22
//   37  33  11  38  34  26  26  29   0  15  11  22  29  40  40
//    8  27  40  33  31  39  26  21  39   0  15   8  28  12  38
//   18  16  38  20  10  22  30   7  34  17   0  19  39   7  39
//   38  13   5  16  11  40  27  28  17  22  25   0   8  24  14
//    7  19  36  25  19   9  29  14  29  20  17   9   0   6  23
//   22  24  35   7  29  13  24  40  25  30  29  24  28   0  14
//   23  34  30  15  22  25  40  32  13  34  36  25  15  32   0
//
// Edge    Weight
// 10 - 1  14
// 13 - 2  16
// 13 - 3  26
// 11 - 4  9
// 12 - 5  28
// 13 - 6  31
// 12 - 7  35
// 13 - 8  40
// 12 - 9  28
// 12 - 10 39
// 0 - 11  38
// 0 - 12  7
// 0 - 13  22
// 0 - 14  23
