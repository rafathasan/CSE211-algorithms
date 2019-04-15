//============================================================================
// Name        : cycle.cpp
// Author      : Rafat Hasan
// Github      : https://github.com/rafathasan/Algorithm-Project/blob/master/cycle.cpp
// Copyright   : GPLv3
// Description : Brute-force cycle detection in C++, Ansi-style
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
  vertices = new Vertex[n];                                   //populating vertex with default value
  for (int i = 0; i < n; i++) {
    vertices[i].tag = i;
    vertices[i].flag = 0;
  }
}

int checkCycle(int ** matrix, Vertex * vertices, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == i)                                           //checking for diagonal and pre-incrementing loop key
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

// Number of Vertex :15
// Lowest weight :5
// Highest weight :30
// 
//   20  12  21  11  12  25  17   9   5  29  16  18  16  10   8
//   28  10  13  22   7  26  23   7  28  11  11   6  27  15  10
//   18  21   8  25  28  27  10  18  10  19  30  26  23  22  24
//   15  14  20  22   9  20  11  11  28  22  20  18  22  26  29
//   23  24  17  27   7  29  23  29  29   7  21  20   9  26  13
//   15   9  10  10  17  30  18  13  17  15  15   5  23  26  27
//   23  22   9  18  30  15  29   7  28  10  28  24  16  23  11
//   29  20  23  10   5   8  20  19  19   9  10  28  30   6   7
//   19   9  14  25  26  20  26   5   6  19  29  11  20  19   9
//   29  16  10  20   6  18  20  16  14  26  22  26  13  20  29
//    5  17  29   9  12  27  21  18  21  22  21  20  17  28  25
//   14  14  16  19  19  26   5  19  27  25  28  27  12  17  23
//   18   7   6  28   7  19  15  23  10  30  15  26   5  24  28
//    8  15  18  16  29  14  29  12  10  13  28  14  23  27  18
//   15  15  25  10  18  25  28  28  30  22  30   6  17  18  17
// Edge    Weight
// 6 - 1   23
// 6 - 2   10
// 10 - 3  20
// 6 - 4   23
// 0 - 5   15
// 0 - 6   23
// 10 - 7  10
// 6 - 8   26
// 10 - 9  22
// 0 - 10  5
// 10 - 11 28
// 6 - 12  15
// 3 - 13  16
// 10 - 14 30