//============================================================================
// Name        : cycle.cpp
// Author      : Rafat Hasan
// Github      : github.com/rafathasan/Algorithm-Project/blob/master/huffman
// Copyright   : GPLv3
// Description : HuffmanAlgorithm(Array Based) in C++, Ansi-style
//============================================================================

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;
struct Vertex {
  int tag;
  bool flag;
  int parent;
};

void populate_vertices(Vertex * vertices, int n);
int checkCycle(int ** matrix, Vertex * vertices, int n);
void allocate(int ** & , int);
void populate(int ** X, int s, int low, int high, int parcentage);
int max(int ** matrix, int s);
void display(int ** X, int s, int mx);
int num_dig(int n);

int main() {
  int ** matrix;
  Vertex * vertices;
  int n, p, low, high;
  cout << "Number of Vertex :";
  cin >> n;
  cout << "Lowest weight :";
  cin >> low;
  cout << "Highest weight :";
  cin >> high;
  cout << "Connectness Percentage :";
  cin >> p;
  allocate(matrix, n);
  populate(matrix, n, low, high, p);
  display(matrix, n, max(matrix, n));
  populate_vertices(vertices, n);
  if (checkCycle(matrix, vertices, n)) {
    cout << "Has Cycle";
    return 0;
  }
  cout << "No Cycle";
}

void populate_vertices(Vertex * vertices, int n) {
  vertices = new Vertex[n];                         //populating vertex with default value
  for (int i = 0; i < n; i++) {
    vertices[i].tag = i;
    vertices[i].flag = 0;
  }
}

int checkCycle(int ** matrix, Vertex * vertices, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == i)                                       //checking for diagonal and pre-incrementing loop key
        ++j;
      if (matrix[i][j] > 0) {
        if (vertices[j].flag) {
          if (vertices[i].parent != j)
            return 1;
        }else
          vertices[j].parent = i;
      }
    }
    vertices[i].flag = 1;
  }
  return 0;
}

void populate(int ** matrix, int s, int low, int high, int parcentage) {

  int c = 0;
  double edges = parcentage / 100.0;
  int max_edges = (s * (s - 1)) / 2;
  double edges_needed = (parcentage * max_edges) / 100.00;

  if((edges_needed - (int) edges_needed) >= 0.50)           //Rounding the edges
    edges_needed = (int) edges_needed + 1;

  cout << "Please Wait..........";
  while (true) {
    srand(time(0));
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (j == i) {
          matrix[i][j] = 0;                                 //initializing diagonals as 0
        } else if (j < i) {
          matrix[i][j] = matrix[j][i];                      //coping transpose keys
        } else if (j > i) {
          double val = (double) rand() / RAND_MAX;
          if (val <= edges) {
            matrix[i][j] = low + rand() % (high + 1 - low);  //random number in a range
            c++;
          } else {
            matrix[i][j] = -1;
          }
        }
      }
    }
    if (c == (int) edges_needed)                        //Checking if total edges meet the needed edges
      break;
    c=0;
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
