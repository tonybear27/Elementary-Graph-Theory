#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n;
int longest = -1, maxN = -1;


void addEdge(vector<int> graph[], int s, int d) {
    graph[s].push_back(d);
    graph[d].push_back(s);
}

void dfs(vector<int> graph[], vector<bool>& isVisited, int node, int d) {

    isVisited[node] = 1;

    if (d > longest) {
        longest = d;
        maxN = node;
    }

    for (auto x: graph[node]) {
        if (!isVisited[x]) 
            dfs(graph, isVisited, x, d+1);
    } 

}

int main()
{
    cin >> n;

    vector<int> graph[n];
    vector<bool> isVisited(n, 0);

    for(int i=0; i<n-1; i++) {
        
        int u, v;
        cin >> u >> v;
        u--; 
        v--;
        addEdge(graph, u, v);
    }

    dfs(graph, isVisited, 0, 0);
    longest = -1;
    fill(isVisited.begin(), isVisited.end(), 0);
    dfs(graph, isVisited, maxN, 0);

    cout << longest;

    return 0;
}