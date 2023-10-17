#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 50;
const int max_m = 5000;
const int INF = 1e9;

struct edge{
    int a;
    int b;
    int cap;
    int flow;
};

vi g[max_n];
edge k[max_m];
int ile_kart[15][30];
int layer[max_n];
int ptr[max_n];
queue<int> q;

int ile_edge = 0;
void create_edge(int a, int b, int cap){
    k[ile_edge] = {a,b,cap,0};
    k[ile_edge+1] = {b,a,0,0};
    g[a].push_back(ile_edge);
    g[b].push_back(ile_edge+1);
    ile_edge += 2;
}
void update(int ind, int val){
    k[ind].flow += val;
    k[ind^1].flow -= val;
}

bool bfs(int start,int end){
    layer[start] = 0;
    bool ans = false;
    q.push(start);

    while(!q.empty()){
        int ind = q.front();
        q.pop();
        for(auto x:g[ind]){
            int b = k[x].b;
            if(layer[b] != -1 || k[x].flow == k[x].cap) continue;
            layer[b] = layer[ind]+1;
            q.push(b);
            if(b == end) ans = true;
        }
    }
    return ans;
}

int dfs(int v, int end, int akt_flow){
    if(v == end) return akt_flow;
    for(int i = ptr[v]; i < g[v].size(); i++){
        edge x = k[g[v][i]];
        ptr[v]++;
        if(layer[x.b] != layer[v]+1) continue;

        int max_flow = min(akt_flow,x.cap-x.flow);
        if(max_flow <= 0) continue;

        int val = dfs(x.b,end,max_flow);
        if(val > 0){
            update(g[v][i],val);
            ptr[v]--;
            return val;
        }
    }
    return 0;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for(int z = 1; z <= t; z++){

        int n,m;
        cin >> n >> m;

        int start = n+m;
        int end = n+m+1;

        for(int i = 1; i <= n; i++){
            int ile;
            cin >> ile;
            for(int j = 1; j <= ile; j++){
                int x;
                cin >> x;
                ile_kart[i][x]++;
            }
        }

        //stworzyc zrodlo i ujscie
        for(int i = 1; i <= m; i++){
            create_edge(start,i,ile_kart[1][i]);
            create_edge(i,end,1);
        }

        //stworzyc krawedzie
        for(int i = 2; i <= n; i++){ //znajomi
            int ind = i+m-1;
            for(int j = 1; j <= m; j++){ //jaki typ
                if(ile_kart[i][j] == 0)
                    create_edge(j,ind,1);
                else
                    create_edge(ind,j,ile_kart[i][j]-1);
            }
        }

        for(int i = 1; i <= n+m+1; i++) layer[i] = -1;


        //dinic
        int flow = 0;
        //int licznik = 5;
        while(bfs(start,end)){
            while(true){
                int dodaj = dfs(start,end,INF);
                if(dodaj == 0) break;
                flow += dodaj;
            }

            for(int i = 1; i <= n+m+1; i++){
                layer[i] = -1;
                ptr[i] = 0;
            }
        }

        cout << "Case #" << z << ": " << flow << '\n';

        for(int i = 1; i <= n+m+1; i++) g[i].clear();
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++) ile_kart[i][j] = 0;
        }
        for(int i = 0; i < ile_edge; i++){
            k[i].cap = 0;
            k[i].flow = 0;
        }
        ile_edge = 0;

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
