#include <bits/stdc++.h>
#include <fstream>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_s = 1200;
const int max_n = 3e5+7;

vi g[max_n];
pi edges[max_n];

char symbol[max_n];
int ind[max_n];
bool off[max_n];
int rep[max_n];

vi g_sqrt[max_s];
bool odw_sqrt[max_s];

//set<pi> ob;
map<pi,int> m; //numer krawedzi dla a<b

ifstream input ("connect.in");
ofstream output ("connect.out");

void dfs(int v, int r){
    //bez nowych krawedzi
    rep[v] = r;
    for(auto x:g[v]){
        if(off[x]) continue;
        pi p = edges[x];
        if(!rep[p.first]) dfs(p.first,r);
        if(!rep[p.second]) dfs(p.second,r);
    }
}

void dfs_sqrt(int v){
    //wszystko na rep
    odw_sqrt[v] = true;
    for(auto x:g_sqrt[v]){
        if(off[x]) continue;
        pi p = edges[x];
        if(!odw_sqrt[rep[p.first]]) dfs_sqrt(rep[p.first]);
        if(!odw_sqrt[rep[p.second]]) dfs_sqrt(rep[p.second]);
    }
}

void algo(int n,int start, int p){
    //usunac krawedzie
    for(int i = start; i < start+p; i++){
        if(symbol[i] == '?') continue;
        off[ind[i]] = true;
    }
    //policzyc spojne   
    int akt = 0;
    for(int i = start; i < start+p; i++){
        if(symbol[i] == '?') continue;
        pi x = edges[i];
        if(!rep[x.first]){
            akt++;
            dfs(x.first,akt);
        }
        if(!rep[x.second]){
            akt++;
            dfs(x.second,akt);
        }
    }

    int ile_poz = 0;
    for(int i = 1; i <= n; i++){
        if(!rep[i]){
            ile_poz++;
            dfs(i,akt);
        }
    }

    //podzial na sqrt, krawedzie bedace od poczatku
    for(int i = start; i < start+p; i++){
        if(symbol[i] == '-'){
            if(ind[i] >= start) continue;

            off[ind[i]] = false;
            int a = edges[i].first;
            int b = edges[i].second;
            g_sqrt[rep[a]].push_back(ind[i]);
            g_sqrt[rep[b]].push_back(ind[i]);
        }
    }

    for(int i = start; i < start+p; i++){
        if(symbol[i] == '+'){
            int a = edges[i].first;
            int b = edges[i].second;
            g_sqrt[rep[a]].push_back(i);
            g_sqrt[rep[b]].push_back(i);
            off[i] = false;
        }

        else if(symbol[i] == '-'){
            off[ind[i]] = true;
        }

        else{
            int ans = ile_poz;
            for(int j = 1; j <= akt; j++){
                if(!odw_sqrt[j]){
                    ans++;
                    dfs_sqrt(j);
                }
            }
            for(int j = 1; j <= akt; j++) odw_sqrt[j] = 0;
            output << ans << '\n';
        }
    }

    //clear
    for(int i = 1; i <= n; i++)
        rep[i] = 0;
    for(int i = 1; i <= akt; i++){
        g_sqrt[i].clear();
        odw_sqrt[i] = 0;
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,k;
    input >> n >> k;

    const int p = int(sqrt(k))+1;
    int licznik = 0;
    for(int i = 1; i <= k; i++){
        licznik++;
        input >> symbol[i];
        if(symbol[i] != '?'){
            int a,b;
            input >> a >> b;
            if(a > b) swap(a,b);

            if(symbol[i] == '+'){
                g[a].push_back(i);
                g[b].push_back(i);
            }

            edges[i] = {a,b};
            ind[i] = i;
            if(symbol[i] == '+')
                m[{a,b}] = i;
            else
                ind[i] = m[{a,b}];
        }
        if(licznik == p){
            algo(n,i-p+1,p);
            licznik = 0;
        }
    }

    if(licznik > 0) algo(n,k-licznik+1,licznik);

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
