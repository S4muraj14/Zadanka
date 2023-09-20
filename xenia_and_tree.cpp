#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int m_sqrt = 320;
const int max_n = 1e5+7;
const int base = 20;

vi g[max_n];
vi akt;
bool odwiedzone[max_n];

int h[max_n];
int lca[max_n][base];
int dist[max_n];

queue<pi> q;

void set_lca(int i, int prev){
    h[i] = h[prev]+1;
    dist[i] = h[i]-1;

    lca[i][0] = prev;
    for(int k = 1; k < base; k++)
        lca[i][k] = lca[lca[i][k-1]][k-1];

    for(auto x:g[i]) if(x != prev) set_lca(x,i);
}

int find_lca(int a, int b){ 
    if(h[a] > h[b]) swap(a,b);
    
    for(int i = base-1; i >= 0; i--)
        if(h[lca[b][i]] >= h[a]) b = lca[b][i];
    if(a == b) return a;
    
    
    for(int i = base-1; i >= 0; i--){
        if(lca[a][i] != lca[b][i]){
            a = lca[a][i];
            b = lca[b][i];
        }
    }
    return lca[a][0];
}

int get_dist(int a, int b){
    int p = find_lca(a,b);
    return (h[a]+h[b] - 2*h[p]);
}

void bfs(int n){
    for(auto i:akt){
        q.push({i,0});
        dist[i] = 0;
    }

    while(!q.empty()){
        pi x = q.front();
        int i = x.first;
        int prev = x.second;
        q.pop();

        if(odwiedzone[i]) continue;

        odwiedzone[i] = 1;
        dist[i] = min(dist[i],dist[prev]+1);
        for(auto v:g[i]) if(v != prev && !odwiedzone[v]) q.push({v,i});     
    }
    for(int i = 1; i <= n; i++) odwiedzone[i] = 0;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,q;
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    set_lca(1,0);

    while(q--){

        int z,a;
        cin >> z >> a;

        if(z == 1){
            akt.push_back(a);
            if(akt.size() > m_sqrt){
                bfs(n);
                akt.clear();
            }
        }
        else{
            int ans = dist[a];
            for(auto x:akt)
                ans = min(ans,get_dist(a,x));
            cout << ans << '\n';
        }

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
