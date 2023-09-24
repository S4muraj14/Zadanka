#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1007;
const int max_c = 107;
const int INF = 1e9+7;

vector<pi> g[max_n];
int price[max_n];
int dp[max_n][max_c];
bool odw[max_n][max_c];

priority_queue<pi> q; //first - dist, second - {v,c} v*(c+1)+c

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    for(int i = 0; i < n; i++) cin >> price[i];
    for(int i = 1; i <= m; i++){
        int a,b,d;
        cin >> a >> b >> d;
        g[a].push_back({b,d});
        g[b].push_back({a,d});
    }

    int t;
    cin >> t;
    while(t--){

        int c,start,end;
        cin >> c >> start >> end;

        //dp od [0..c]

        for(int i = 0; i < n; i++){
            for(int j = 0; j <= c; j++){
                dp[i][j] = INF;
                odw[i][j] = 0;
            }
        }

        q.push({0,start*(c+1)});
        while(!q.empty()){
            int cost = -q.top().first;
            int v = q.top().second/(c+1);
            int fuel = q.top().second%(c+1);
            q.pop();

            if(odw[v][fuel]) continue;

            odw[v][fuel] = 1;
            dp[v][fuel] = cost;

            //cout << "v: " << v << " fuel: " << fuel << " cost: " << cost << '\n'; 

            if(fuel+1 <= c){
                if(cost+price[v] < dp[v][fuel+1])
                    q.push({-(cost+price[v]),v*(c+1)+fuel+1});
            }

            for(auto x:g[v]){
                int u = x.first;
                int k = fuel-x.second;
                if(k >= 0){
                    if(dp[v][fuel] < dp[u][k])
                        q.push({-cost,u*(c+1)+k});
                }
            }
        }

        int ans = INF;
        for(int i = 0; i <= c; i++) ans = min(ans,dp[end][i]);

        if(ans == INF) cout << "impossible\n";
        else cout << ans << '\n';
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
