//============================================================================
// Name        : Dijkstra.cpp
// Author      : Rafat Hasan
// Version     :
// Copyright   : GPLv3
// Description : Dijkstra in C++, Ansi-style
//============================================================================

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include <vector>

using namespace std;

struct Vertex{
    int cost;
    int parent;
    bool flag;
};


void allocate(int** &, int );
void populate(int** matrix,int s,int low,int high,int parcentage);
void display(int** matrix,int s,int mx);
int max(int** matrix, int s);
int num_dig(int n);
void select(int& s,int& d,int n);
void randomized(int& s,int& d,int n);
void dijkstra(int** G,int n,int s,int d);
int minVertex(Vertex* vertex,int n);
void print_path(int s,int d,Vertex *&vertex);
void print(int s,int d,Vertex *&vertex);


int main(){
    int **matrix;
    int n,p,low,high,source,dest;
    bool desicion=false;
    cout<<"Number of Vertex :";
    cin>>n;
    cout<<"percentage of Edges(1-100): ";
    cin>>p;
    cout<<"Lowest weight :";
    cin>>low;
    cout<<"Highest weight :";
    cin>>high;
    allocate(matrix,n);
    populate(matrix,n,low,high,p);
    display(matrix,n,max(matrix,n));
    int ch;

        cout<<"1. select source & destination. "<<endl;
        cout<<"2. Random source & destination"<<endl;
        cout<<"3. exit."<<endl;
    do{
        cin>>ch;
        switch(ch){
        case 1: select(source,dest,n);
                dijkstra(matrix,n,source,dest);
                break;
        case 2: randomized(source,dest,n);
                dijkstra(matrix,n,source,dest);
                break;
        }
    }while(ch!=3);
    return 0;
}

void allocate(int** &matrix, int sz){
	matrix =new int*[sz];
    for(int i = 0; i < sz; i++)
    matrix[i] = new int[sz];
}

void populate(int** matrix,int s,int low,int high,int parcentage){

 int count=0;
 double edges=parcentage/100.0;
 int max_edges=(s*(s-1))/2;
 double estimated_edges=(parcentage*max_edges)/100.00;

 if((estimated_edges-(int)estimated_edges)>=0.50)estimated_edges=(int)estimated_edges+1;


 cout<<"Please Wait..........";
 while(true){
   srand(time(0));
   for(int i=0;i<s;i++){
     for(int j=0;j<s;j++){
        if(j==i){
            matrix[i][j]=0;
        }

        else if(j<i){
            matrix[i][j]=matrix[j][i];
        }

        else if(j>i){
              double val=(double)rand()/RAND_MAX;
               if(val<=edges){
                        matrix[i][j] = low+rand()%(high+1-low);
                        count++;
            }
            else {
                matrix[i][j]=-1;
            }
        }
      }
    }
    if(count==(int)estimated_edges)
    break;
   count=0;
   }
}


int max(int** matrix, int s){
	int mx=matrix[0][0];
	for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
		if(matrix[i][j]>mx)mx=matrix[i][j];
	}
	}
	return mx;
}



int num_dig(int n){
	if(n<10)return 1;
	return 1+num_dig(n/10);
}

void display(int** matrix,int s,int mx){
  cout<<endl;
  for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
            cout<<setw(num_dig(mx)+2)<<matrix[i][j];
      }
      cout<<endl;
  }
}

void select(int& s,int& d,int n){
    cout<<"Enter source & destination between "<<"1 to "<<n<<endl;
    cout<<"Enter source node :";
    cin>>s;
    cout<<"Enter destination node :";
    cin>>d;

    while(s<1 || s>n || d<1 || d>n){
    cout<<"Invalid!!"<<endl;
    cout<<"Enter source & destination between "<<"1 to "<<n<<endl;
    cout<<"Enter source node :";
    cin>>s;
    cout<<"Enter destination node :";
    cin>>d;
    }
    s=s-1;
    d=d-1;
}

void randomized(int& s,int& d,int n){

    srand(time(0));
    s=rand()%n;
    while(true){
    srand(time(0));
    d=rand()%n;
    if(d!=s){
        break;
    }
    }
}


void dijkstra(int** G,int n,int s,int d){


bool found=false;
Vertex* vertex=new Vertex[n];
for(int i=0;i<n;i++){
    vertex[i].cost = -1;
    vertex[i].parent= -1;
    vertex[i].flag= false;
}

    vertex[s].cost=0;
    vertex[s].parent=s;
    vertex[s].flag=false;

for(int i=0;i<n;i++){
    int min=minVertex(vertex,n);
     if(vertex[min].cost==-1 )
        break;
    else if(min==d){
        found=true;
        print_path(s,d,vertex);
        break;
    }
    vertex[min].flag=true;
    for(int j=0;j<n;++j){
        if(G[min][j]>0 && !vertex[j].flag){
            int cost=vertex[min].cost+G[min][j];
             if(cost<vertex[j].cost || vertex[j].cost==-1){
                vertex[j].cost=cost;
                vertex[j].parent=min;
             }
        }
    }
}

    if (found==false){
        cout<<"Destination from "<<s+1<<" to Source"<<d+1<<endl;
        cout<<"There is no path"<<endl;
    }

}

int minVertex(Vertex* Vertex,int n){
        int minVertex=-1;

        for(int i=0;i<n;i++){
              if(!Vertex[i].flag && (minVertex==-1||(Vertex[i].cost>=0 && Vertex[minVertex].cost==-1) 
                ||(Vertex[i].cost>=0 && Vertex[minVertex].cost>=0 && Vertex[i].cost<=Vertex[minVertex].cost))){
                minVertex=i;
            }
        }
        return minVertex;

}

void print(int source,Vertex*& vertex,int par){
    if(par!=source){
        print(source,vertex,vertex[par].parent);
    }
    cout<<vertex[par].parent<<" => ";
}

void print_path(int s,int d,Vertex *&vertex){
  cout<<"Destination from "<<s+1<<" to Source"<<d+1<<endl;
  vector <int> p;
  int a=d;
  cout<<"total cost :"<<vertex[d].cost<<endl;
while(true){
        p.push_back(vertex[a].parent);
        a=vertex[a].parent;
        if(a==s){
            break;
        }
}

cout<<"path: ";
for (vector<int>::iterator it = p.begin(); it != p.end(); it++)
      cout << *it+1 << " > ";

      cout<<d+1<<endl;
}