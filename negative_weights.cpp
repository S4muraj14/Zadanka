#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1007;
const int INF = 1e9;

vector<pi> g[max_n];
int dist[max_n];
bool m_inf[max_n]; // ta sama tablica odwiedzone
queue<int> q;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    while(1){
        
        int n,m,t,s;
        cin >> n >> m >> t >> s;

        if(n == 0) break;

        for(int i = 1; i <= m; i++){
            int a,b,c;
            cin >> a >> b >> c;
            g[a].push_back({b,c});
        }

        for(int i = 0; i < n; i++) dist[i] = INF;
        dist[s] = 0;

        for(int i = 1; i <= n-1; i++){
            for(int v = 0; v < n; v++){
                for(auto k:g[v])
                    if(dist[v] != INF) dist[k.first] = min(dist[k.first],dist[v]+k.second);   
            }
        }

        //sprawdzic czy jest ujemny cykl
        for(int v = 0; v <= n-1; v++){
            for(auto k:g[v]){
                if(dist[v]+k.second < dist[k.first] && dist[v] != INF) q.push(k.first);
            }
        }

        //bfs oznaczyc -inf
        while(!q.empty()){
            int v = q.front();
            q.pop();

            if(m_inf[v]) continue;
            m_inf[v] = 1;

            for(auto x:g[v]) if(!m_inf[x.first]) q.push(x.first);
        }

        while(t--){
            int x;
            cin >> x;
            if(m_inf[x]) cout << "-Infinity\n";
            else if(dist[x] == INF) cout << "Impossible\n";
            else cout << dist[x] << '\n';
        }
        cout << '\n';

        for(int i = 0; i < n; i++){
            g[i].clear();
            m_inf[i] = 0;
            dist[i] = INF;
        }
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
