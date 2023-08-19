#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

struct Node{
  int val;
  Node *l;
  Node *r;

  Node(int v = 0){
    val = v;
    l = nullptr;
    r = nullptr;
  }

  ~Node(){
      if(l) delete l;
      if(r) delete r;
  }
};

const int base = 1<<30;
Node *wierzcholek = new Node();

void update(Node *v, int a, int b, int q){
  //cout << "update od: " << a << " - " << b << " q: " << q << '\n';
  v->val--;
  if(a == b) return;

  int mid = (a+b)/2;

  if(!v->l) v->l = new Node((b-a+1)/2);
  if(q <= mid) update(v->l,a,mid,q);
  else{
    if(!v->r) v->r = new Node((b-a+1)/2);
    update(v->r,mid+1,b,q);
  }
}

int query(Node *v, int a, int b, int q){
  //cout << "query od: " << a << " - " << b << " q: " << q << '\n';
  if(a == b) return a;

  int mid = (a+b)/2;

  if(!v->l) v->l = new Node((b-a+1)/2);
  Node *l = v->l;
  //cout << "l val: " << l->val << '\n';
  if(q <= l->val) return query(l,a,mid,q);
  else{
    if(!v->r) v->r = new Node((b-a+1)/2);
    Node *r = v->r;
    return query(r,mid+1,b,q-l->val);
  }
}

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);

  int n,q;
  cin >> n >> q;

  wierzcholek->val = base;
  update(wierzcholek,0,base-1,0);

  while(q--){

    char c;
    int x;
    cin >> c >> x;

    if(c == 'L') cout << query(wierzcholek,0,base-1,x) << '\n';
    else{
      int v = query(wierzcholek,0,base-1,x);
      update(wierzcholek,0,base-1,v);
    }
  }




  return 0;
}
