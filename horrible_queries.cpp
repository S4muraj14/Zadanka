#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

ll p,k,val;

const int base = 1<<17;
ll tree[base*2];
ll tree2[base*2];

void push(int v ,int l, int r, ll len){
  tree2[l] += tree2[v];
  tree2[r] += tree2[v];

  tree[l] += len*tree2[v];
  tree[r] += len*tree2[v];

  tree2[v] = 0;
}

void add(int v,ll a, ll b){
  if(p > b || k < a ) return;
  if(a >= p && b <= k){
    tree[v] += (b-a+1)*val;
    tree2[v] += val;
  }
  else{
    ll l = v*2;
    ll r = v*2+1;
    ll mid = (a+b)/2;

    push(v,l,r,(b-a+1)/2);
    add(l,a,mid);
    add(r,mid+1,b);

    tree[v] = tree[l]+tree[r];
  }
}

ll query(int v, int a, int b){
  if(p > b || k < a ) return 0;
  if(a >= p && b <= k){
    return tree[v];
  }
  else{
    ll l = v*2;
    ll r = v*2+1;
    ll mid = (a+b)/2;

    push(v,l,r,(b-a+1)/2);

    return query(l,a,mid)+query(r,mid+1,b);
  }
}

void clear(int n){
  for(int i = 1; i <= n; i++){
    p = i; k = i;
    val = -query(1,0,base-1);
    add(1,0,base-1);
  }
}

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  while(t--){

    int n,c;
    cin >> n >> c;

    while(c--){

      int z;
      cin >> z;

      if(z == 0){
        cin >> p >> k >> val;
        add(1,0,base-1);
      }
      else{
        cin >> p >> k;
        cout << query(1,0,base-1) << '\n';
      }
    }

    clear(n);

  }


  return 0;
}
