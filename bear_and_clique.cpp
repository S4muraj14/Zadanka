#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e5+7;
const ll INF = 1e18+7;

vector<pl> g[max_n];
bool odw[max_n];
ll dist[max_n];
priority_queue<pl> q;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    for(ll i=1; i < max_n; i++)
        dist[i] = INF;

    ll t;
    cin >> t;
    while(t--){

        ll n,k,x,m,start;
        cin >> n >> k >> x >> m >> start;

        ll vir = n+1;
        for(ll i = 1; i <= k; i++){
            g[i].push_back({vir,x});
            g[vir].push_back({i,0LL});
        }

        for(ll i = 1; i <= m; i++){
            ll a,b,c;
            cin >> a >> b >> c;
            g[a].push_back({b,c});
            g[b].push_back({a,c});
        }

        dist[start] = 0LL;

        //for(ll i = 1; i <= n; i++){
        //    cout << "i: " << i << " dist: " << dist[i] << " odw: " << odw[i] << '\n';
        //}

        q.push({0LL,start});
        while(!q.empty()){
            ll v = q.top().second;
            q.pop();

            if(odw[v]) continue;
            odw[v] = 1;

            for(auto x:g[v]){
                if(dist[v]+x.second < dist[x.first]){
                    dist[x.first] = dist[v]+x.second;
                    q.push({-dist[x.first],x.first});
                }
            }
        }

        for(ll i = 1 ; i <= n; i++) cout << dist[i] << ' ';
        cout << '\n';

        for(ll i=1; i <= n+1; i++){
            odw[i] = 0;
            dist[i] = INF;
            g[i].clear();
        }
        

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
