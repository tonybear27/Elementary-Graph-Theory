#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;

struct Node{
    int out;
    int in;
    int weight;
}node[1000];

int main()
{
    int n, m;
    cin>>n>>m;

    vector<vector<int> > matrix(n, vector<int>(n));
    vector<vector<int> > graph(m, vector<int>(3));
    for(int i=0; i<m; i++)
        for(int j=0; j<3; j++)
            cin>>graph[i][j];

    for(int i=0; i<m; i++) {
        matrix[graph[i][0]-1][graph[i][1]-1]=graph[i][2];
        for(int j=0; j<3; j++) {
            if (j==0) 
                node[graph[i][j]-1].out++;
            else if (j==1)
                node[graph[i][j]-1].in++;
            else
                node[graph[i][j-2]-1].weight=node[graph[i][j-1]-1].weight=graph[i][j];
        }
    }

    for (int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
            cout<<matrix[i][j]<<' ';
        cout<<endl;
    } 
    for (int i=0; i<n; i++)
        cout<<node[i].in<<' '<<node[i].out<<endl;

    return 0;
}