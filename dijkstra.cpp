//============================================================================
// Name        : Dijkstra.cpp
// Author      : Rafat Hasan
// Github     : https://github.com/rafathasan/Algorithm-Project/blob/master/dijkstra.cpp
// Copyright   : GPLv3
// Description : Dijkstra's algorithm in C++, Ansi-style
//============================================================================

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;

struct Vertex {
  int cost;
  int parent;
  bool flag;
};

void allocate(int ** & , int);
void populate(int ** matrix, int s, int low, int high, int parcentage);
int max(int ** matrix, int s);
int num_dig(int n);
void dijkstra(int ** G, int n, int s, int d);
int minVertex(Vertex * vertex, int n);
void print_path(int s, int d, Vertex * & vertex);
void display(int ** matrix, int s, int mx);

int main() {
    int ** matrix;
    int n, p, low, high, source, dest;
    bool desicion = false;
    cout << "Number of Vertex :"<<endl;;
    cout << "percentage of Edges(1-100): "<<endl;
    cout << "Lowest weight :"<<endl;
    cout << "Highest weight :"<<endl;
    cin >> n >> p >> low >> high;

    allocate(matrix, n);
    populate(matrix, n, low, high, p);
    display(matrix, n, max(matrix, n));
    int ch;

    cout << "Enter Source And Destination: " << endl;
    cin >> source>>dest;
    if(source<n&&dest<n)
    dijkstra(matrix, n, source-1, dest-1);
    else
        cout<<"Invalid Source And Destination"<<endl;
    return 0;
}

void allocate(int ** & X, int sz) {
  X = new int * [sz];
  for (int i = 0; i < sz; i++)                              //initializing 2d array with size
    X[i] = new int[sz];
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

int max(int ** matrix, int s) {
  int mx = matrix[0][0];                                    //finding the maximum value from 2d array
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (matrix[i][j] > mx) mx = matrix[i][j];
    }
  }
  return mx;
}

int num_dig(int n) {
  if (n < 10) return 1;                                     //getting the digit count in a number
  return 1 + num_dig(n / 10);
}

void display(int ** X, int s, int mx) {
  cout << endl;
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      cout << setw(num_dig(mx) + 2) << X[i][j];             //displaying 2d array and allocating whitespace by using maximum digit length
    }
    cout << endl;
  }
}

void dijkstra(int ** X, int n, int s, int d) {

  bool found = false;
  Vertex * vertex = new Vertex[n];
  for (int i = 0; i < n; i++) {
    vertex[i].cost = -1;
    vertex[i].parent = -1;
    vertex[i].flag = false;                             //setting initial value to all vertex
  }

  vertex[s].cost = 0;
  vertex[s].parent = s;                               //setting initial value to source vertex
  vertex[s].flag = false;

  for (int i = 0; i < n; i++) {
    int min = minVertex(vertex, n);                   //setting the minimum
    if (vertex[min].cost == -1)
      break;
    else if (min == d) {
      found = true;
      print_path(s, d, vertex);                       //destination found and calling to print
      break;
    }
    vertex[min].flag = true;
    for (int j = 0; j < n; ++j) {
      if (X[min][j] > 0 && !vertex[j].flag) {
        int cost = vertex[min].cost + X[min][j];      //adding terversal cost to the current vertex
        if (cost < vertex[j].cost || vertex[j].cost == -1) {
          vertex[j].cost = cost;
          vertex[j].parent = min;
        }
      }
    }
  }

  if (found == false) {
    cout << "Destination from " << s + 1 << " to Source" << d + 1 << endl;
    cout << "There is no path" << endl;
  }

}

int minVertex(Vertex * Vertex, int n) {
  int minVertex = -1;                                     //getting unvisited minimum vertex

  for (int i = 0; i < n; i++) {
    if (!Vertex[i].flag && (minVertex == -1 || (Vertex[i].cost >= 0 && Vertex[minVertex].cost == -1) ||
        (Vertex[i].cost >= 0 && Vertex[minVertex].cost >= 0 && Vertex[i].cost <= Vertex[minVertex].cost))) {
      minVertex = i;
    }
  }
  return minVertex;
}

void tervarsal(Vertex* vert, int s, int a) {
    if(s!=a)                                          //recursive function for printing
        tervarsal(vert, s, vert[a].parent);
    cout<< a+1 <<" > ";
}

void print_path(int s, int d, Vertex * & vertex) {    //path printing by calling recursive function
  cout << "Destination: " << s + 1 << "  Source:  " << d + 1 << endl;
  cout << "Total Cost: " << vertex[d].cost << endl;
  tervarsal(vertex, s, d);
}










// Number of Vertex : 15
// percentage of Edges(1-100): 40
// Lowest weight : 5
// Highest weight : 30
//
// Please Wait..........
//    0  -1  14  29  -1  -1  -1  -1  -1  -1  -1  -1  16  -1  30
//   -1   0  16   8  18  -1  24  -1  -1  23  -1  16  -1  19  -1
//   14  16   0  -1  -1  -1  22  14  -1  -1  -1  -1  -1  29  21
//   29   8  -1   0  30  25  -1  -1  -1  -1  18  11  -1  15  16
//   -1  18  -1  30   0  -1  30   9  17  -1  -1   8  -1  -1  -1
//   -1  -1  -1  25  -1   0  -1  19  27  -1  -1  15  -1  -1  19
//   -1  24  22  -1  30  -1   0  -1  -1  -1  -1   6  -1  24  -1
//   -1  -1  14  -1   9  19  -1   0  -1  18  19  10  -1  13   7
//   -1  -1  -1  -1  17  27  -1  -1   0  -1  -1  -1  -1  -1  23
//   -1  23  -1  -1  -1  -1  -1  18  -1   0  -1  -1  -1  -1  10
//   -1  -1  -1  18  -1  -1  -1  19  -1  -1   0   5  29  -1  -1
//   -1  16  -1  11   8  15   6  10  -1  -1   5   0   5  -1  -1
//   16  -1  -1  -1  -1  -1  -1  -1  -1  -1  29   5   0  -1  20
//   -1  19  29  15  -1  -1  24  13  -1  -1  -1  -1  -1   0  -1
//   30  -1  21  16  -1  19  -1   7  23  10  -1  -1  20  -1   0
//
// Enter Source And Destination:
// 5 15
// Destination: 5  Source:  15
// Total Cost: 16
// 5 > 8 > 15 >
