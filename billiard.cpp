#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
typedef long long ll;
typedef long double ld;
//typedef __int128 int128;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

pair<ll,pl> euclid(ll a, ll b){
    if(b == 0)
        return {a,{1,0}};
    
    pair<ll,pl> p = euclid(b,a%b);
    ll x = p.nd.st;
    ll y = p.nd.nd;
    return {p.st,{y,x-y*(a/b)}};
}   

ll suf(ll a, ll b){
    ll ans = a/b;
    if(a%b != 0) ans++;
    return ans;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n,m,x,y,vx,vy;

    cin >> n >> m >> x >> y >> vx >> vy;

    if(vx == 0){
        if(x != 0 && x != n) cout << -1;
        else if(y == 1) cout << x << ' ' << m;
        else cout << x << ' ' << 0;
    }
    else if(vy == 0){
        if(y != 0 && y != m) cout << -1;
        else if(x == 1) cout << n << ' ' << y;
        else cout << 0 << ' ' << y;
    }
    else{
        if(x == 0 && vx == -1) vx = 1;
        else if(x == n && vx == 1) vx = -1;

        if(y == 0 && vy == -1) vy = 1;
        else if(y == m && vy == 1) vy = -1;

        if(vx == 1 /*&& x != 0*/) x = n-x;
        if(vy == 1 /*&& y != 0*/) y = m-y;

        //cout << "vx: " << vx << " vy: " << vy << "\n";
        //cout << "x: " << x << " y: " << y << "\n";

        ll target = y-x;

        pair<ll,pl> p = euclid(max(n,m),min(n,m));

        ll d = p.st;
        ll a = p.nd.st;
        ll b = p.nd.nd; //znajdzie -b

        /* if(target < 0){
            a = -a;
            b = -b;
        } */
        if(n < m) swap(a,b);

        //cout << "init val\n";
        //cout << "d: " << d << " a: " << a << " b: " << b << "\n";

        //cout << "target: " << target << '\n';
        if(target%d != 0) cout << -1;
        else{
            ll c = target/d;
            a *= c;
            b *= c;

            //cout << "c(target/d): " << c << " a: " << a << " b: " << b << '\n';

            //a > 0 i b < 0 - cel
            ll nww_a = m/d;
            ll nww_b = n/d;
            //mozna zamienic
            /* if(nww_a < 0){
                nww_a = -nww_a;
                nww_b = -nww_b;
            } */

            //cout << "nww_a: " << nww_a << " nww_b: " << nww_b << '\n';

            //dopelnic do najmniejszego rozwiazania, gdzie a > 0 i b < 0
            if(a > 0){
                //doprowadzenie do najmniejszej niedodatniej
                ll ile = suf(a,nww_a);
                //cout << "a > 0, ile: " << ile << '\n';
                a -= nww_a*ile;
                b += nww_b*ile;
                //cout << "po zmianie a: " << a << " b: " << b << "\n";
            }

            if(b > 0){
                ll ile = suf(-b,nww_b);
                //cout << "b >= 0, ile: " << ile << '\n';
                a += nww_a*ile;
                b -= nww_b*ile;
                if(b == 0){
                    a += nww_a;
                    b -= nww_b; 
                }
                //cout << "po zmianie a: " << a << " b: " << b << "\n";
            }
            if(a < 0){
                ll ile = suf(-a,nww_a);
                //cout << "a <= 0, ile: " << ile << '\n';
                a += nww_a*ile;
                b -= nww_b*ile;
                //cout << "po zmianie a: " << a << " b: " << b << "\n";
            }

            //cout << "new_a: " << a << " new_b: " << b << "\n";

            b = -b; //dla mod

            ll ans_x = 0;
            ll ans_y = 0;
            if(a%2 == 0 && vx == 1) ans_x = n;
            if(a%2 == 1 && vx == -1) ans_x = n;
 
            if(b%2 == 0 && vy == 1) ans_y = m;
            if(b%2 == 1 && vy == -1) ans_y = m;

            cout << ans_x << ' ' << ans_y;
        }
    }

    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
