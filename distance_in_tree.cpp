#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 5e4+7;
vi g[max_n];
bool off[max_n];
int sajz[max_n];
//dlugosc sciezki / ilosc
map<int,int> m;

int k;  
int ans = 0;

void size_dfs(int v, int prev){
    sajz[v] = 1;
    for(auto x : g[v]){
        if(x == prev || off[x]) continue;
        size_dfs(x,v);
        sajz[v] += sajz[x];
    }
}

int find_centroid(int v, int prev, int tree_size){
    for(auto x : g[v]){
        if(off[x] || x == prev) continue;
        if(sajz[x] > tree_size/2) return find_centroid(x,v,tree_size);
    }
    return v;
}

void dfs_ans(int v, int prev, int val){
    ans += m[k-val];
    for(auto x : g[v]){
        if(x != prev && !off[x]) dfs_ans(x,v,val+1);
    }
}

void dfs_update(int v, int prev, int val){
    m[val]++;
    for(auto x : g[v]){
        if(x != prev && !off[x]) dfs_update(x,v,val+1);
    }
}

void centroid_decomposition(int v){
    m[0] = 1;

    size_dfs(v,0);
    int centr = find_centroid(v,0,sajz[v]);

    for(auto x : g[centr]){
        if(off[x]) continue;
        dfs_ans(x,centr,1);
        dfs_update(x,centr,1);
    }

    off[centr] = true;
    m.clear();

    for(auto x : g[centr]){
        if(off[x]) continue;
        centroid_decomposition(x);
    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n >> k;

    for(int i=1 ;i < n ;i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if(k == 1) ans = n-1;
    else centroid_decomposition(1);

    cout << ans << '\n';

  return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
