//============================================================================
// Name        : Prim's MST.cpp
// Author      : Rafat Hasan
// Version     :
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

struct Vertex {
  int vert;
  int key;
};

struct Vector {
  int * ary;
  int size;
  Vector(int val) {
    ary = new int[val];
  }
};

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
  int * parent = new int[s];
  int * key = new int[s];
  bool * mstSet = new bool[s];

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

int max(int ** matrix, int s) {
  int mx = matrix[0][0];
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (matrix[i][j] > mx) mx = matrix[i][j];
    }
  }
  return mx;
}

void populate(int ** X, int s, int low, int high) {
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < s; ++j)
        {
            x[i][j] = rand() % (high - low + 1) + low;
        }
    }
}

void allocate(int ** & X, int sz) {
  X = new int * [sz];
  for (int i = 0; i < sz; i++)
    X[i] = new int[sz];
}

int num_dig(int n) {
  if (n < 10) return 1;
  return 1 + num_dig(n / 10);
}

void display(int ** X, int s, int mx) {
  cout << endl;
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      cout << setw(num_dig(mx) + 2) <<X[i][j];
    }
    cout << endl;
  }

}