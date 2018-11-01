/*
首先肯定只需要考虑[1,n]这条主链上的点，连出去的子树可以预处理出走完的期望步数
比较直接的dp是用f[i][j][k]表示当前在i号点，最近的存档点在j，已经用了k次机会，但是转移是很多无序状态套在一起的，不好确定dp顺序
可以考虑把存档的位置作为关键点来dp,用f[i][j]表示已经用了i次机会，当前在点j，转移的话可以枚举下一个存档点，考虑如何求出走到走到下一个存档点的代价
step[i][j]表示从存档点i走到j，(i,j)开区间中没有存档点的期望步数，由step[i][j-1]可以很方便地求出
剩下的就是决策单调的O(n^2)状态O(n)转移的经典问题了，可以用分治O(nlogn)解决
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=705;
const int maxm=1505;
const double inf=1e30;
int n,m,P,deg[maxm];
double len[maxm],step[maxn][maxn],f[maxn][maxn];
vector<int>G[maxm];
void dfs(int x){
  len[x]=1.0;
  for(int v:G[x]){
    dfs(v);
    len[x]+=len[v]/deg[x];
  }
}
void solve(int k,int fl,int fr,int gl,int gr){
  if(fl>fr)return;
  int fm=fl+fr>>1;
  int gm=gl;
  for(int i=gl;i<=gr;i++){
    if(f[k-1][i]+step[i][fm]<f[k-1][gm]+step[gm][fm]){
      gm=i;
    }
  }
  f[k][fm]=f[k-1][gm]+step[gm][fm];
  solve(k,fl,fm-1,gl,gm);
  solve(k,fm+1,fr,gm,gr);
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d%d%d",&n,&m,&P);
    for(int i=1;i<=m;i++){
      G[i].clear();
      deg[i]=0;
      len[i]=0.0;
    }
    for(int i=1;i<=m-n;i++){
      int x,y;scanf("%d%d",&x,&y);
      G[x].push_back(y);
      deg[x]++;
    }
    for(int i=1;i<=n;i++){
      dfs(i);
    }
    for(int i=n;i;i--){
      for(int j=1;j<i;j++){
        step[i][j]=inf;
      }
      for(int j=i+1;j<=n;j++){
        step[i][j]=(1+deg[j-1])*step[i][j-1]+1+deg[j-1]*len[j-1];
        // printf("step %d %d : %.4lf\n",i,j,step[i][j]);
      }
    }
    for(int i=1;i<=P;i++){
      for(int j=1;j<=n;j++){
        f[i][j]=inf;
      }
    }
    f[1][1]=0;
    for(int i=2;i<=P;i++){
      solve(i,1,n,1,n);
    }
    printf("%.4lf\n",f[P][n]);
  }
  return 0;
}