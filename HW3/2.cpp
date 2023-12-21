#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
typedef vector<vector<pair<ll, ll> > > vvp;
typedef priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pqv;

vector<ll> dist, dist2, dist3;
const ll INF = LONG_MAX;

void construct(vvp& graph, ll u, ll v, ll weight) {
    u--;
    v--;
    graph[v].push_back(make_pair(weight, u));
}

void dijkstra(vvp& graph, vector<ll>& dist, pqv& pq) {

    while(!pq.empty()) {
        ll u = pq.top().second;
        ll dis = pq.top().first;
        pq.pop();

        if(dis > dist[u])
            continue;
        
        for(auto& edge: graph[u]) {
            ll v = edge.second;
            ll weight = edge.first;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void dijkstra(vvp& graph, ll s, ll n) {

    dist.resize(n, INF);

    pqv pq;
    dist[s] = 0;
    pq.push(make_pair(0, s));

    dijkstra(graph, dist, pq);

    dist2.resize(n, INF);
    dist2[n - 1] = 0;
    pq.push(make_pair(0, n - 1));

    dijkstra(graph, dist2, pq);

    for(ll i = 0; i < n; i++)
        if(dist[i]!=INF && dist2[i]!=INF)
            graph[n].push_back(make_pair(dist[i] + dist2[i], i));

    dist3.resize(n + 1, INF);
    dist3[n] = 0;
    pq.push(make_pair(0, n));

    dijkstra(graph, dist3, pq);

    dist3.pop_back();
}

int main() {
    
    ll T, sub;

    cin >> T >> sub;
    while (T--) {
        ll n, m, k;
        cin >> n >> m >> k;

        vvp graph(n + 1);
        for (ll i = 0; i < m; i++) {
            ll u, v, w;
            cin >> u >> v >> w;
            construct(graph, u, v, w);
        }
        
        dijkstra(graph, 0, n);

        if(k == 1) {
            for (ll i: dist)
                if (i == INF)
                    cout << -1 << ' ';
                else
                    cout << i << ' ';
        }
        else {
            for(ll i: dist3)
                if (i == INF)
                    cout << -1 << ' ';
                else
                    cout << i << ' ';
        }

        dist.clear();
        dist2.clear();
        dist3.clear();

        puts("");
    }

    return 0;
}