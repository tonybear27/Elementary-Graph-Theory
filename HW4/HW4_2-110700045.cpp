#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int maxn = 1200;
const int inf = 1e9+7;

class Map {
private:

	struct Edge {
		int to , cap , rev;
		Edge(int to , int cap , int rev):to(to) , cap(cap) , rev(rev) {}	
	};

	vector<Edge> graph[maxn];
	int n , s , t;
	int level[maxn] , iter[maxn];

	void bfs() {
		fill(level , level+maxn , -1);

        level[s] = 0;

		queue<int> q;
		q.push(s);

		while(!q.empty()) {
			int now = q.front(); 
            q.pop();

			for(Edge &e: graph[now]) {
				if(e.cap > 0 && level[e.to] == -1){
					level[e.to] = level[now]+1;
					q.push(e.to);
				}
			}
		}
	}

	int dfs(int now , int flow) {
		if(now == t) 
            return flow;

		for(int &i = iter[now] ; i < graph[now].size() ; i++) {

			Edge &e = graph[now][i];
			if(e.cap > 0 && level[e.to] == level[now]+1){
				int ret = dfs(e.to , min(e.cap , flow));
				if(ret > 0){
					e.cap -= ret;
					graph[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}

		return 0;
	}

public:

    Map(int n, int s, int t): n(n), s(s), t(t) {
        for(int i = 0 ; i <= n ; i++) 
            graph[i].clear();
    }

    void add(int a , int b , int cap){
		graph[a].push_back(Edge(b , cap , graph[b].size()));
		graph[b].push_back(Edge(a , 0 , graph[a].size() - 1));
	}

    int getFlow() {
		int ret = 0 ;
		while(true) {
			bfs();
			
            if(level[t] == -1) 
                break;
			
            fill(iter , iter+maxn , 0);

			int tmp;
			while((tmp=dfs(s,inf)) > 0)
				ret += tmp;
		}

		return ret;
	}
};

int main(){

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    int n , m , k;
	cin >> n >> m >> k;


	int start = n + m + 1;
	int end = n + m + 10;
	int med = n + m + 2;

    struct Map flow(n + m + 21, start, end);

	flow.add(start , med , k);
    
	for(int i = 1 ; i <= n ; i++){
		flow.add(start , i , 1);
		flow.add(med , i , 1);
	}

	for(int i = 1 ; i <= m ; i++)
		flow.add(n + i , end , 1);

	for(int i = 1 ; i <= n ; i++){
		int num; 
        cin >> num;
		while(num--) {
			int to ; 
            cin >> to;
			
            flow.add(i , n + to , 1);
		}
	}

	cout << flow.getFlow() << endl;

    return 0;
}