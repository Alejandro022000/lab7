#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<algorithm>
#include "ArgumentManager.h"
using namespace std;

bool BFS(int **graph, int start, int end, int size){
  queue<int> q;
  bool *visited = new bool[size];
  for(int i = 0; i < size; i++)
    visited[i] = false;
  q.push(start);
  int v;
  while(!q.empty()){
    v = q.front();
    q.pop();
    if(v == end){
      delete [] visited;
      return true;
    }
    if(!visited[v])
      visited[v] = true;
    for(int i = 0; i < size; i++){
      if(graph[v][i] != 0 && !visited[i]){
        q.push(i);
      }
    }
  }
  delete [] visited;
  return false;
}

int main(int argc, char *argv[]){
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  int n, start, end = 0;
  input >> n;
  input >> start;
  input >> end;

  int **graph = new int*[n];
  for(int i = 0; i < n; i++)
    graph[i] = new int[n];

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      graph[i][j] = 0;
    }
  }

  string inStr, str;
  int i, j = 0;
  
  while(getline(input, inStr)){
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    
    if(inStr == " " || inStr.length() == 0)
      continue;
    
    i =  stoi(inStr.substr(0,inStr.find(' ')));
    j = stoi(inStr.substr(inStr.find(' ') + 1, inStr.length() - inStr.find(' ') - 1));

    graph[i][j] = 1;
    graph[j][i] = 1;
  }

  if(BFS(graph, start, end, n)){
    output << "true" << endl;
  }
  else{
    output << "false" << endl;
  }
  
  for(int i = 0; i < n; i++)
    delete [] graph[i];
  delete [] graph;


  return 0;
}