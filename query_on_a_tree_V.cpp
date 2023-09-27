#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e5+7;
const int base = 16;
const int INF = 1e9;

vi g[max_n];
bool off[max_n];
int sajz[max_n];
int anc[max_n][base];
int h[max_n];

bool ozn[max_n];
multiset<int> c_val[max_n];
int c_prev[max_n];

void set_lca(int v, int prev){
    h[v] = h[prev]+1;

    anc[v][0] = prev;
    for(int i = 1; i < base; i++)
        anc[v][i] = anc[anc[v][i-1]][i-1];
    
    for(auto x:g[v]) if(x != prev) set_lca(x,v);
}

int get_lca(int a, int b){
    if(h[a] > h[b]) swap(a,b);

    for(int i = base-1; i >= 0; i--)
        if(h[anc[b][i]] >= h[a]) b = anc[b][i];
    
    if(a == b) return a;

    for(int i = base-1; i >= 0; i--){
        if(anc[a][i] != anc[b][i]){
            a = anc[a][i];
            b = anc[b][i];
        }
    }

    return anc[a][0];
}

int get_dist(int a, int b){
    int p = get_lca(a,b);
    return h[a]+h[b]-2*h[p];
}

void size_dfs(int v, int prev){
    sajz[v] = 1;
    for(auto x : g[v]){
        if(x == prev || off[x]) continue;
        size_dfs(x,v);
        sajz[v] += sajz[x];
    }
}

int find_centroid(int v, int prev, int tree_size, int prev_cent){
    for(auto x : g[v]){
        if(off[x] || x == prev) continue;
        if(sajz[x] > tree_size/2) return find_centroid(x,v,tree_size,prev_cent);
    }
    c_prev[v] = prev_cent;
    return v;
}

void centroid_decomposition(int v, int prev_cent){
    size_dfs(v,0);
    int centr = find_centroid(v,0,sajz[v],prev_cent);

    off[centr] = true;

    for(auto x : g[centr]){
        if(off[x]) continue;
        centroid_decomposition(x,centr);
    }

}

void add(int v, int start, bool f){
    if(v == 0) return;

    int dist = get_dist(v,start);

    if(f) c_val[v].insert(dist);
    else{
        auto it = c_val[v].find(dist);
        c_val[v].erase(it);
    }

    add(c_prev[v], start, f);
}

int query(int v, int start, int ans){
    if(v == 0) return ans;

    int dist = get_dist(v,start);
    if(!c_val[v].empty()){
        int x = *c_val[v].upper_bound(-1);
        ans = min(ans,dist+x);
    }

    return query(c_prev[v], start, ans);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for(int i=1 ;i < n ;i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    centroid_decomposition(1,0);
    set_lca(1,0);

    int q;
    cin >> q;

    while(q--){
        int z,v;
        cin >> z >> v;
        if(z == 0){
            add(v,v,!ozn[v]);
            ozn[v] = !ozn[v];
        }
        else{
            int ans = query(v,v,INF);
            if(ans == INF) cout << "-1\n";
            else cout << ans << '\n';
        }
    }

  return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
