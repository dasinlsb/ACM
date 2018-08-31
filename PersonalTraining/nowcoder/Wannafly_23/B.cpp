/*
赛后发现是一道非常基础的Nim和，不过真的好久没打了忘得差不多了
对于取的个数没有限制的多堆石子的游戏，每一堆的sg[x]=x，具体推导的话是x可以转移到0...x-1任意一个数，取mex就行
这道题的推法和上述游戏完全一样，检查一下每个状态能转移到的所有状态的sg函数，将这些sg函数值取mex即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
vector< int >q[maxn];
int a[maxn],f[maxn],vis[maxn];
int main(){
  freopen("aa.in","r",stdin);
  for(int i=1;i<maxn;i++){
    for(int j=i;j<maxn;j+=i){
      q[j].push_back(i);
    }
  }
  for(int i=1;i<maxn;i++){
    for(int j=0;j<q[i].size();j++)vis[f[i-q[i][j]]]=i;
    for(f[i]=0;vis[f[i]]==i;f[i]++);
  }
  int n;scanf("%d",&n);
  int tot=0;
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    tot^=f[a[i]];
  }
  int ans=0;
  for(int i=1;i<=n;i++){
    for(int j=0;j<q[a[i]].size();j++){
      if((tot^f[a[i]]^f[a[i]-q[a[i]][j]])==0){
        ans++;
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}