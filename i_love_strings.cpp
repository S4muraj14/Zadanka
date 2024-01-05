#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

const int base = 60;
const int max_n = 1007;

struct node{
    vector<int> ind;
    int c = 0; //jaka litera
    bool checked = false; //czy wzielismy ans
    bool out = false; //czy cos sie konczy w danym v
    int nearest = 0; //najblizszy gdzie sie cos konczy
    int anc = 0;
    int suflink = 0;
    int next[base];
    int mem_go[base];

    node(int new_c, int new_anc){
        c = new_c;
        anc = new_anc;
        for(int i = 0; i < base; i++){
            next[i] = 0;
            mem_go[i] = 0;
        }
    }
};

bool ans[max_n];
vector<node> vec;

int go(int v, int c);

int suf(int v){
    if(!vec[v].suflink){
        int x = vec[v].anc;
        if(v == 1 || x == 1) vec[v].suflink = 1; 
        else vec[v].suflink = go(suf(x),vec[v].c);

        x = vec[v].suflink;
        if(vec[x].out) vec[v].nearest = x;
        else vec[v].nearest = vec[x].nearest;
    }

    return vec[v].suflink;
}

int go(int v, int c){
    if(!vec[v].mem_go[c]){
        if(vec[v].next[c])
            vec[v].mem_go[c] = vec[v].next[c];
        else{
            if(v == 1) vec[v].mem_go[c] = 1;
            else vec[v].mem_go[c] = go(suf(v),c); 
        }
    }
    return vec[v].mem_go[c];
}

void dfs(int v){
    if(!suf(v))
        suf(v);
    for(int i = 0; i < base; i++)
        if(vec[v].next[i]) dfs(vec[v].next[i]);
}

int main(){

    int t;
    cin >> t;
    while(t--){

        string s;
        int n;
        cin >> s >> n;

        node blank(0,0);
        node start(0,1);
        vec.push_back(blank);
        vec.push_back(start);
        vec[1].out = true;

        for(int i = 1; i <= n; i++){
            string x;
            cin >> x;

            int v = 1;
            for(int j = 0; j < x.length(); j++){
                int c = (x[j]-'A');
                if(!vec[v].next[c]){
                    vec[v].next[c] = vec.size();
                    node a(c,v);
                    vec.push_back(a);
                }
                v = vec[v].next[c];
            }
            vec[v].out = true; //konczy sie w danym v
            vec[v].ind.push_back(i);
        }

        dfs(1);

        int v = 1;
        for(int i = 0; i < s.length(); i++){
            int c = int(s[i]-'A');
            v = go(v,c);

            if(vec[v].out)
                for(auto y : vec[v].ind)
                    ans[y] = true;
                
            int x = vec[v].nearest;
            while(x != 1 && !vec[x].checked){
                for(auto y : vec[x].ind)
                    ans[y] = true;
                
                vec[x].checked = true;
                x = vec[x].nearest;
            }
        }

        for(int i = 1; i <= n; i++){
            if(ans[i]) cout << "y\n";
            else cout << "n\n";
        }

        vec.clear();
        for(int i = 1; i <= n; i++) ans[i] = false;
    }



    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
