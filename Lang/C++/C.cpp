/*input
8
5 4 0 0 6 0 0 0 
10
2 1 5 4 6 8 3 7 
2 1 5 3 8 6 4 7 
1 5 2 4 7 8 6 3 
3 2 4 1 5 8 6 7 
2 1 3 4 7 5 6 8 
1 3 5 2 8 7 6 4 
1 5 2 4 8 7 3 6 
2 1 4 5 6 7 8 3 
1 2 5 4 8 6 3 7 
2 1 5 4 3 6 8 7 
*/
// C++ program to print all topological sorts of a graph 
#include <bits/stdc++.h> 
using namespace std; 

class Graph 
{ 
  int V; // No. of vertices 

  // Pointer to an array containing adjacency list 
  list<int> *adj; 

  // Vector to store indegree of vertices 
  vector<int> indegree; 

  // A function used by alltopologicalSort 
  void alltopologicalSortUtil(vector<int>& res, 
                bool visited[]); 

public: 
  Graph(int V); // Constructor 

  // function to add an edge to graph 
  void addEdge(int v, int w); 

  // Prints all Topological Sorts 
  void alltopologicalSort(); 
}; 

// Constructor of graph 
Graph::Graph(int V) 
{ 
  this->V = V; 
  adj = new list<int>[V]; 

  // Initialising all indegree with 0 
  for (int i = 0; i < V; i++) 
    indegree.push_back(0); 
} 

// Utility function to add edge 
void Graph::addEdge(int v, int w) 
{ 
  adj[v].push_back(w); // Add w to v's list. 

  // increasing inner degree of w by 1 
  indegree[w]++; 
} 

// Main recursive function to print all possible 
// topological sorts 
map < string, bool > mp;
void Graph::alltopologicalSortUtil(vector<int>& res, 
                bool visited[]) 
{ 
  // To indicate whether all topological are found 
  // or not 
  bool flag = false; 
  // cout << "hello";
  for (int i = 0; i < V; i++) 
  { 
    // If indegree is 0 and not yet visited then 
    // only choose that vertex 
    if (indegree[i] == 0 && !visited[i]) 
    { 
      // reducing indegree of adjacent vertices 
      list<int>:: iterator j; 
      for (j = adj[i].begin(); j != adj[i].end(); j++) 
        indegree[*j]--; 

      // including in result 
      // cout << i << "\n";
      res.push_back(i); 
      visited[i] = true; 
      alltopologicalSortUtil(res, visited); 

      // resetting visited, res and indegree for 
      // backtracking 
      visited[i] = false; 
      res.erase(res.end() - 1); 
      for (j = adj[i].begin(); j != adj[i].end(); j++) 
        indegree[*j]++; 

      flag = true; 
    } 
  } 

  // We reach here if all vertices are visited. 
  // So we print the solution here 
  if (!flag) 
  { 
    string s = "";
    for (int i = 0; i < res.size(); i++) 
      s += to_string(res[i]+1) + "|";
    mp[s] = 1;
  } 
} 

// The function does all Topological Sort. 
// It uses recursive alltopologicalSortUtil() 
void Graph::alltopologicalSort() 
{ 
  // Mark all the vertices as not visited 
  bool *visited = new bool[V]; 
  for (int i = 0; i < V; i++) 
    visited[i] = false; 

  vector<int> res; 
  alltopologicalSortUtil(res, visited); 
} 

// Driver program to test above functions 
int main() 
{ 
  // Create a graph given in the above diagram 
  int n;
  cin >> n;
  Graph g(n); 
  for(int i = 1; i <= n; i ++) {
    int x;
    cin >> x;
    if(not x) continue;
    g.addEdge(i - 1, x - 1);
  }

  g.alltopologicalSort(); 
  int k;
  cin >> k;
  // for(auto x: mp) {
  //   cout << x.first << " ";
  // }
  for(int i = 1; i <= k; i ++) {
    string s = "";
    for(int j = 0; j < n; j ++) {
      int x;
      cin>> x;
      s += to_string(x) + "|";
    }  
    if(mp[s] == 0) {
      cout << "error\n";
    }
  }
  return 0; 
} 
