/*
一旦两个点在某一时刻t走到同一个点，那么显然之后它们的位置都会相同
暴力走min(n,K)步即可，剩下的问题就是每种物品有一种颜色，求选出物品集合颜色各不相同的方案
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
const int mod=1000*1000*1000+7;
int cnt[maxn];
class Autogame{
  public:
  int wayscnt(vector<int>a,int K){
    int n=a.size();
    int step=min(K,n);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++){
      int now=i;
      for(int j=0;j<step;j++)now=a[now]-1;
      cnt[now]++;
    }
    int ans=1;
    for(int i=0;i<n;i++){
      ans=1LL*ans*(cnt[i]+1)%mod;
    }
    return ans;
  }
};
int main(){
  // freopen("aa.in","r",stdin);
  
  return 0;
}