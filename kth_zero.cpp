#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

const int base = 1<<17;
int tree[base*2];

void update(int a, int val){
  a += base;
  if(val == 0) tree[a] = 1;
  else tree[a] = 0;
  a /= 2;
  while(a){
    tree[a] = tree[a*2]+tree[a*2+1];
    a /= 2;
  }
}

int query(int val){
  int a = 1;

  while(a < base){
    if(tree[a*2] >= val) a *= 2;
    else{
      val -= tree[a*2];
      a = a*2+1;
    }
  }

  return a-base;
}

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);

  int n,q;
  cin >> n >> q;

  for(int i = 1; i <= n; i++){
    int x;
    cin >> x;
    update(i,x);
  }

  while(q--){

    int c;
    cin >> c;

    if(c == 1){
      int ind;
      cin >> ind;
      //cout << "tree[1]: " << tree[1] << '\n';
      if(tree[1] < ind) cout << "NO\n";
      else cout << query(ind)-1 << '\n';
    }

    else{
      int ind,val;
      cin >> ind >> val;
      update(ind+1,val);
    }


  }



  return 0;
}
