//============================================================================
// Name        : Longest Common Subsequence.cpp
// Author      : Rafat Hasan
// Github     : https://github.com/rafathasan/Algorithm-Project/blob/master/lcs.cpp
// Copyright   : GPLv3
// Description : LCS in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

void mapping(int ** & , char ** & , string * , int, int);
void print(char ** & , string * , int, int);
void allocate(int**& ary, char**& sign, int x,int y);
void initialize(int** ary, char** sign, int x,int y);
void display(int** ary, char** sign, int x,int y);

int main() {
  int ** ary;
  char ** sign;
  string words[2];

  cin>>words[0]>>words[1];
  //getline(cin, words[0]);
  //getline(cin, words[1]);

  int x = words[0].length();
  int y = words[1].length();

  cout << x << endl;
  cout << y << endl;

  void allocate(ary, sign, x, y);
  void initialize(ary, sign, x, y);

  mapping(ary, sign, words, x, y);
  display(ary, sign, x, y);
  print(sign, words, x, y);
  return 0;
}

void display(int** ary, char** sign, int x,int y){
  for (int i = 0; i < x + 1; i++) {       //displaying both int array and char array
    for (int j = 0; j < y + 1; j++) {
      cout << ary[i][j] << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < x + 1; i++) {
    for (int j = 0; j < y + 1; j++) {
      cout << sign[i][j] << " ";
    }
    cout << endl;
  }
}

void initialize(int** ary, char** sign, int x,int y){
  for (int i = 0; i < x + 1; i++) {         //initializing int array and char array by words length
    for (int j = 0; j < y + 1; j++) {
      ary[i][j] = 0;
      sign[i][j] = '0';
    }
  }
}

void allocate(int**& ary, char**& sign, int x,int y){
  ary = new int * [x + 1];                  //allocating int array and char array
  sign = new char * [x + 1];

  for (int i = 0; i < x + 1; i++) {
    ary[i] = new int[y + 1];
    sign[i] = new char[y + 1];
  }
}

void print(char**& sign, string * words, int x, int y) { 
                                                    //printing the Longest Common Subsequence by using char array
  if (sign[x][y] == 'D') {
    print(sign, words, x - 1, y - 1);
    cout << words[0][x - 1];
  } else if (sign[x][y] == 'L') {
    print(sign, words, x, y - 1);
  } else if (sign[x][y] == 'U') {
    print(sign, words, x - 1, y);
  } else {
    return;
  }
}

void mapping(int ** & ary, char ** & sign, string * words, int x, int y) {
  cout << "size: " << x << " " << y << endl;            //mapping the int array and char array

  for (int i = 1; i < x + 1; i++) {
    for (int j = 1; j < y + 1; j++) {
      if (words[0][i - 1] == words[1][j - 1]) {
        ary[i][j] = ary[i - 1][j - 1] + 1;
        sign[i][j] = 'D';
      } else {
        if (ary[i][j - 1] > ary[i - 1][j]) {
          ary[i][j] = ary[i][j - 1];
          sign[i][j] = 'L';
        } else if (ary[i][j - 1] == ary[i - 1][j]) {
          ary[i][j] = ary[i][j - 1];
          sign[i][j] = 'U';
        } else {
          ary[i][j] = ary[i - 1][j];
          sign[i][j] = 'U';
        }
      }
    }
  }
}
