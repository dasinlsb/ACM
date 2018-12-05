/*
把(i,p[i])看作二维平面上的点，那么选择一个点就会删掉这个点以及它左上方以及右下方的所有点
显然删除的点肯定会构成一条左下->右上的链，那么可以dp用f[i]表示从左到右考虑了前i个点，且第i个点已选的最小代价
直接递推难以优化O(n)的转移复杂度,考虑分治
先递归解决左半边，由于要保证相邻两个转移点之间没有任何其他点，可以根据y坐标从小到大在左边区间维护一条右下->左上的链，右边区间维护一条左下->右上的链
这样每当在右边加入一个点(x1,y1)，就相当于对于它的合法前驱(x2,y2)询问左半边的链中y2<y<y1内的最优答案，要求支持快速单点修改，区间查询最小值，可以用线段树加速
时间复杂度O(nlog^2n)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int inf=2e9+5;
int n;
struct Node{
  int x,y,v,f;
  void print(){printf("[%d,%d,%d,%d]\n",x,y,v,f);}
}a[maxn];
const int maxtree=1<<18;
int val[maxtree];
void push_up(int x){
  val[x]=min(val[x<<1],val[x<<1|1]);
}
void update(int v,int p,int l,int r,int x){
  if(l==r){
    val[x]=v;
    return;
  }
  int mid=l+r>>1;
  if(p<=mid)update(v,p,l,mid,x<<1);
  else update(v,p,mid+1,r,x<<1|1);
  push_up(x);
}
int ask(int L,int R,int l,int r,int x){
  if(l>=L && r<=R){
    return val[x];
  }
  int mid=l+r>>1,res=inf;
  if(L<=mid)res=min(res,ask(L,R,l,mid,x<<1));
  if(R>mid)res=min(res,ask(L,R,mid+1,r,x<<1|1));
  return res;
}
void solve(int l,int r){
  if(l==r){
    if(a[l].f==inf)a[l].f=0;
    a[l].f+=a[l].v;
    return;
  }
  int mid=l+r>>1;
  solve(l,mid);
  sort(a+l,a+1+mid,[&](Node a,Node b){
    return a.y<b.y;
  });
  sort(a+mid+1,a+1+r,[&](Node a,Node b){
    return a.y<b.y;
  });
  stack<Node> stkl,stkr;
  for(int li=l,ri=mid+1;ri<=r;ri++){
    for(;li<=mid && a[li].y<a[ri].y;li++){
      for(;stkl.size() && a[li].x>stkl.top().x;stkl.pop()){
        update(inf,stkl.top().y,1,n,1);
      }
      stkl.push(a[li]);
      update(a[li].f,a[li].y,1,n,1);
    }
    for(;stkr.size() && a[ri].x<stkr.top().x;stkr.pop());
    int low=stkr.size()?stkr.top().y:1;
    a[ri].f=min(a[ri].f,ask(low,a[ri].y,1,n,1));
    stkr.push(a[ri]);
  }
  for(int i=l;i<=mid;i++){
    update(inf,a[i].y,1,n,1);
  }
  sort(a+l,a+1+r,[&](Node a,Node b){
    return a.x<b.x;
  });
  solve(mid+1,r);
}
void output(){
  static Node stk[maxn];
  int top=0;
  for(int i=1;i<=n;i++){
    for(;top && a[i].y>stk[top].y;top--);
    stk[++top]=a[i];
  }
  int ans=inf;
  for(int i=1;i<=top;i++){
    ans=min(ans,stk[i].f);
  }
  assert(ans<inf);
  printf("%d\n",ans);
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",&a[i].y);
    a[i].x=i;
    a[i].f=inf;
  }
  for(int i=1;i<=n;i++){
    scanf("%d",&a[i].v);
  }
  fill(val,val+maxtree,inf);
  solve(1,n);
  // for(int i=1;i<=n;i++){
  //   a[i].print();
  // }
  output();
  return 0;
} 