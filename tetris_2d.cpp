#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 1e6+7;
const int max_sqrt = 1007;
int arr[max_n];
int pelne[max_n];
int niepelne[max_n];

int blok(int x){
    return x/max_sqrt;
}

int query(int x, int y){

    int b1 = blok(x);
    int b2 = blok(y);   
    int ans = max(pelne[b1],pelne[b2]);

    if(b1 == b2){
        for(int i = x; i <= y; i++)
            ans = max(ans,arr[i]);
        return ans;
    }

    while(blok(x) == b1){
        ans = max(ans,arr[x]);
        x++;
    }
    while(blok(x) == b2){
        ans = max(ans,arr[y]);
        y--;
    }
    for(int i = b1+1; i < b2; i++){
        int p = max(pelne[i],niepelne[i]);
        ans = max(ans,p);
    }

    return ans;
}

void update(int x, int y, int val){
    int b1 = blok(x);
    int b2 = blok(y);

    niepelne[b1] = max(niepelne[b1],val);
    niepelne[b2] = max(niepelne[b2],val);

    if(b1 == b2){
        for(int i = x; i <= y; i++)
            arr[i] = max(arr[i],val);
        return;
    }

    while(blok(x) == b1){
        arr[x] = max(arr[x],val);
        x++;
    }
    while(blok(x) == b2){
        arr[y] = max(arr[y],val);
        y--;
    }
    for(int i = b1+1; i < b2; i++)
        pelne[i] = max(pelne[i],val);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,q;
    cin >> n >> q;

    for(int i = 1; i <= q; i++){

        int l,a;
        cin >> l >> a;

        int b = a+l-1;
        //if(b > n) b = n;

        int h = query(a,b)+1;
        update(a,b,h);

    }

    int ans = 0;
    for(int i = 0; i <= n; i++){
        ans = max(ans,arr[i]);
        ans = max(ans,pelne[blok(i)]);
        ans = max(ans,niepelne[blok(i)]);
    }
    cout << ans << '\n';

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
