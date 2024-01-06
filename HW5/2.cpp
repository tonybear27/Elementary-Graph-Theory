#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
using namespace std;

int n, m;

class Graph {
private:
    struct Edge {
        int to, rev, flow, cap;
        Edge(int t, int r, int f, int c): to(t), rev(r), flow(f), cap(c) {}
    };

    int n;
    vector<int> level;
    vector<vector<Edge> > adj;
    vector<bool> vis;

    bool bfs(int src, int des) {

        fill(level.begin(), level.end(), -1);
        level[src] = 0;

        queue<int> q;
        q.push(src);

        while( !q.empty() ) {

            int cur = q.front();
            q.pop();

            for(auto &edge: adj[cur]) {

                if(level[edge.to] == -1 && edge.flow < edge.cap){
                    level[edge.to] = level[cur] + 1;
                    q.push(edge.to);
                }

            }
        }

        return level[des] != -1;
    }

    int sendFlow(int u, int flow, int t, vector<int>& idx) {

        if(u == t) return flow;
        
        for(; idx[u] < (int)adj[u].size(); idx[u]++) {

            Edge& e = adj[u][idx[u]];

            if(level[e.to] == level[u] + 1 && e.flow < e.cap) {

                int curFlow = min(flow, e.cap - e.flow);
                int tmpFlow = sendFlow(e.to, curFlow, t, idx);

                if(tmpFlow > 0) {
                    e.flow += tmpFlow;
                    adj[e.to][e.rev].flow -= tmpFlow;

                    return tmpFlow;
                }
            }
        }

        return 0;
    }

public:

    Graph(int n) {
        this->n = n;
        adj = vector<vector<Edge> >(n);
        level = vector<int>(n);
        vis = vector<bool>(n, false);
    }

    void addEdge(int x, int y, int cap) {
        adj[x].push_back(Edge(y, adj[y].size(), 0, cap));
        adj[y].push_back(Edge(x, adj[x].size(), 0, 0));
    }

    int dinic(int s, int t) {
        
        for(int i = 0; i < n; i++) {
            for(Edge& j: adj[i])
                j.flow = 0;
        }

        if(s == t) return -1;

        int total = 0;
        while(bfs(s, t)) {

            vector<int> idx(n, 0);

            while(int flow = sendFlow(s, INT_MAX, t, idx))
                total += flow;
        }

        return total;
    }
};

int main () {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    Graph graph(2 * n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph.addEdge(v, u, 1);
        graph.addEdge(u, v, 1);
    }

    int ans = INT_MAX;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (i != j) 
                ans = min(ans, graph.dinic(i, j));
        }
    }

    cout << ans << endl;

    return 0;
}