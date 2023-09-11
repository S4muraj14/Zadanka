#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_m = 107;
const int max_n = 1e4;
bool dp[max_n+7][max_m];
int p[5] = {0,1000,100,10,1};

int get_digit(int n, int x){
    if(n < p[x]) return 0;
    for(int i = 4; i > x; i--) n /= 10;
    return n%10;
}

int next(int n, int x){
    if(get_digit(n,x) == 9) return n-9*p[x];
    else return n+p[x];
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){

        int n,m;
        cin >> n >> m;

        for(int i = 0; i < max_n; i++) dp[i][0] = (i > n ? 1:0);
        
        for(int i = 1; i <= m; i++){
            for(int j = 0; j < max_n; j++){
                //logika na zasadzie jesli nasza tura to szukamy przynajmniej
                //jednego wygrywajacego, inaczej przeciwnik szuka przynajmniej 
                //jednego przegrywajacego
                int player = (i%2 == m%2);
                bool w = !player;
                for(int l = 1; l <= 4; l++){
                    bool ans = dp[next(j,l)][i-1];
                    if(player){
                        if(ans){
                            w = 1;
                        }
                    }
                    else{
                        if(!ans){
                            w = 0;
                        }
                    }
                }
                dp[j][i] = w;
            }
        }

        if(dp[n][m]) cout << "Ada\n";
        else cout << "Vinit\n";

    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
