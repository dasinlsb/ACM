/*
打表可以发(cai)现(ce)起点不会很大
直接暴力从小到大枚举起点对应的质数，然后二分找到右端点的右界，倒过来枚举右端点(这样好处是一旦找到可以直接从内层循环break，否则对于一个固定的左端点要跑满)
检验质数可以miller_rabin，事实上枚举不大于sqrt(n)的质数好像更快一点...
*/
#include <bits/stdc++.h>
using namespace std;

namespace dasin{
  const int maxn=2e7;
  int maxST,pn,prim[maxn/10];
  bool vis[maxn];
  long long sum[maxn/10];
  void init(){
    for(int i=2;i<maxn;i++){
      if(!vis[i])prim[++pn]=i;
      for(int j=1;j<=pn && i*prim[j]<maxn;j++){
        vis[i*prim[j]]=1;
        if(i%prim[j]==0)break;
      }
    }
    maxST=80;
    for(int i=1;i<=pn;i++){
      sum[i]=sum[i-1]+prim[i];
    }
  }
  int isPrim(long long n){
    if(n==1)return 0;
    if(n<maxn)return !vis[n];
    for(int i=1;1LL*prim[i]*prim[i]<=n;i++){
      if(n%prim[i]==0)return 0;
    }
    return 1;
  }
  int solve(long long N){
    pair<int,long long> res=make_pair(1,-2);
    for(int st=1;st<=maxST && prim[st]<=N;st++){
      int ed=st+res.first;
      if(~(sum[ed]-sum[st-1])&1)ed++;
      if(ed>pn)break;
      int maxed=upper_bound(sum+ed,sum+1+pn,sum[st-1]+N)-sum-1;
      for(int r=maxed;r>=ed;r--){
        long long p=sum[r]-sum[st-1];
        if(!isPrim(p))continue;
        res=max(res,make_pair(r-st+1,-p));
        break;
      }
    }
    printf("%lld %d\n",-res.second,res.first);
    return 1;
  }
  void main(){
    init();
    int _;scanf("%d",&_);
    for(;_--;){
      long long n;scanf("%lld",&n);
      int status=solve(n);
      // printf("status %d\n",status);
    }
  }
}

int main(){
  freopen("aa.in","r",stdin);
  clock_t _st=clock();
  dasin::main();
  clock_t _ed=clock();
  // printf("time %.6lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
  return 0;
}