/*
想要用dp或是其他一些方法保留操作过程中序列的信息十分困难，可以单独考虑每个点对
设f[i][j]表示当前p_i>p_j的概率，每次操作(a,b)只会影响{a,b}->{1,2..n}的f,直接暴力修改，最后累加一下每个点对对答案的贡献即可

*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int a[maxn];
double f[maxn][maxn];
int main(){
  freopen("aa.in","r",stdin);
  int n,m;scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)if(a[i]>a[j]){
      f[i][j]=1.0;
    }
  }
  for(int cur=1;cur<=m;cur++){
    int x,y;scanf("%d%d",&x,&y);
    for(int i=1;i<=n;i++)if(i!=x && i!=y){
      double tmp=0.5*(f[x][i]+f[y][i]);
      f[x][i]=f[y][i]=tmp;
      f[i][x]=f[i][y]=1.0-tmp;
    }
    f[x][y]=f[y][x]=0.5;
  }
  double ans=0;
  for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
      ans+=f[i][j];
      // printf("f %d %d %.4lf\n",i,j,f[i][j]);
    }
  }
  printf("%.8lf\n",ans);
  return 0;
}