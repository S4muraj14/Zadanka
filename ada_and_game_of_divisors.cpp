#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 2e7;
int sito[max_n+7];
bool dp[max_n+7];

int count(int x){
    int last = 0;
    int ile = 0;
    int ans = 1;
    while(x > 1){
        if(sito[x] == last) ile++;
        else{
            ans *= ile+1;
            last = sito[x];
            ile = 1;
        }
        x /= sito[x];
    }
    ans *= ile+1;
    return ans;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int i = 2; i <= max_n; i++){
        if(!sito[i]){
            for(int j = i; j <= max_n; j += i)
                sito[j] = i;
        }
    }

    dp[1] = 1;
    int last_p = 0;
    for(int i = 2; i <= max_n; i++){
        if(i-count(i) <= last_p)
            dp[i] = 1;
        else{
            dp[i] = 0;
            last_p = i;
        }
        
    }

    //for(int i = 0; i <= 50; i++){
    //    cout << "i: " << i << " sito: " << sito[i] << " dp[i]: " << dp[i] << '\n';
    //}

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(dp[n]) cout << "Ada\n";
        else cout << "Vinit\n";
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
