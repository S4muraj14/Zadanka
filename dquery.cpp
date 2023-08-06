#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

struct x{
    int l;
    int r;
    int ind;
};

const int max_n = 1e6+7;
const int max_sqrt = 178;
int arr[max_n];
int ile[max_n];
x query[max_n];
int odpowiedzi[max_n];

int blok(int x){
    return x/max_sqrt;
}

bool comp(x& a, x& b){
    if(blok(a.l) == blok(b.l))
        return (a.r < b.r);
    return blok(a.l) < blok(b.l);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) cin >> arr[i];

    int q;
    cin >> q;
    for(int i = 1 ; i <= q; i++){
        int l,r;
        cin >> l >> r;
        query[i] = {l,r,i};
    }

    sort(query+1,query+1+q,comp);

    int l = query[1].l;
    int r = query[1].r;
    int ans = 0;

    for(int i = l; i <= r; i++){
        ile[arr[i]]++;
        if(ile[arr[i]] == 1) ans++;
    }
    odpowiedzi[query[1].ind] = ans;

    //cout << "query: " << query[1].ind << " l: " << l << " r: " << r << " ans: " << ans << '\n';

    for(int t = 2; t <= q; t++){
        x akt = query[t];
        
        if(akt.l < l){
            for(int i = l-1; i >= akt.l; i--){
                ile[arr[i]]++;
                if(ile[arr[i]] == 1) ans++;
            }
        }
        else{
            for(int i = l; i < akt.l; i++){
                ile[arr[i]]--;
                if(ile[arr[i]] == 0) ans--;
            }
        }

        if(akt.r > r){
            for(int i = r+1; i <= akt.r; i++){
                ile[arr[i]]++;
                if(ile[arr[i]] == 1) ans++;
            }
        }
        else{
            for(int i = r; i > akt.r; i--){
                ile[arr[i]]--;
                if(ile[arr[i]] == 0) ans--;
            }
        }
        

        //cout << "query: " << akt.ind << " l: " << akt.l << " r: " << akt.r << " ans: " << ans << '\n';

        odpowiedzi[akt.ind] = ans;
        l = akt.l;
        r = akt.r;
    }

    for(int i = 1; i <= q; i++) cout << odpowiedzi[i] << '\n';

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
