/*
直接暴力枚举原分子分母的枚举量就有10^4^2，还要检验，时间上无法接受
由于1<=K<=N-1，所以cancel后的分子和分母肯定都在10^3范围内，考虑用10^6的复杂度去枚举它们
然后10^K枚举原分子和分母要共同删去的数字集，然后N!/(N-K)!枚举排列
很多信息可以预处理，预处理后常数不大，可以通过
*/
#include <bits/stdc++.h>
using namespace std;

namespace dasin{
  const int maxn=10005;
  vector<int> bit[maxn],maybe[1005][1005];
  bool f[maxn][maxn];
  int ban[1005];
  void dfs_maybe(int now,vector<int>&n,vector<int>&_n,vector<int>&res){
    if(!n.size() && !_n.size()){
      res.push_back(now);
      return;
    }
    if(n.size() && !(n.back()==0 && now==0)){
      int v=n.back();
      n.pop_back();
      dfs_maybe(now*10+v,n,_n,res);
      n.push_back(v);
    }
    if(_n.size()){
      int v=_n.back();
      _n.pop_back();
      dfs_maybe(now*10+v,n,_n,res);
      _n.push_back(v);
    }
  }
  
  int solve(int N,int K){
    vector<int> ten;
    ten.push_back(1);
    for(int i=1;i<=4;i++)ten.push_back(ten[i-1]*10);
    for(int n=1;n<ten[4];n++){
      for(int i=n;i;i/=10){
        bit[n].push_back(i%10);
      } 
    }
    for(int n=ten[K-1];n<ten[K];n++){
      ban[n]=0;
      for(int i=0;i<bit[n].size();i++){
        if(bit[n][i]==0)ban[n]=1;
        if(i && bit[n][i]>bit[n][i-1])ban[n]=1;
      }
    }
    vector<int> id(K);
    for(int n=1;n<ten[N-K];n++){
      vector<int> bn=bit[n];
      for(;bn.size()<N-K;)bn.push_back(0);
      for(int add=ten[K-1];add<ten[K];add++){
        if(ban[add])continue;
        vector<int> _bn(K);
        for(int i=0;i<K;i++)id[i]=i;
        do{
          for(int i=0;i<K;i++)_bn[i]=bit[add][id[i]];
          dfs_maybe(0,bn,_bn,maybe[n][add]);
        }while(next_permutation(id.begin(),id.end()));
      }
    }
    for(int _down=1;_down<ten[N-K];_down++){
      for(int _up=1;_up<_down;_up++){
        for(int add=ten[K-1];add<ten[K];add++){
          if(ban[add])continue;
          for(auto&down:maybe[_down][add]){
            for(auto&up:maybe[_up][add]){
              if(up*_down==_up*down)f[up][down]=1;
            }
          }
        }
      }
    }
    int totalUp=0,totalDown=0;
    for(int i=ten[N-1];i<ten[N];i++){
      for(int j=ten[N-1];j<i;j++){
        if(f[j][i]){
          totalUp+=j;
          totalDown+=i;
        }
      }
    }
    printf("%d %d\n",totalUp,totalDown);
    return 1;
  }
}

int main(){
  //freopen("aa.in","r",stdin);
  clock_t _st=clock();
  int N,K;
  scanf("%d%d",&N,&K);
  int status=dasin::solve(N,K);
  // printf("status %d\n",status);
  clock_t _ed=clock();
  // printf("time %.6lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
  return 0;
}