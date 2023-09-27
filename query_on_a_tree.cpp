#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e4+7;
const int base = 1<<14;

vector<pi> g[max_n];
pi m[max_n];

int h[max_n];
int anc[max_n];
int sajz[max_n];

int pre[max_n];
int head[max_n];

int tree[base*2];

void update_tree(int v, int val){
    v += base;
    tree[v] = val;
    v /= 2;
    while(v){
        tree[v] = max(tree[v*2],tree[v*2+1]);
        v /= 2;
    }
}

int query_tree(int a, int b){
    a += base-1;
    b += base+1;
    int ans = 0;
    while(a/2 != b/2){
        if(a%2 == 0) ans = max(ans,tree[a+1]);
        if(b%2 == 1) ans = max(ans,tree[b-1]);
        a /= 2; b /= 2;
    }
    return ans;
}

void dfs_init(int v, int prev){
    h[v] = h[prev]+1;
    anc[v] = prev;
    sajz[v] = 1;

    for(auto x:g[v]){
        if(x.first != prev){
            dfs_init(x.first,v);
            sajz[v] += sajz[x.first];
        }
    }
}

int p = 1;
void dfs_hld(int v, int prev, int start, int k){
    pre[v] = p++;
    head[v] = start;
    anc[v] = prev;
    update_tree(pre[v],k);

    int m = 0;
    int ind = 0;
    int k_ind = 0;
    for(auto x:g[v]){
        if(x.first == prev) continue;
        if(sajz[x.first] > m){
            ind = x.first;
            k_ind = x.second;
            m = sajz[x.first];
        }
    }

    //przedłużamy ścieżkę
    if(ind != 0) dfs_hld(ind,v,start,k_ind);

    for(auto x:g[v]){
        if(x.first == prev || x.first == ind) continue;
        dfs_hld(x.first,v,x.first,x.second);
    }
}

int query_hld(int a, int b){
    int ans = 0;

    while(head[a] != head[b]){
        //b zawsze nizej w drzewie
        if(h[head[a]] > h[head[b]]) swap(a,b);
        //sciezka do head plus krawedz do kolejnej sciezki
        ans = max(ans,query_tree(pre[head[b]],pre[b]));
        b = anc[head[b]];
    }

    if(a == b) return ans;

    if(h[a] > h[b]) swap(a,b);
    ans = max(ans,query_tree(pre[a]+1,pre[b]));

    return ans;
}

void change_input(int a, int b, int val){
    if(h[a] > h[b]) swap(a,b);
    update_tree(pre[b],val);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){

        int n;
        cin >> n;

        //cout << "t: " << t << " n: " << n << '\n';
        
        for(int i = 1; i < n; i++){
            int a,b,c;
            cin >> a >> b >> c;
            g[a].push_back({b,c});
            g[b].push_back({a,c});
            m[i] = {a,b};
        }

        dfs_init(1,0);
        dfs_hld(1,0,1,0);

        
        //for(int i = 1; i <= n; i++){
        //    cout << "i: " << i << " h: " << h[i] << " anc: " << anc[i] << " sajz: " << sajz[i]
        //         << " preorder: " << pre[i] << " head: " << head[i] << '\n';
        //}
        
        while(1){
            string s;
            cin >> s;

            if(s == "QUERY"){
                int a,b;
                cin >> a >> b;
                cout << query_hld(a,b) << '\n';
            }
            else if(s == "CHANGE"){
                int v,val;
                cin >> v >> val;
                change_input(m[v].first,m[v].second,val);
            }

            else break;
        }

        //clear
        p = 1;
        for(int i = 1; i <= n; i++){
            g[i].clear();
        }

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
