/*
n为奇数时可以直接构造出来
n为偶数的时候递归构造，假设已经构造好n/2的答案
左上和右下放(x+n/2|x<-a(n/2))
右上那个沿主对角线翻折一下之后就和左下完全对称了
然后把右上按值循环移位即可
n==4要手动构造
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int a[maxn][maxn];
int solve(int n){
  if(n==2)return 0;
  if(n==4){
    for(int i=0;i<4;i++){
      a[0][i]=i;
      a[1][i]=(2+i)%4;
      a[2][i]=(3-i);
      a[3][i]=(1-i+4)%4;
    }
    return 1;
  }
  if(n&1){
    for(int i=0;i<n;i++){
      int k=(n-i)%n;
      for(int j=0;j<n;j++,k=(k+1)%n){
        a[i][j]=k;
      }
    }
    return 1;
  }
  if(!solve(n/2))return 0;
  for(int i=0;i<n/2;i++){
    for(int j=0;j<n/2;j++){
      a[i+n/2][j]=a[i][j+n/2]=a[i][j];
      a[i+n/2][j+n/2]=(a[i][j]+=n/2);
    }
  }
  for(int i=0;i<n/2;i++){
    for(int j=i+1;j<n/2;j++){
      swap(a[i][n/2+j],a[j][n/2+i]);
    }
  }
  for(int i=0;i<n/2;i++){
    for(int j=0;j<n/2;j++){
      a[i][j+n/2]=(a[i][j+n/2]+1)%(n/2);
    }
  }
  return 1;
}
int test(int n){
  static int vis[maxn];
  for(int i=0;i<n;i++){
    memset(vis,0,sizeof vis);
    for(int j=0;j<n;j++){
      if(vis[a[i][j]])return 0;
      vis[a[i][j]]=1;
    }
    memset(vis,0,sizeof vis);
    for(int j=0;j<n;j++){
      if(vis[a[j][i]])return 0;
      vis[a[j][i]]=1;
    }
  }
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(a[i][j]==a[j][i])return 0;
    }
  }
  return 1;
}
int main(){
  // freopen("aa.in","r",stdin);
  int n;scanf("%d",&n);
  if(!solve(n))return puts("-1"),0;
  assert(test(n));
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      printf("%d ",a[i][j]+1);
    }
    puts("");
  }
  return 0;
}