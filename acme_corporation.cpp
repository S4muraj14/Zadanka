#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

struct edge{
    ll a;
    ll b;
    ll cost;
    ll cap;
    ll flow;
};

const ll max_n = 407;
const ll max_m = 9507;
const ll INF = 1e18;

vi g[max_n];
edge k[max_m];

ll cost[max_n];
ll price[max_n];
ll czas[max_n];

ll dist[max_n];
ll pop[max_n];
ll ile_flow[max_n];
bool na_kolejce[max_n];
queue<ll> q;

ll ile_edge = 0;
void create_edge(ll a, ll b, ll cost, ll cap){
    k[ile_edge] = {a,b,cost,cap,0};
    k[ile_edge+1] = {b,a,-cost,0,0};
    g[a].push_back(ile_edge);
    g[b].push_back(ile_edge+1);
    ile_edge += 2;
}

void update(ll ind, ll val){
    k[ind].flow += val;
    k[ind^1].flow -= val;
}

void spfa(ll start, ll end){
    dist[start] = 0;
    q.push(start);
    na_kolejce[start] = true;
    ile_flow[start] = INF;

    while(!q.empty()){ 
        ll v = q.front();
        //cout << "sprawdzamy v: " << v << " akt_koszt(dist): " << dist[v] << '\n';
        q.pop();
        na_kolejce[v] = false;

        for(auto x:g[v]){
            if(k[x].flow == k[x].cap) continue;
            ll b = k[x].b;
            ll nowe = k[x].cost;
            if(dist[b] > dist[v]+nowe){
                //cout << "updatujemy: " << b << '\n';
                ile_flow[b] = min(ile_flow[v],k[x].cap-k[x].flow);
                dist[b] = dist[v]+nowe;
                pop[b] = x;
                if(!na_kolejce[b]){
                    q.push(b);
                    na_kolejce[b] = true;
                }
            }
        }

    }
}

int main(){

    //ios::sync_with_stdio(0);
    //cin.tie(0);

    ll t;
    cin >> t;
    for(ll z = 1; z <= t; z++){

        ll n,store_cost;
        cin >> n >> store_cost;

        //cout << "n: " << n << " store_cost: " << store_cost << '\n';

        ll start = 2*n+1;
        ll end = 2*n+2;
        for(ll i = 1; i <= n; i++){
            ll amount,cap;
            cin >> cost[i] >> amount >> price[i] >> cap >> czas[i];
            //cout << "v: " << i << " cost: " << cost[i] << " amount: " << amount
            //     << " price: " << price[i] << " cap: " << cap << " czas: " << czas[i] << '\n';
            create_edge(start,i,cost[i],amount);
            create_edge(n+i,end,-price[i],cap);
        }

        for(ll i = 1; i <= n; i++){
            for(ll j = i; j <= min(i+czas[i],n); j++){
                ll w = (j-i)*store_cost;
                //cout << "check edge od i: " << i << " j : " << j << " w: " << w << '\n';
                if(w+cost[i] >= price[j]) continue;
                create_edge(i,n+j,w,INF);
            }
        }
        /*
        for(ll i = 0; i < ile_edge; i++){
            cout << "edge nr: " << i << " a: " << k[i].a << " b: " << k[i].b
                 << " cost: " << k[i].cost << " cap: " << k[i].cap << '\n';
        }
        */

        for(ll i = 1; i <= n*2+2; i++) dist[i] = INF;
    

        //algorytm, szukamy najwiekszego zysku
        //wrzucic ll
        spfa(start,end);
        ll ans = 0;
        while(dist[end] != INF){
            
            if(dist[end] >= 0) break;
            //cout << "dist(suma kosztow): " << dist[end] << " flow: " << ile_flow[end] << '\n';
            ll flow = ile_flow[end];
            ll akt = pop[end];
            ans += -dist[end]*flow;
            //powinna dzialac taka kolejnosc
            while(true){
                update(akt,flow);
                if(k[akt].a == start) break;
                akt = pop[k[akt].a];
            }

            for(ll i = 1; i <= n*2+2; i++){
                dist[i] = INF;
                ile_flow[i] = 0;
                pop[i] = 0;
            }

            spfa(start,end);

        }

        cout << "Case " << z << ": " << ans << '\n';

        for(ll i = 1; i <= n*2+2; i++) g[i].clear();
        ile_edge = 0;
        //if(z == 77) break; //usunac

    }

    

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
