/*
直接上高精度两个大数的比较一次的复杂度可能达到10W级别无法接受
考虑用主席树维护维护每个点的距离的二进制表示
加上一个2的幂相当于连续的一段1翻成0在加个1，也就是若干个单点翻转，势能分析一下复杂度是对的
比较两个距离的大小相当于求两个二进制数的LCP，然后直接比较下一位数字的大小，这个可以用hash解决
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100025;
const int maxm=1e7;
const int mod=1e9+7;
const int P[2]={mod,mod-2};
int tot,pw[2][maxn];
struct Node{
  int ld,hs[2],son[2];
}t[maxm];
void up(int x){
  int&l=t[x].son[0];
  int&r=t[x].son[1];
  for(int i=0;i<2;i++){
    t[x].hs[i]=(t[l].hs[i]+1LL*pw[i][t[x].ld]*t[r].hs[i])%P[i];
  }
}
int ins(int p,int l,int r,int y){
  int x=++tot;
  if(l==r){
    t[x].hs[0]=1-t[y].hs[0];
    t[x].hs[1]=1-t[y].hs[1];
    return x;
  }
  int mid=l+r>>1;
  t[x].ld=mid-l+1;
  if(p<=mid){
    t[x].son[0]=ins(p,l,mid,t[y].son[0]);
    t[x].son[1]=t[y].son[1];
  }else{
    t[x].son[0]=t[y].son[0];
    t[x].son[1]=ins(p,mid+1,r,t[y].son[1]);
  }
  up(x);
  return x;
}
int ask(int p,int l,int r,int x){
  if(!x)return 0;
  if(l==r)return t[x].hs[0];
  int mid=l+r>>1;
  if(p<=mid)return ask(p,l,mid,t[x].son[0]);
  else return ask(p,mid+1,r,t[x].son[1]);
}
int eq(int x,int y){
  return t[x].hs[0]==t[y].hs[0] && t[x].hs[1]==t[y].hs[1];
}
int getp(int p,int l,int r,int x,int y){
  if(l==r){
    return eq(x,y)?l:p;
  }
  int mid=l+r>>1;
  if(eq(t[x].son[1],t[y].son[1])){
    return getp(mid+1,l,mid,t[x].son[0],t[y].son[0]);
  }
  return getp(p,mid+1,r,t[x].son[1],t[y].son[1]);
}
int cmp(int x,int y){
  int p=getp(maxn+1,0,maxn,x,y);
  return p && ask(p-1,0,maxn,x)<ask(p-1,0,maxn,y);
}
struct cmp_p{
  bool operator()(const pair<int,int>&x,const pair<int,int>&y)const{
    return !cmp(x.first,y.first);
  }
};

int n,m,S,T,ed,fir[maxn];
struct Edge{int v,w,nxt;}e[maxn*2];
int root[maxn],pre[maxn];
void adde(int x,int y,int z){
  e[++ed].v=y;e[ed].w=z;e[ed].nxt=fir[x];fir[x]=ed;
}
int main(){
  freopen("aa.in","r",stdin);
  for(int i=0;i<2;i++){
    pw[i][0]=1;
    for(int j=1;j<maxn;j++){
      pw[i][j]=2LL*pw[i][j-1]%P[i];
    }
  }
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int x,y,z;scanf("%d%d%d",&x,&y,&z);
    adde(x,y,z);adde(y,x,z);
  }
  scanf("%d%d",&S,&T);
  for(int i=1;i<=n;i++)if(i!=S)root[i]=ins(maxn,0,maxn,root[i]);
  priority_queue< pair<int,int>,vector< pair<int,int> > ,cmp_p> q;
  q.push(make_pair(root[S],S));
  pre[S]=S;
  for(;q.size();){
    pair<int,int>t=q.top();q.pop();
    int x=t.second;
    if(t.first!=root[x])continue;
    for(int i=fir[x];i;i=e[i].nxt){
      if(!cmp(root[x],root[e[i].v]))continue;
      int _x=root[x];
      int _w=e[i].w;
      for(;ask(_w,0,maxn,_x)==1;){
        _x=ins(_w,0,maxn,_x);
        _w++;
      }
      _x=ins(_w,0,maxn,_x);
      if(cmp(_x,root[e[i].v])){
        pre[e[i].v]=x;
        q.push(make_pair(root[e[i].v]=_x,e[i].v));
      }
    }
  }
  if(!pre[T]){
    return puts("-1"),0;
  }
  int dist=0;
  for(int i=0,j=1;i<maxn;i++){
    if(ask(i,0,maxn,root[T])){
      dist=(dist+j)%mod;
    }
    j=2LL*j%mod;
  }
  printf("%d\n",dist);
  vector<int>ans;
  for(int x=T;;x=pre[x]){
    ans.push_back(x);
    if(x==S)break;
  }
  reverse(ans.begin(),ans.end());
  printf("%d\n",ans.size());
  for(int i:ans)printf("%d ",i);
  return 0;
}