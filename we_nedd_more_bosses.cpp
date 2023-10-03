#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 3e5+7;

vi g[max_n];
vi tree[max_n];

int pre[max_n];
int anc[max_n];
bool odw[max_n];

bool most[max_n];
int low[max_n];

int wynik[max_n];
int lazy[max_n];

int ind = 1;
void dfs(int v){
    odw[v] = 1;
    pre[v] = ind++;
    for(auto x:g[v]){
        if(!odw[x]){
            tree[v].push_back(x);
            anc[x] = v;
            dfs(x); 
        }
    }
}   

void set_low(int v, int prev){
    for(auto x:tree[v]) set_low(x,v);

    low[v] = pre[v];
    for(auto x:g[v]){
        if(x == anc[v]) continue;
        if(pre[x] > pre[v]) low[v] = min(low[v],low[x]);
        else low[v] = min(low[v],pre[x]);
    }

    if(low[v] == pre[v]) most[v] = 1;
}

void dp(int v){
    for(auto x:tree[v]) dp(x);

    int m1 = 0;
    int m2 = 0;
    for(auto x:tree[v]){
        int val = lazy[x];
        if(most[x]) val++;
        if(val > m2){
            if(val > m1){
                m2 = m1;
                m1 = val;
            }
            else m2 = val;
        }
    }

    wynik[v] = m1+m2;
    lazy[v] = m1;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);
    set_low(1,0);
    dp(1);

    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(wynik[i],ans);
    cout << ans << '\n';

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
