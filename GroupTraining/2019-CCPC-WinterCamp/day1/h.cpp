/*
一种做法是考虑当前区间[l,r]中被最小值分割出的若干区间，这些区间都可以看作是子问题，需要继承的状态就是在下方最高染色的高度
用f[l][r][low][k]表示上述过程中被分割出的某个区间[l,r]下方最高的染色高度为low,恰好使用k次染色的最大面积
(l,r)状态数显然为O(n)，所有标号一下可以用O(n^3)的空间存储这些状态
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,kk,a[maxn],aa[maxn],b[maxn][maxn],pos[1000005];
int scnt,sid[maxn][maxn];
bool vis[maxn*2][maxn];
long long f[maxn*2][maxn][maxn];
void dfs(int l,int r,int low){
  static long long g[2][maxn];
  if(!sid[l][r]){
    sid[l][r]=++scnt;
  }
  int x=sid[l][r];
  if(vis[x][low])return;
  vis[x][low]=1;
  vector<int> sub;
  for(int i=l;i<=r;i++){
    if(a[i]!=b[l][r]){
      int j=i;
      for(;j<=r && a[j]!=b[l][r];j++); j--;
      int _low=pos[b[l][r]];
      dfs(i,j,_low);
      dfs(i,j,low);
      sub.push_back(sid[i][j]);
      i=j;
    }
  }
  memset(g,0,sizeof g);
  for(int y:sub){
    for(int k=kk;k;k--){
      for(int _k=1;_k<=k;_k++){
        g[0][k]=max(g[0][k],g[0][k-_k]+f[y][low][_k]);
        g[1][k]=max(g[1][k],g[1][k-_k]+f[y][pos[b[l][r]]][_k]);
      }
    }
  }
  for(int k=1;k<=kk;k++){
    f[x][low][k]=max(g[0][k],g[1][k-1]+(b[l][r]-aa[low])*(r-l+1));
  }
}
int main(){
  freopen("input.txt","r",stdin);
  scanf("%d%d",&n,&kk);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    aa[i]=a[i];
  }
  sort(aa+1,aa+1+n);
  for(int i=1;i<=n;i++){
    pos[aa[i]]=i;
  }
  for(int i=1;i<=n;i++){
    b[i][i]=a[i];
    for(int j=i+1;j<=n;j++){
      b[i][j]=min(b[i][j-1],a[j]);
    }
  }
  dfs(1,n,0);
  long long ans=0;
  for(int i=1;i<=kk;i++){
    ans=max(ans,f[sid[1][n]][0][i]);
  }
  printf("%lld\n",ans);
  return 0;
}