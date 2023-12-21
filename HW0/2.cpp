#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int num;
    cin>>num;
    
    vector<int> v(num);
    map<int, int> m; 
    m.clear();

    for(int i=0; i<num; i++)
    {
        cin>>v[i];
        m[v[i]]++;
    }

    int number;
    int max=0;
    
    for(map<int, int>::iterator it=m.begin(); it!=m.end(); it++)
    {
        if(it->second>=max)
        {
            max=it->second;
            number=it->first;
        }
    }

    cout<<number<<' '<<max<<endl;

    return 0;
}