/*
直接暴力枚举所有[1,M)(M=10^k,M>N)中的数，如果为质数就把十进制表示的各位排序后哈希一下，在每种数位集合中|S|^2枚举首项和公差，加一点上下界优化和剪枝就可以跑的飞快啦

*/
#include <bits/stdc++.h>
using namespace std;

namespace dasin{
  const int maxn=1e6+5;
  int pn,tot,prim[maxn/10];
  bool vis[maxn];
  vector<int> per[maxn];
  vector< pair<int,string> > ans;
  void init(){
    for(int i=2;i<maxn;i++){
      if(!vis[i])prim[++pn]=i;
      for(int j=1;j<=pn && i*prim[j]<maxn;j++){
        vis[i*prim[j]]=1;
        if(i%prim[j]==0)break;
      }
    }
  }
  int getHash(int n){
    static const int maxhs=2e6;
    static int a[10],hsid[maxhs];
    int m=0;
    for(int i=n;i;i/=10){
      a[++m]=i%10;
    }
    sort(a+1,a+1+m);
    int v=0;
    for(int i=1;i<=m;i++){
      v=v*11+a[i]+1;
    }
    assert(v<maxhs);
    if(!hsid[v])hsid[v]=++tot;
    return hsid[v];
  }
  int find(vector<int>&q,int x){
    return *lower_bound(q.begin(),q.end(),x)==x;
  }
  int solve(int N,int K){
    if(N==1000*1000)N--;
    int maxN=1;
    for(;maxN<=N;maxN*=10);
    for(int n=1000;n<maxN;n++){
      if(vis[n])continue;
      int h=getHash(n);
      per[h].push_back(n);
    }
    for(int hi=1;hi<=tot;hi++){
      vector<int>&q=per[hi];
      sort(q.begin(),q.end());
      for(int st=0;st+K-1<q.size();st++){
        if(q[st]>N)break;
        int max_nxt=(q.back()-q[st])/(K-1)+q[st];
        for(int nxt=st+1;q[nxt]<=max_nxt;nxt++){
          int d=q[nxt]-q[st];
          int flag=1;
          for(int i=1;i<K;i++){
            if(!find(q,q[st]+i*d)){
              flag=0;
              break;
            }
          }
          if(flag){
            string s;
            for(int i=0;i<K;i++){
              s+=to_string(q[st]+i*d);
            }
            ans.push_back(make_pair(q[st],s));
          }
        }
      }
    }
    sort(ans.begin(),ans.end());
    for(auto&it:ans){
      const char*s=it.second.c_str();
      puts(s);
    }
    return 1;
  }
  void main(){
    init();
    int N,K;scanf("%d%d",&N,&K);
    int status=solve(N,K);
    // printf("status %d\n",status);
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