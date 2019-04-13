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
void populate(int ** X, int s, int low, int high, int parcentage);
void display(int ** X, int s, int mx);
int max(int ** X, int s);
int num_dig(int n);
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
  cout << "percentage of Edges(50-100): ";
  cin >> p;
  cout << "Lowest weight :";
  cin >> low;
  cout << "Highest weight :";
  cin >> high;
  allocate(matrix, n);
  populate(matrix, n, low, high, p);
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

void populate(int ** X, int s, int low, int high, int parcentage) {

  int count = 0;
  double edges = parcentage / 100.0;
  int max_edges = (s * (s - 1)) / 2;
  double estimated_edges = (parcentage * max_edges) / 100.00;

  if ((estimated_edges - (int) estimated_edges) >= 0.50) estimated_edges = (int) estimated_edges + 1;

  cout << "Please Wait..........";
  while (true) {
    srand(time(0));
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (j < i) {
          X[i][j] = X[j][i];
        } else if (j > i) {
          double val = (double) rand() / RAND_MAX;
          if (val <= edges) {
            X[i][j] = rand() % (high - low + 1) + low;
            count++;
          } else {
            X[i][j] = -1;
          }
        } else {
          X[i][j] = 0;
        }

      }
    }
    if (count == (int) estimated_edges)
      break;
    count = 0;
  }
}

int max(int ** X, int s) {
  int mx = X[0][0];
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (X[i][j] > mx) mx = X[i][j];
    }
  }
  return mx;
}

int num_dig(int n) {
  if (n < 10) return 1;
  return 1 + num_dig(n / 10);
}

void allocate(int ** & X, int sz) {
  X = new int * [sz];
  for (int i = 0; i < sz; i++)
    X[i] = new int[sz];
}

void display(int ** X, int s, int mx) {
  cout << endl;
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      cout << setw(num_dig(mx) + 2) << X[i][j];
    }
    cout << endl;
  }

}