#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int max_n = 3000;
const int sajz = 12;

int meks[max_n+7][max_n+7];
bool ile[2*max_n+7];
vi v;

int count(int i, int j){
    int akt_i = i-1;
    int akt_j = j-1;
    if(akt_i >= 0 && akt_j >= 0) 
        ile[meks[akt_i][akt_j]] = 1;

    while(akt_j >= 0){
        ile[meks[i][akt_j]] = 1;
        akt_j--;
    }

    while(akt_i >= 0){
        ile[meks[akt_i][j]] = 1;
        akt_i--;
    }
    
    for(int x = 0; x < i+j+7; x++) if(!ile[x]) return x;
    return -1;
}

int find_mex(int i, int j){
    int akt_i = i-1;
    int akt_j = j-1;

    while(akt_i >= 0){
        v.push_back(meks[akt_i*sajz][j*sajz]/12);
        akt_i--;
    }

    while(akt_j >= 0){
        v.push_back(meks[i*sajz][akt_j*sajz]/12);
        akt_j--;
    }

    sort(v.begin(),v.end());
    int next = 0;;
    for(auto x:v){
        if(x != next) return next*sajz;
        next++;
    }
    if(v.size() == 0) return 0;
    else return (v[v.size()-1]+1)*sajz;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int i = 0; i < sajz; i++){
        for(int j = 0; j < sajz; j++){
            meks[i][j] = count(i,j);
            for(int x = 0; x < i+j+7; x++) ile[x] = 0;
        }
    }

    //albo <=
    for(int i = 0; i < max_n/sajz; i++){
        for(int j = 0; j < max_n/sajz; j++){
            int start = find_mex(i,j);
            v.clear();
            meks[i*sajz][j*sajz] = start;
            //cout << "i: " << i*sajz << " j: " << j*sajz << " meks: " << start << '\n';
            //for(int x = 0; x < i+j+7; x++) ile[x] = 0;
            //fill(akt_i,akt_j,start);
        }
    }

    /*
    for(int i = sajz*3-1; i >= 0; i--){
        for(int j = 0; j < sajz*3; j++) 
            cout << meks[i-i%sajz][j-j%sajz]+meks[i%sajz][j%sajz] << ' ';
        cout << '\n';
    }
    */

    //cout << "meks 24 31 " << meks[24-24%sajz][31-34%sajz] << " + " <<meks[24%sajz][31%sajz] << '\n';
    
    

    int t;
    cin >> t;
    while(t--){

        int n;
        cin >> n;
        int ans = 0;
        for(int i = 1; i <= n; i++){
            int x,y;
            cin >> x >> y;
            int p = meks[y-y%sajz][x-x%sajz]+meks[y%sajz][x%sajz];
            ans = ans^p;
        }
        if(ans) cout << "Ada\n";
        else cout << "Vinit\n";

    }


    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
