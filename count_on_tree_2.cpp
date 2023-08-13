#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

struct query{
    int l;
    int r;
    int ind;
    int lca;
};

const int max_n = 4e4+7;
const int max_m = 1e5+7;
const int m_sqrt = 207;
const int base = 16;

int ans = 0;

pi pierwsze_wejscie[max_n];

int arr[max_n];
vi g[max_n];
int h[max_n];
int lca[max_n][base];

int lista[max_n*2];
pi indeksy[max_n];

int odpowiedzi[max_m];
query zapytania[max_m];

int ile_liczb[max_n]; //skompresowac pewnie trzeba
int ile_v[max_n];

int ind = 1;
void setup(int i, int prev){
    lca[i][0] = prev;
    for(int j = 1; j < base; j++)
        lca[i][j] = lca[lca[i][j-1]][j-1];

    lista[ind] = i;
    indeksy[i].first = ind;
    ind++;

    h[i] = h[prev]+1;
    for(auto x:g[i]) if(x != prev) setup(x,i);

    lista[ind] = i;
    indeksy[i].second = ind;
    ind++;
}

int get_lca(int a, int b){
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

int blok(int a){
    return a/m_sqrt;
}

bool comp(query& a, query& b){
    if(blok(a.l) == blok(b.l)){
        return a.r < b.r;
    }
    return blok(a.l) < blok(b.l);
}

void add(int v){
    ile_v[v]++;
    if(ile_v[v] == 1){
        ile_liczb[arr[v]]++;
        if(ile_liczb[arr[v]] == 1) ans++;
    }
    if(ile_v[v] == 2){
        ile_liczb[arr[v]]--;
        if(ile_liczb[arr[v]] == 0) ans--;
    }
}

void remove(int v){
    ile_v[v]--;
    if(ile_v[v] == 1){
        ile_liczb[arr[v]]++;
        if(ile_liczb[arr[v]] == 1) ans++;
    }
    if(ile_v[v] == 0){
        ile_liczb[arr[v]]--;
        if(ile_liczb[arr[v]] == 0) ans--;
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        pierwsze_wejscie[i] = {x,i};
    }

    sort(pierwsze_wejscie+1,pierwsze_wejscie+1+n);
    int skal = 0;
    for(int i = 1;i <= n; i++){
        if(pierwsze_wejscie[i].first > pierwsze_wejscie[i-1].first) skal++;
        arr[pierwsze_wejscie[i].second] = skal;
    }

    for(int i = 1; i < n; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    setup(1,0);

    for(int i = 1; i <= m; i++){
        int a,b;
        cin >> a >> b;
        int p = get_lca(a,b);
        //lca to ktores z wierzcholkow
        if(p == a){
            zapytania[i] = {indeksy[a].first, indeksy[b].first, i, 0};
        }
        else if(p == b){
            zapytania[i] = {indeksy[b].first, indeksy[a].first, i, 0};
        }
        else{
            //z jednego wierzcholka wartosc jak wychodzimy, z drugiego jak wchodzimy
            query x;
            if(indeksy[a].first < indeksy[b].first){
                x.l = indeksy[a].second;
                x.r = indeksy[b].first;
            }
            else{
                x.l = indeksy[b].second;
                x.r = indeksy[a].first;
            }
            x.ind = i;
            x.lca = p;
            zapytania[i] = x;
        }
    }

    sort(zapytania+1,zapytania+1+m, comp);


    int l = 0;
    int r = 0;

    for(int i = 1; i <= m; i++){
        query akt = zapytania[i];

        if(akt.l < l)
            for(int i = l-1; i >= akt.l; i--)
                add(lista[i]);
            
        else
            for(int i = l; i < akt.l; i++)
                remove(lista[i]);
            
        if(akt.r > r)
            for(int i = r+1; i <= akt.r; i++)
                add(lista[i]);
            
        
        else
            for(int i = r; i > akt.r; i--)
                remove(lista[i]);
            
        l = akt.l;
        r = akt.r;

        if(akt.lca != 0){   
            if(ile_liczb[arr[akt.lca]] == 0) odpowiedzi[akt.ind] = ans+1;
            else odpowiedzi[akt.ind] = ans;
        }
        else 
            odpowiedzi[akt.ind] = ans;
    }

    for(int i = 1; i <= m; i++) cout << odpowiedzi[i] << '\n';

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
