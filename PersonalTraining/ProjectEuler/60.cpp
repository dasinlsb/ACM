#include <bits/stdc++.h>
using namespace std;
const int maxn=90000005;
const int maxp=1500;
const int inf=1e9;
const int TOTAL=5;
clock_t _st;
int pn,prim[maxn/10];bool vis[maxn];
int tag[maxp];
vector<int> G[maxp],des;
pair< int,vector<int> >best;
void print_time(){
  clock_t _ed=clock();
  printf("time %.6lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
}
int con(int x,int y){
  long long _x=x,_y=y;
  for(int i=y;i;i/=10)_x*=10;_x+=y;
  for(int i=x;i;i/=10)_y*=10;_y+=x;
  // assert(_x<maxn && _y<maxn);
  if(_x>=maxn || _y>=maxn)return 0;
  return !vis[_x] && !vis[_y];
}
void dfs(int p,int sum,int have){
  if(have && sum+(TOTAL-have)*des[have-1]>=best.first){
    return;
  }
  if(have==TOTAL){
    best.first=sum;
    best.second=des;
    print_time();
    exit(0);
    return;
  }
  if(p==maxp)return;
  if(tag[p]==have){
    des[have]=prim[p];
    for(int v:G[p])tag[v]++;
    dfs(p+1,sum+prim[p],have+1);
    for(int v:G[p])tag[v]--;
  }
  dfs(p+1,sum,have);
}
int solve(){
  for(int i=2;i<maxn;i++){
    if(!vis[i])prim[++pn]=i;
    for(int j=1;j<=pn && i*prim[j]<maxn;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0)break;
    }
  }
  des.resize(TOTAL,0);
  best.first=inf;
  for(int i=2;i<maxp;i++){
    for(int j=i+1;j<maxp;j++){
      if(con(prim[i],prim[j])){
        G[i].push_back(j);
      }
    }
  }
  dfs(2,0,0);
  if(best.first==inf)return 0;
  printf("sum %d\n",best.first);
  for(int x:best.second)printf("%d ",x);puts("");
  return 1;
}
int main(){
  freopen("aa.in","r",stdin);
  // freopen("mine.out","w",stdout);
  _st=clock();
  printf("found %d\n",solve());
  return 0;
}