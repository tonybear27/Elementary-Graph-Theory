#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

bool isK5(bitset<15> subdivision[], int n, int m) {
    
    vector<int> k5;

	for(int i = 0; i < n; i++) 
		if (subdivision[i].count() == 4) 
			k5.push_back(i);

	if (k5.size() == 5) {
		set<int> s;
		for (int &x : k5) {
			s.insert(x);
			for (int i = 0; i < n; i++) 
                if (subdivision[x][i]) 
                    s.insert(i);
        }

        if (s.size() == 5)
            return 0;
    }

    return 1;
}

bool isK33(bitset<15> subdivision[], int n, int m) {

    vector<pair<int, vector<int> > > k33;

    for (int i = 0; i < n; i++) {

        if (subdivision[i].count() == 3) {
            
            vector<int> tmp;

            for (int j = 0; j < n; j++) 
                if (subdivision[i][j]) 
                    tmp.push_back(j);


            k33.emplace_back(i , tmp);
        }
    }

    sort(k33.begin(), k33.end(), [&](const pair<int,vector<int> > &a , const pair<int,vector<int> > &b) {
        return a.second < b.second;
    });

    if (k33.size() == 6	&& k33[0].second == k33[1].second && k33[1].second == k33[2].second && k33[3].second == k33[4].second && k33[4].second == k33[5].second && k33[2].second != k33[3].second) 
        return 0;
    
    return 1;
}

void solve(vector<pii>& Graph, int n, int m) {

	bool flag = 1;
	for (int edge = 1; edge < (1 << m); edge++) {

		if(!flag) 
            break;

		bitset<15> subdivision[15];
		for (int j = 0; j < m; j++) {

			if (edge >> j & 1) {
				int a = Graph[j].first;
                int b = Graph[j].second;

				subdivision[a][b] = 1; 
                subdivision[b][a] = 1;
			}
		}

		bool f = 1;
		while (f) {

			f = 0;

			for (int i = 0; i < n; ++i) {

				if (subdivision[i].count() == 2) {
					
                    f = 1;
					vector<int> del;
					
                    for (int j = 0; j < n; j++) {
						if (subdivision[i][j]) 
							del.push_back(j);
					}

					int a = del[0];
                    int b = del[1];

					subdivision[a][i] = subdivision[i][a] = 0;
					subdivision[b][i] = subdivision[i][b] = 0;
					subdivision[a][b] = subdivision[b][a] = 1;
				}
			}
		}
		

		flag = isK33(subdivision, n, m) && isK5(subdivision, n, m);
		
	}

	cout << (flag ? "Yes" : "No") << '\n';
}

int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);

    int Q;
	cin >> Q;
	while(Q--) {
		int n, m; 
        cin >> n >> m ;
        
        vector<pii> Graph;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            Graph.emplace_back(--u, --v);
        }

        solve(Graph, n, m);
	}

    return 0;
}