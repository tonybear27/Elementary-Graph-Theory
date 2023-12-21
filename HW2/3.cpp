#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e6+5;

vector<int> glass[MAXN], C_key;
int n, m;
int degree[MAXN] = {0},  num, D_key[MAXN] ={0};
bool visited[MAXN] = {0};

void dfs(int s) {
    for(int i : glass[s]) {
        if(!visited[i] && degree[i]!=3){
            visited[i] = 1;
            num++;

            dfs(i);
        }
    }
}

void key() {
    vector<int> leaf;
    for(int i=0; i<n; i++){
        if(!visited[i] && degree[i]==1){
            visited[i] = 1;
            num = 1;
            leaf.push_back(i);

            dfs(i);
            D_key[num]++;
        }
    }

    if(leaf.size() != m+2)
        cout << "NO";
    else {
        for(int i : C_key) {
            int f = 1;
            if(D_key[i]) {
                D_key[i]--;
                f = 0;
            }
            if(f) {
                cout << "NO";
                return;
            }
        }
        cout << "YES";
    }

    return;

}

int main(){
    ios::sync_with_stdio(0); 
    cin.tie(0);
    
    cin >> n;
    
    for(int i=1;i<n;i++){
        int a, b;
        cin >> a >> b;

        glass[a].push_back(b);
        glass[b].push_back(a);
        degree[a]++; 
        degree[b]++;
        
    }
    
    cin >> m;
    
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        C_key.push_back(x);
    }

    key();

    return 0;
}