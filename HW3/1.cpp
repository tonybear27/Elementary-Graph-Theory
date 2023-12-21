#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef priority_queue< pii, vector<pii>, greater<pii> > pqv;

const int INF = INT_MAX;
int n, m, mi, who;
vector<bool> used;

void add(ll& ans, vector<vector<pii> >& offer, vector<ll>& cost, pqv& pq, int use, int val) 
{
    used[use] = 1;
    ans += val;

    for (auto& edge : offer[use]) {
        int to = edge.first;
        int weight = edge.second;

        if (!used[to])
            pq.push(make_pair(weight, to));
    }

    if (cost[use] < mi) {
        mi = cost[use];
        who = use;
    }
}

ll solve(vector<vector<pii> >& offer, vector<ll>& cost){

	mi = cost[0];
    who = 0;
	used[0] = 1;

    // 
	int pt = 0;
	vector<pii> duty(n - 1);
	for(int i = 1 ; i < n ; i++)
        duty[i - 1] = make_pair(cost[i], i);

	sort(duty.begin(), duty.end());

	pqv pq;
	for(auto &[to , weight] : offer[0])
		pq.push(make_pair(weight, to));

	ll ans = 0;
	for(int i = 1 ; i < n ; i++){
		while(pq.size() && used[pq.top().second]) 
            pq.pop();

		while(pt < n-1 && used[duty[pt].second]) 
            pt++;

		int tmp = mi + (duty[pt].first);
		int tmp2 = pq.empty() ? INF : pq.top().first;

		if(tmp > tmp2){
			auto [weight , b] = pq.top();
			pq.pop();
			add(ans, offer, cost, pq, b, tmp2);
		}
		else{
			int to = duty[pt++].second;
			add(ans, offer, cost, pq, to, tmp);
		}
	}

	return ans;
}

int main(){
	int Q;
	cin >> Q;

    while(Q--) {
	    
        cin >> n >> m;

        vector<ll> cost(n);
        vector<vector<pii> > offer(n);
        used.clear();
        used.resize(n, 0);

        for(int i = 0 ; i < n ; i++) 
            cin >> cost[i];

        for(int i = 0; i < m; i++){
            ll a, b, w;
            cin >> a >> b >> w;
            a--;
            b--;

            offer[a].push_back(make_pair(b, w));
            offer[b].push_back(make_pair(a, w));
	    }

        cout << solve(offer, cost) << endl;
    }
    return 0;
}