#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> tree;

int getHeight(vector<int>& height, int node){
    if(height[node])
        return height[node];
    if(!tree[node].size())
        return 0;

    int h = 0;
    for(int i: tree[node]) {
        int temp = getHeight(height, i);
        h = h >temp ? h: temp;
    }

    height[node] = h + 1;
    return height[node];
}

void dfs(vector<int>& height, vector<int>& par, int root) {

    getHeight(height, root);

    for(int i: tree[root]){
        par[i] = root;
        dfs(height, par, i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> height(n + 1, 0), par(n + 1, -1);
    vector<bool> seen(n + 1, 0);

    tree.resize(n + 1);

    for(int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        if(seen[y])
            tree[y].push_back(x);
        else
            tree[x].push_back(y);
        seen[x] = seen[y] = 1;
    }

    dfs(height, par, 1);

    for(int i = 1; i <= n; i++)
        cout << height[i] << " " << par[i] << endl;
    return 0;
}