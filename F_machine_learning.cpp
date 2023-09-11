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
    int ile_z;
    int ind;
};

int sqrt3 = 0;
int sqrt2 = 0;
const int max_n = 2e5+7;

map<int,int> m;
int arr[max_n];

query zapytania[max_n];
pi zmiany[max_n];
pi prev_zmiany[max_n];
int ile[max_n];//ile dla kazdej liczby
int meks[max_n];//wszystkie mozliwe wartosci meks

int ans[max_n];

int blok(int a){
    return a/sqrt3;
}

bool comp(query a, query b){
    if(blok(a.l) == blok(a.l)){
        if(blok(a.r) == blok(b.r))
            return a.ind < b.ind;
        else 
            return blok(a.r) < blok(b.r);
    }
    else 
        return blok(a.l) < blok(b.l);
}

int pierwiastek(ll n){
    n *= n;
    ll ans = 0;
    ll l = 0, r = 1e4+7;

    while(l <= r){
        ll s = (l+r+1)/2;
        if(s*s*s > n) r = s-1;
        else{
            l = s+1;
            ans = s;
        }
    }

    return ans;
}

void add(int x){
    meks[ile[x]]--;
    ile[x]++;
    meks[ile[x]]++;
}
void remove(int x){
    meks[ile[x]]--;
    ile[x]--;
    meks[ile[x]]++;
}

void change(pi x, int l, int r){
    int ind = x.first;
    int val = x.second;

    if(ind >= l && ind <= r){
        add(val);
        remove(arr[ind]);
    }
    arr[ind] = val;
}

int find_mex(){
    for(int i = 1; i <= sqrt2+7; i++){
        if(!meks[i]) return i;
    }
    return -1;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,q;
    cin >> n >> q;

    sqrt3 = 2*pierwiastek(n);
    sqrt2 = 2*int(sqrt(n))+7;

    int ile = 1;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        if(!m[x]) m[x] = ile++;
        arr[i] = m[x];
    }

    int ile_przed = 0;
    int ile_query = 1;
    for(int i = 1; i <= q; i++){
        int c,a,b;
        cin >> c >> a >> b;
        if(c == 1)
            zapytania[ile_query++] = {a,b,ile_przed,ile_query-1};
        else{
            if(!m[b]) m[b] = ile++;
            zmiany[++ile_przed] = {a,m[b]};
        }
    }

    sort(zapytania+1,zapytania+ile_query,comp);

    zapytania[0] = {0,0,0,0};

    int l = 0;
    int r = 0;
    for(int i = 1; i < ile_query; i++){
        int akt_l = zapytania[i].l;
        int akt_r = zapytania[i].r;
        int ile_z = zapytania[i].ile_z;

        if(ile_z >= zapytania[i-1].ile_z){
            for(int j = zapytania[i-1].ile_z+1; j <= ile_z; j++){
                prev_zmiany[j] = {zmiany[j].first,arr[zmiany[j].first]};
                change(zmiany[j],l,r); 
            } 
        }  
        else{
            for(int j = zapytania[i-1].ile_z; j > ile_z; j--){
                change(prev_zmiany[j],l,r);
            }
        }            
        
        while(l > akt_l){
            l--;
            add(arr[l]);
        }
        while(r < akt_r){
            r++;
            add(arr[r]);
        }
        while(l < akt_l){
            remove(arr[l]);
            l++;
        }
        while(r > akt_r){
            remove(arr[r]);
            r--;
        }   
        
        ans[zapytania[i].ind] = find_mex();
    }


    for(int i = 1; i < ile_query; i++)
        cout << ans[i] << '\n';


    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
