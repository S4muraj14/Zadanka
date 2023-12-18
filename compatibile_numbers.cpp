#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int base = 22;
int arr[1<<base];
int rep[1<<base];

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        int mask = 0;
        for(int j = 0; j < base; j++)
            if(!(arr[i]&(1<<j))) mask += 1<<j;
        rep[mask] = arr[i];
    }

    for(int i = (1<<base)-1; i >= 0; i--){
        if(!rep[i]) continue;
        for(int j = 0; j < base; j++)
            if(i&(1<<j)) rep[i-(1<<j)] = rep[i];
    }

    for(int i = 1; i <= n; i++){
        int mask = 0;
        if(arr[i] == 0){
            if(i == 1) cout << arr[2] << ' ';
            else cout << arr[1] << ' ';
            continue;
        }
        if(rep[arr[i]]) cout << rep[arr[i]] << ' ';
        else cout << -1 << ' ';
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
