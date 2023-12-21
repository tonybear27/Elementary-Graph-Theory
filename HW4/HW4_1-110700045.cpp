#include <iostream>
#include <vector>
#define min(a, b) (a) > (b) ? (b): (a) 
using namespace std;

vector<int> dis, low;
vector<bool> isVisited, isAP;

void auxiliary(vector<int> graph[], int u, int par, int& time) {
    
    int child = 0;
    isVisited[u] = 1;
    dis[u] = low[u] = ++time;

    for(auto v: graph[u]) {
        if(!isVisited[v]) {
            child++;
            auxiliary(graph, v, u, time);

            low[u] = min(low[u], low[v]);

            if(par != -1 && low[v] >= dis[u])
                isAP[u] = 1;
        } 
        else if(v != par)
            low[u] = min(low[u], dis[v]);
    }

    if(par == -1 && child > 1)
        isAP[u] = 1;
}

void solve(vector<int> graph[], int n) {

    dis.resize(n, 0);
    low.resize(n);
    isVisited.resize(n, 0);
    isAP.resize(n, 0);

    int time = 0, par = -1;

    for(int i = 0; i < n; i++) {
        if(!isVisited[i]) {
            auxiliary(graph, i, par, time);
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if (isAP[i])
            cnt ++;
    }

    cout << cnt << endl;

    for(int i = 0; i < n; i++) {
        if(isAP[i]) {
            cout << i + 1 << ' ';
        }
    }
}

void init(vector<int> graph[], int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

int main() {

    int n, e;
    cin >> n >> e;

    vector<int> graph[n];
    for(int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        init(graph, u, v);
    }

    solve(graph, n);

    return 0;
}