#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

struct edge{
    int a;
    int b;
    int cap;
    int flow;
};

const int max_n = 35;
const int INF = 1e9;

int w[max_n];
int max_points[max_n];

edge v[max_n*max_n];
vi g[max_n];
vi poprawne;

int odw[max_n];

void update(int ind, int val){
    v[ind].flow += val;
    v[ind^1].flow -= val;
}

int powt = 1;
int dfs(int i, int x, int end, int akt_flow){
    //ignorujemy x
    odw[i] = powt;
    if(i == end) return akt_flow;
    for(auto a:g[i]){
        if(v[a].b == x || odw[v[a].b] == powt) continue;
        int max_flow = min(akt_flow,v[a].cap-v[a].flow);
        if(max_flow <= 0) continue;
        int val = dfs(v[a].b,x,end,max_flow);
        if(val > 0){
            update(a,val);
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
    while(t--){

        int n;
        cin >> n;

        for(int i =1 ; i <= n; i++){
            int win,d;
            cin >> win >> d;
            w[i] = win;
            max_points[i] += w[i];
        }

        int ile_edge = 0;
        int ile_meczy = 0;
        int start = n+1;
        int end = n+2;
        for(int i =1 ; i <= n; i++){
            for(int j = 1; j <= n; j++){
                int cap;
                cin >> cap;
                //bez duplikatow
                if(cap == 0 || i >= j) continue;

                max_points[i] += cap;
                max_points[j] += cap;
                ile_meczy += cap;

                v[ile_edge] = {i,j,cap,0};
                g[i].push_back(ile_edge);

                v[ile_edge+1] = {j,i,0,0};
                g[j].push_back(ile_edge+1);

                ile_edge += 2;
            }
        }

        //tworzymy zrodlo
        for(int i = 1; i <= n; i++){
            v[ile_edge] = {start,i,0,0};
            g[start].push_back(ile_edge);

            v[ile_edge+1] = {i,start,0,0};
            g[i].push_back(ile_edge+1);

            ile_edge += 2;
        }
        //tworzymy ujscie
        for(int i = 1; i <= n; i++){
            v[ile_edge] = {i,end,0,0};
            g[i].push_back(ile_edge);

            v[ile_edge+1] = {end,i,0,0};
            g[end].push_back(ile_edge+1);

            ile_edge += 2;
        }

        //kazdy team
        for(int i = 1; i <= n; i++){
            bool ans = true;

            for(int j = 1; j <= n; j++){
                if(i == j) continue;
                int k = max_points[i]-w[j];
                if(k < 0){
                    ans = false;
                    break;
                }
                int ind = ile_edge-n*2;
                ind += (j-1)*2;
                v[ind].cap = k;
            }

            if(ans){
                //ustawiamy zrodlo
                for(int j = 0; j < ile_edge; j++){
                    if(v[j].b == end || v[j].a == start) continue;
                    if(v[j].a == i || v[j].b == i) continue;
                    int u = v[j].a;
                    int ind = ile_edge-n*4;
                    ind += (u-1)*2; 
                    v[ind].cap += v[j].cap;
                }

                int ile = 0;
                while(true){
                    powt++;
                    int val = dfs(start,i,end,INF);
                    if(val == 0) break;
                    ile += val;
                }
                if(ile >= ile_meczy-max_points[i]+w[i]) poprawne.push_back(i);

                for(int j = 0; j < ile_edge; j++) v[j].flow = 0;
                for(int j = ile_edge-n*4; j < ile_edge-n*2; j++) v[j].cap = 0;
            }
            
        }
        
        if(poprawne.size() > 0){
            for(int i = 0; i < poprawne.size(); i++){
                cout << poprawne[i];
                if(i != poprawne.size()-1) cout << ' ';
            }
        }
        cout << '\n';

        powt = 1;
        for(int i =1 ; i<= n+2; i++){
            g[i].clear();
            max_points[i] = 0;
            w[i] = 0;
            odw[i] = 0;
        }
        poprawne.clear();

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
