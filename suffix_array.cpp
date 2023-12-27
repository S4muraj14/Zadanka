#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e5+7;
const int base = 18;

int kmr[max_n][base];
pi tab[max_n];

vi s1[max_n];
vi s2[max_n];

pi ans[max_n];

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    int n = s.length();
    
    int pow = 0;
    for(int i = 1; i < base; i++){
        if((1<<i) > n){
            pow = i;
            break;
        }
    }

    for(int i = 0; i < n; i++)
        kmr[i][0] = int(s[i]-'0')+1;

    for(int i = 1; i <= pow; i++){
        for(int j = 0; j < n; j++){
            tab[j].st = kmr[j][i-1];
            if(j+(1<<(i-1)) >= n) tab[j].nd = 0;
            else tab[j].nd = kmr[j+(1<<(i-1))][i-1];
            s1[tab[j].nd].push_back(j);
        }

        for(int j = 0; j <= max(80,n); j++){
            for(auto x:s1[j])
                s2[tab[x].st].push_back(x);
            s1[j].clear();
        }

        int ind = 0;
        for(int j = 0; j <= max(80,n); j++){
            int prev = -1;
            for(auto x:s2[j]){
                if(tab[x].nd != prev) ind++;
                kmr[x][i] = ind;
                if(i == pow) cout << x << '\n';
                prev = tab[x].nd; 
            }
            s2[j].clear();
        }
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
