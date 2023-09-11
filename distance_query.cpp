#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e5+7;
const int base = 16;
vector<pi> g[max_n];
int h[max_n];
int anc[max_n][base];
int most[max_n][base];
int least[max_n][base];

void policz(int i, int prev, int k){
    h[i] = h[prev]+1;

    anc[i][0] = prev;
    most[i][0] = k;
    least[i][0] = k;
    for(int r = 1; r < base; r++){
        anc[i][r] = anc[anc[i][r-1]][r-1];
        most[i][r] = max(most[i][r-1],most[anc[i][r-1]][r-1]);
        least[i][r] = min(least[i][r-1],least[anc[i][r-1]][r-1]);
    }
    for(auto x : g[i]) if(x.first != prev) policz(x.first,i,x.second);
}

pi get_ans(int a, int b){
    int ans_ma = 0;
    int ans_mi = 1e9;
    if(h[a] > h[b]) swap(a,b);

    for(int r = base-1; r >= 0; r--){
        if(h[anc[b][r]] >= h[a]){
            ans_ma = max(ans_ma,most[b][r]);
            ans_mi = min(ans_mi,least[b][r]);
            b = anc[b][r];
        }
    }

    if(a == b) return{ans_mi,ans_ma};

    for(int r = base-1; r >= 0; r--){
        if(anc[a][r] != anc[b][r]){
            ans_ma = max(ans_ma,most[a][r]);
            ans_ma = max(ans_ma,most[b][r]);
            ans_mi = min(ans_mi,least[a][r]);
            ans_mi = min(ans_mi,least[b][r]);
            a = anc[a][r];
            b = anc[b][r];
        }
    }

    ans_ma = max(ans_ma,most[a][0]);
    ans_ma = max(ans_ma,most[b][0]);
    ans_mi = min(ans_mi,least[a][0]);
    ans_mi = min(ans_mi,least[b][0]);

    return{ans_mi,ans_ma};
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for(int i = 1; i < n; i++){
        int a,b,c;
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }

    policz(1,0,0);

    int q;
    cin >> q;
    while(q--){
        int a,b;
        cin >> a >> b;
        pi x = get_ans(a,b);
        cout << x.first << ' ' << x.second << '\n';
    }



    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
