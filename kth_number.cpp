#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

struct Node{
  int val;
  Node *l;
  Node *r;

  Node(){
    val = 0;
    l = nullptr;
    r = nullptr;
  }

  ~Node(){
      if(l) delete l;
      if(r) delete r;
  }
};

const int base = 1<<17;
const int max_n = 1e5+7;
Node *tree[max_n];
pi arr[max_n];
int true_val[max_n];

void start(Node *v, int a, int b){
  if(a == b) return;
  v->l = new Node();
  v->r = new Node();
  start(v->l,a,(a+b)/2);
  start(v->r,(a+b)/2+1,b);
}

void update(Node *v, Node *prev, int a, int b, int q){
  //cout << "update od: " << a << " - " << b << " q: " << q << '\n';
  v->val = prev->val + 1;
  if(a == b) return;

  int mid = (a+b)/2;

  if(q <= mid){
    v->l = new Node();
    v->r = prev->r;
    update(v->l,prev->l,a,mid,q);
  }
  else{
    v->r = new Node();
    v->l = prev->l;
    update(v->r,prev->r,mid+1,b,q);
  }
}

int query(Node *v, Node* prev, int a, int b, int q){
  //cout << "query od: " << a << " - " << b << " q: " << q <<7 3
  if(a == b) return a;

  int mid = (a+b)/2;

  Node *l = v->l;
  Node *l_p = prev->l;
  int diff = l->val - l_p->val;
  if(q <= diff) return query(l,l_p,a,mid,q);
  else{
    Node *r = v->r;
    Node *r_p = prev->r;
    return query(r,r_p,mid+1,b,q-diff);
  }
}

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);

  int n,q;
  cin >> n >> q;

  for(int i = 1; i <= n; i++){
    int x;
    cin >> x;
    arr[i] = {x,i};
  }
  sort(arr+1,arr+n+1);

  int s = 0;
  int prev = -1e9-7;
  for(int i = 1; i <= n; i++){
    if(arr[i].first > prev){
      s++;
      true_val[s] = arr[i].first;
    }
    prev = arr[i].first;
    arr[i] = {arr[i].second,s};
  }

  sort(arr+1,arr+n+1);

  tree[0] = new Node();
  start(tree[0],0,base-1);

  for(int i = 1; i <= n; i++){
    int x = arr[i].second;
    tree[i] = new Node();
    update(tree[i],tree[i-1],0,base-1,x);
  }


  while(q--){
    int a,b,x;
    cin >> a >> b >> x;
    cout << true_val[query(tree[b],tree[a-1],0,base-1,x)] << '\n';
  }




  return 0;
}
