#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

struct Node{
  int pref;
  int suf;
  int sum;
  int ans;
};

const int base = 1<<16;
const int INF = -1e4-7;
Node tree[base*2];

Node match(Node l, Node r){
  Node ans;

  ans.pref = max(l.pref,l.sum+r.pref);
  ans.suf = max(r.suf,r.sum+l.suf);
  ans.sum = l.sum+r.sum;
  ans.ans = max(l.ans,r.ans);
  ans.ans = max(ans.ans,l.suf+r.pref);

  return ans;
}

void update(int a, int val){
  a += base;
  tree[a] = {val,val,val,val};

  a /= 2;
  while(a){
    tree[a] = match(tree[a*2],tree[a*2+1]);
    a /= 2;
  }

}

int query(int a, int b){
  a += base-1;
  b += base+1;
  Node prev = {INF,INF,INF,INF};
  stack<Node> s;
  while(a/2 != b/2){
    if(a%2 == 0) prev = match(prev,tree[a+1]);
    if(b%2 == 1) s.push(tree[b-1]);
    a /= 2; b /= 2;
  }
  while(!s.empty()){
    prev = match(prev,s.top());
    s.pop();
  }
  return prev.ans;
}

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  for(int i = 1 ; i <= n; i++){
    int x;
    cin >> x;
    update(i,x);
  }

  int q;
  cin >> q;
  while(q--){
    int c;
    cin >> c;
    if(c == 0){
      int ind,val;
      cin >> ind >> val;
      update(ind,val);
    }
    if(c == 1){
      int a,b;
      cin >> a >> b;
      cout << query(a,b) << '\n';
    }
  }


  return 0;
}
