#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 3e5+7;

vector<pi> g[max_n]; //first - v, second - k
vector<pi> tree[max_n]; //synowie w drzewie
pi krawedzie[max_n];

bool art[max_n];
bool most[max_n];

bool odw[max_n];
int pre[max_n];
int low[max_n]; //wartosc pre
int anc[max_n];

int rep[max_n];
bool zawiera_art[max_n];
bool odw_ans[max_n];

int fajnd(int v){
    if(rep[v] == v) return v;
    rep[v] = fajnd(rep[v]);
    return rep[v];
}

void onion(int a, int b){
    a = fajnd(a);
    b = fajnd(b);
    rep[b] = a;
}

int ind = 1;
void dfs(int v){
    odw[v] = 1;
    pre[v] = ind++;
    for(auto x:g[v]){
        if(!odw[x.first]){
            tree[v].push_back(x);
            anc[x.first] = v;
            dfs(x.first); 
        }
    }
}   

void set_low(int v, int prev, int k){
    for(auto x:tree[v]) set_low(x.first,v,x.second);

    low[v] = pre[v];
    for(auto x:g[v]){
        int u = x.first;
        if(u == anc[v]) continue;
        if(pre[u] > pre[v]) low[v] = min(low[v],low[u]);
        else low[v] = min(low[v],pre[u]);
    }

    if(low[v] == pre[v]) most[k] = 1;
}

void set_fu(int v){
    for(auto x:g[v]){
        if(most[x.second] || fajnd(v) == fajnd(x.first)) continue;
        onion(v,x.first);
        set_fu(x.first); 
    }
}

bool ans = 0;
void dfs_ans(int v, int target, bool cur){
    odw_ans[v] = 1;
    if(zawiera_art[fajnd(v)]) cur = 1;
    if(v == target){
        ans = cur;
        return;
    }
    for(auto x:g[v]){
        if(odw_ans[x.first]) continue;
        if(art[x.second]) dfs_ans(x.first,target,1);
        else dfs_ans(x.first,target,cur);
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        g[a].push_back({b,i});
        g[b].push_back({a,i});
        krawedzie[i] = {a,b};
        if(c == 1) art[i] = 1;
    }

    for(int i = 1; i <= n; i++) rep[i] = i;

    //drzewo   
    dfs(1);
    set_low(1,0,0);

    
    for(int i = 1; i <= n; i++){
        if(fajnd(i) == i) set_fu(i);
    }

    
    for(int i =1; i <= m; i++){
        if(art[i]){
            int a = krawedzie[i].first;
            int b = krawedzie[i].second;
            if(fajnd(a) == fajnd(b)) zawiera_art[fajnd(a)] = 1;
        }
    }
    
    int start,end;
    cin >> start >> end;

    dfs_ans(start,end,0);
    if(ans) cout << "YES\n";
    else cout << "NO\n";
    
    
    

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
