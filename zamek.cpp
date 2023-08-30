#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef pair<ll,ll> pl;

struct Pole{
    int x1;
    int y1;
    int x2;
    int y2;
};

const int max_n = 1e6+7;
Pole arr[max_n];
bool niebezpieczne[max_n];
pi zapytania[max_n];

vector<pi> v; //first - x, second - ind (jesli ind na minusie usuwanie jesli +n to bomba)
set<int> s; // wartosc y
map<int,int> lookup; //first - y, second - ind
vi g[max_n]; //graf
//jakies skalowanie na x i y
//first - x/y, second - +ind po lewej/ na dole -ind po prawej/na gorze
vector<pi> poziome[max_n];
vector<pi> pionowe[max_n];
map<int,int> sx;
map<int,int> sy;

queue<int> q;
int dist[max_n];

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int w,h,n,m;
    cin >> w >> h >> n >> m;

    pi start;
    pi end;

    int a,b;
    cin >> a >> b;
    start = {a,b};
    cin >> a >> b;
    end = {a,b};

    for(int i = 1; i <= n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        arr[i] = {x1,y1,x2,y2};
        v.push_back({x1,i});
        v.push_back({x2,-i});
    }

    for(int i = 1; i <= m; i++){
        int x,y;
        cin >> x >> y;
        zapytania[i] = {x,y};
        v.push_back({x,i+n});
    }

    sort(v.begin(),v.end());

    //usunac niebezpieczne wierzcholki

    //cout << "usuwanie niebezpiecznych\n";
    for(auto x:v){
        int ind = x.second;
        if(ind < 0){
            //usuwamy
            ind = -ind;
            //cout << "usuwamy: " << ind << " val: " << arr[ind].y2 << '\n';
            s.erase(arr[ind].y2);
        }
        else if(ind <= n){
            //dodajemy
            //cout << "dodajemy: " << ind << " val: " << arr[ind].y2 << '\n';
            s.insert(arr[ind].y2);
            lookup[arr[ind].y2] = ind;
        }
        else{
            //ktore Pole nie dziala
            ind -= n;
            int y = zapytania[ind].second; //pytamy o dany y
            //cout << "bomba nr: " << ind << " val: " << y << '\n';
            auto ans = s.lower_bound(y);
            //cout << "niebezpieczne od wysokosc: " << *ans << " ind: " << lookup[*ans] << '\n';
            niebezpieczne[lookup[(*ans)]] = true;
        }   
    }

    //stworzyc graf
     
    int it_x = 1;
    int it_y = 1;
    for(int i =  1; i <= n; i++){
        Pole p = arr[i];
        //wrzucamy dolny y
        if(!sx.count(p.x1)) sx[p.x1] = it_x++;
        pionowe[sx[p.x1]].push_back({p.y1,-i});
        if(!sx.count(p.x2)) sx[p.x2] = it_x++;
        pionowe[sx[p.x2]].push_back({p.y1,i});

        //wrzucamy mniejszy x
        if(!sy.count(p.y1)) sy[p.y1] = it_y++;
        poziome[sy[p.y1]].push_back({p.x1,-i});
        if(!sy.count(p.y2)) sy[p.y2] = it_y++;
        poziome[sy[p.y2]].push_back({p.x1,i});
    }

    int i = 1;
    //nie stykac sie rogami
    //cout << "tworzenie grafu\n";
    while(!poziome[i].empty()){
        sort(poziome[i].begin(),poziome[i].end());
        int u = 0;
        int d = 0;
        //cout << "nowa linia\n";
        for(auto x:poziome[i]){
            int ind = x.second;
            if(ind > 0) u = ind;
            else d = -ind;
            //cout << "u: " << u << " d: " << d << '\n';
            if(u == 0 || d == 0) continue;
            if(niebezpieczne[u] || niebezpieczne[d]) continue;
            if(arr[u].x1 < arr[d].x2 && arr[u].x2 > arr[d].x1){
                g[u].push_back(d);
                g[d].push_back(u);
            }
        }
        i++;
    }

    i = 1;
    while(!pionowe[i].empty()){
        sort(pionowe[i].begin(),pionowe[i].end());
        int l = 0;
        int r = 0;
        for(auto x: pionowe[i]){
            int ind = x.second;
            if(ind > 0) l = ind;
            else r = -ind;
            //cout << "l: " << l << " r: " << r << '\n';
            if(l == 0 || r == 0) continue;
            if(niebezpieczne[l] || niebezpieczne[r]) continue;
            if(arr[l].y1 < arr[r].y2 && arr[l].y2 > arr[r].y1){
                g[l].push_back(r);
                g[r].push_back(l);
            }
        }
        i++;
    }

    int start_ind = 0;
    int end_ind = 0;
    for(int i = 1; i <= n; i++){
        if(arr[i].x1 < start.first && arr[i].x2 > start.first && arr[i].y1 < start.second && arr[i].y2 > start.second)
            start_ind = i;
        if(arr[i].x1 < end.first && arr[i].x2 > end.first && arr[i].y1 < end.second && arr[i].y2 > end.second)
            end_ind = i;
    }  

    /*
    cout << "start_ind: " << start_ind << " end_ind: " << end_ind << '\n';
    for(int i = 1; i <= n; i++){
        cout << "i: " << i << '\n';
        cout << "niebezpieczne: " << niebezpieczne[i] << '\n';
        cout << "graf\n";
        for(auto x:g[i]) cout << x << ' ';
        cout << '\n'; 
    }
    */

    if(start_ind == end_ind) cout << 1;
    else{
        q.push(start_ind);
        dist[start_ind] = 1;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto x:g[v]){
                if(!dist[x]){
                    dist[x] = dist[v]+1;
                    q.push(x);
                }
            }
        }
        cout << dist[end_ind];
    }


    return 0;
}

//g++ -O3 -static -Wall .cpp -std=c++17
