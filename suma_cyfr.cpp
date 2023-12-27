#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 207; 
const ll INF = 1e18;

ll dp[max_n][max_n][max_n]; //i,sum,mult
ll ten[max_n];

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int s,m,q;
    cin >> s >> m >> q;

    ten[0] = 1;
    for(int i = 1; i <= 200; i++)
        ten[i] = (ten[i-1]*10)%m;

    dp[0][0][0] = 1;
    ll last_i = -1;
    bool end = false;
    for(int i = 1; i <= 200; i++){
        for(int suma = 0; suma <= s; suma++){
            for(int mult = 0; mult < m; mult++){
                for(int k = 0; k <= 9; k++){
                    if(k > suma) continue;
                    ll akt = (k*ten[i-1])%m;
                    ll prev = (mult-akt+m)%m;
                    dp[i][suma][mult] += dp[i-1][suma-k][prev];
                    if(suma == s && mult == 0 && dp[i][suma][mult] > INF){
                        last_i = i;
                        end = true;
                        break;
                    }
                }
                if(end) break;
            }
            if(end) break;
        }
        if(end) break;
    }


    if(last_i == -1) last_i = 200;
     
    while(q--){
        ll num;
        cin >> num;

        if(dp[last_i][s][0] < num){
            cout << "NIE\n";
            continue;
        }

        ll suma = s;
        ll mult = 0;
        bool dodane = false;
        for(int i = last_i; i >= 1; i--){
            ll akt_ans = 0;
            if(dp[i-1][suma][mult] >= num){
                if(dodane) cout << 0;
                continue;
            }

            for(int k = 0; k <= 9; k++){
                    ll akt = (k*ten[i-1])%m;
                    ll prev = (mult-akt+m)%m;
                    ll add = dp[i-1][suma-k][prev];
                    

                    if(akt_ans+add >= num){
                        cout << k;
                        num -= akt_ans;
                        dodane = true;

                        suma -= k;
                        ll a = ((k)*ten[i-1])%m;
                        mult = (mult-a+m)%m;  
                        break;
                    }
                    akt_ans += add;
                }
        }   
        cout << '\n';
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
