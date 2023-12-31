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
    int out = 0;
    int c = 0;
    node* nearest;
    node* anc;
    node* suflink;
    node* next[base];
    node* mem_go[base];

    node(int new_c, node* new_anc){
        c = new_c;
        anc = new_anc;
        nearest = nullptr;
        suflink = nullptr;
        for(int i = 0; i < base; i++){
            next[i] = nullptr;
            mem_go[i] = nullptr;
        }
    }
    ~node(){
        for(int i = 0; i < base; i++)
            if(next[i]) delete next[i];
    }
};

node* start = new node(0,nullptr);
bool ans[max_n];

node* go(node* v, int c);

node* suf(node *v){
    //cout << "suflink od: " << v << '\n';
    if(!v->suflink){
        node* x = v->anc;
        //moze check na anc niepotrzebny
        if(x == start || x->anc == start) v->suflink = start; 
        else v->suflink = go(x->suflink,x->c);
    }
    node* x = v->suflink;
    while(!x->out && x != start)
        x = suf(x);
    v->nearest = x;

    return v->suflink;
}

node* go(node *v, int c){
    if(!v->mem_go[c]){
        if(v->next[c])
            v->mem_go[c] = v->next[c];
        else{
            if(v == start) v->mem_go[c] = start;
            else v->mem_go[c] = go(suf(v),c); 
        }
    }
    return v->mem_go[c];
}

void dfs(node* v){
    //cout << "dfs od: " << v << '\n';
    if(!suf(v)){
        suf(v);
        //cout << "utworzony suf\n";
    }
    for(int i = 0; i < base; i++)
        if(v->next[i]) dfs(v->next[i]);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){

        string s;
        int n;
        cin >> s >> n;

        start->nearest = start;
        start->anc = start;

        for(int i = 1; i <= n; i++){
            string x;
            cin >> x;

            node* v = start;
            //cout << "dodajemy: " << x << " na drzewo\n";
            for(int j = 0; j < x.length(); j++){
                int c = (x[j]-'A');
                if(!v->next[c]) v->next[c] = new node(c,v);
                v = v->next[c];
                //cout << "j: " << j << " v: " << v << " c: " << c << '\n';
            }
            v->out = i; //konczy sie w danym v
            //cout << "v: " << v << " out: " << v->out << '\n';
        }

        //cout << "udane drzewo trie\n";

        //set suflink i nearest
        dfs(start);

        //cout << "udany dfs\n";

        node* v = start;
        for(int i = 0; i < s.length(); i++){
            int c = int(s[i]-'A');
            v = go(v,c);

            //cout << "i: " << i << " v: " << v << '\n';
            //cout << "out: " << v->out << '\n';
            if(v->out) ans[v->out] = true;
            //cout << "out\n";
            node* x = v->nearest;
            //cout << "x: " << x << '\n';
            while(x != start){
                //cout << "petla nearest\n";
                ans[x->out] = true;
                x = x->nearest;
            }
        }

        for(int i = 1; i <= n; i++){
            if(ans[i]) cout << "y\n";
            else cout << "n\n";
        }

        for(int i = 0; i < base; i++){
            if(start->next[i]){
                delete start->next[i];
                start->next[i] = nullptr;
            }
            start->mem_go[i] = nullptr;
        }
        for(int i = 1; i <= n; i++) ans[i] = false;
    }



    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
