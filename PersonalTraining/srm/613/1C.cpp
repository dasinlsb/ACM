/*
把left和right分开dp会导致相交部分无法合并，可以把两个部分合起来考虑
如果只有left，假设我们从左到右考虑，在途中放棋子肯定是会产生后效性的，所以对于每一行i，要在扫描到left[i]这一列的时候才能决定棋子的摆放
在到达left[i]之前可以做的[关于放棋子的决策]是[打算将要放多少个棋子],这样只要在left[i]处算一下排列数即可
如果只有right，假设也是从左到右考虑，之前遇到到的所有right[i]都可以当作放棋子的决策位置
合起来就是f[i][j][k]表示前i列，left部分打算放但还没放j个，right部分有k行可以放棋子
转移就直接枚举这一列是否放棋子，如果放棋子的话是放在空位还是left还是right即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
const int maxm=205;
const int mod=1000*1000*1000+7;
int fac[maxn],inv[maxn];
int l_end[maxm],r_start[maxm],empty_cnt[maxm];
int f[maxm][maxn][maxn];
class TaroCheckers{
public:
inline void update(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int A(int x,int y){
  if(x<y)return 0;
  return 1LL*fac[x]*inv[x-y]%mod;
}
int getNumber(vector<int>left,vector<int>right,int M){
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv[0]=inv[1]=1;
  for(int i=2;i<maxn;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  for(int i=1;i<maxn;i++)inv[i]=1LL*inv[i-1]*inv[i]%mod;
  int n=left.size();
  memset(l_end,0,sizeof(l_end));
  memset(r_start,0,sizeof(r_start));
  memset(empty_cnt,0,sizeof(empty_cnt));
  for(int i=0;i<n;i++){
    l_end[left[i]]++;
    r_start[M-right[i]+1]++;
    for(int j=left[i]+1;j<M-right[i]+1;j++){
      empty_cnt[j]++;
    }
  }
  memset(f,0,sizeof(f));
  f[0][0][0]=1;
  for(int i=0;i<M;i++){
    for(int j=0;j<=n;j++){
      for(int k=0;k<=n;k++)if(f[i][j][k]){
        int _j=j-l_end[i+1];
        int _k=k+r_start[i+1];
        if(_j>=0){
          update(f[i+1][_j][_k],1LL*f[i][j][k]*A(j,l_end[i+1])%mod);
        }
        if(_j+1>=0){
          update(f[i+1][_j+1][_k],1LL*f[i][j][k]*A(j+1,l_end[i+1])%mod);
        }
        if(_j>=0 && _k-1>=0){
          update(f[i+1][_j][_k-1],1LL*f[i][j][k]*A(j,l_end[i+1])*_k%mod);
        }
        if(_j>=0){
          update(f[i+1][_j][_k],1LL*f[i][j][k]*A(j,l_end[i+1])*empty_cnt[i+1]%mod);
        }
      }
    }
  }
  return f[M][0][0];
}
};
int main(){
  // int L[]={3, 37, 26, 50, 8, 3, 38, 15, 58, 47, 35, 8, 27, 22, 5};
  // int R[]={19, 26, 62, 15, 84, 13, 6, 46, 22, 53, 23, 8, 29, 55, 6};
  // int ans=getNumber(vector<int>(L,L+15),vector<int>(R,R+15),102);
  // printf("%d\n",ans);
  return 0;
}