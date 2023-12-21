#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

string s1, s2;
vector<vector<string> > graph;

int overlap(const string s1, const string s2, string &s) {
    int max = INT_MIN;
    int len1 = s1.length();
    int len2 = s2.length();

    string a1="", a2="";

    if(len1==0 || len2==0)
        return max;

    /* Compare prefix */
    for (int i=1; i <= min(len1, len2); i++) {
        if (!s1.compare(0, i, s2, len2-i, i)) {
            if (max < i) {
                max = i;
                s = s2 + s1.substr(i);
            }
        }
    }
    
    /* Compare suffix */
    for (int i = 1; i <= min(len1, len2); i++) {
        if(!s1.compare(len1 - i, i, s2, 0, i)) {
            if (max < i) {
                max = i;
                s = s1 + s2.substr(i);
            }
        }
    }

    return max;
}

/* Check s1 is substring of s2 */
bool isSubstring(string s1, string s2) {
   
   if (s2.find(s1) != string::npos)
        return true;
    return false;
}

string overlap(string &s1, string &s2) {

    int len1 = s1.length(), len2 = s2.length();
    int index = 0, len = 1;

    while(len <= min(len1, len2)) {
        if(s1 != "" && s2 != "") {
            if(s1 != s2 && s2.find(s1) != string::npos)
               s1="";
            else if(s1.substr(len1 - len) == s2.substr(0, len))
                index=len;
        }
        len++;
    }
        
    string result = s2.substr(index);
    
    return result;
}

string solve(vector<vector<string> >& dp, vector<string>& arr, int prev, int mask, int n) {

    if(dp[prev][mask] != "") 
        return dp[prev][mask];

    string res = "";
    int m = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(mask & (1<<i)) 
            continue;
        
        string ss = solve(dp, arr, i, mask | (1<<i), n);
        
        //cout << ss.length() << " " << ss <<endl;

        string s = graph[prev][i] + ss;
        int len = s.length();
        if(len < m || (len == m && s < res)) {
            m = s.length();
            res = s;
        }
    }

    dp[prev][mask] = res;

    return dp[prev][mask];
}

string shortest(vector<string>& arr) {

    int n = arr.size();
    sort(arr.begin(), arr.end());
    graph.resize(n, vector<string>(n, ""));
    vector<vector<string> > dp(n, vector<string> ((1 << (n+1)), ""));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i!=j)
                graph[i][j] = overlap(arr[i], arr[j]);
        }
    }

    string ans = "";
    int m = INT_MAX;
    int mask = 0;

    for(int i = 0; i < n; i++) {
        string ss = solve(dp, arr, i, mask | (1 << i), n);
        //cout << ss.length() << ' ' << ss << endl;
        string s = arr[i] + ss;

        int len = s.length();
        if(len < m || (len == m && s < ans)) {
            m = s.size();
            ans = s;
        }
    }

    return ans;
}

void checkSubstring(vector<string>& arr) {

    for (int i = 0; i < int(arr.size()); i++) {
        for (int j = 0; j < int(arr.size()); j++) {
            bool flag = 0;
            if (i != j) {
                flag = isSubstring(arr[i], arr[j]);
            }
            if (flag)
                arr[i]="";
        }
    }
}

void lex(string &s1, string s2) {
    bool res = s1 >= s2 ? 0: 1;
    if (res) 
        s1 += s2;
    else 
        s1 = s2 + s1;
}

string shortest(vector<string> arr, int len) {

    while (len != 1) {
        int max = INT_MIN;
        int l, r;

        string resS;
       
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                
                if(i!=j) {
                    string s;
                    
                    int res = overlap(arr[i], arr[j], s);

                    if (max < res) {
                        max = res;
                        resS.assign(s);
                        l = i;
                        r = j;
                    }
                }
            } 
        }
        len--;
        if (max != INT_MIN) {
            arr[l] = resS;
            arr.erase(arr.begin() + r);
        }

    }

    sort(arr.begin(), arr.end());
    string ans="";
    for (int i=0; i<arr.size(); i++) {
        ans+=arr[i];
    }
    
    return ans;
}
int main() {
    int n;
    cin >> n;

    vector<string> arr (n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    checkSubstring(arr);

    if (n >= 10) {
        sort(arr.begin(), arr.end());
        sort(arr.begin() + 1, arr.end(), greater<string>());
        cout << shortest(arr, arr.size());
    }
    else
        cout <<shortest(arr);
        
    return 0;
}