/*
考虑对每个f[s]，2<=s<=2k单独计算
对于固定的s，限制来自于所有i,s-i(1<=i,s-i<=k)不能同时选取
先考虑s为奇数的情况，偶数的情况只要花常数时间枚举中间那个是否选即可
我一开始先枚举整个序列分成多少段相同的数，但是复杂度过高且式子难以化简
实际上在外层枚举等价类个数不会简化接下来要处理的限制，内层计算的时候还是要考虑
一种可行的方法是对于不同类别的限制分开处理
假设这些二元组(i,s-i)有t个，可以先枚举从中选i个，方案数是C(t,i)*2^i
这样就把问题转化成x_1+x_2+...+x_i+y_1+y_2+...+y_{k-2*t}==n
要求在x_i>0,y_i>=0的限制下，这个方程的整数解个数，这是个可做的经典问题
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=6005;
const int mod=998244353;
int n,kk;
int fac[maxn],inv[maxn],inv_s[maxn],pw[maxn];
int C(int x,int y){
  if(x<y||x<0)return 0;
  return 1LL*fac[x]*inv_s[y]%mod*inv_s[x-y]%mod;
}
int main(){
  freopen("aa.in","r",stdin);
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv[0]=inv[1]=1;
  for(int i=2;i<maxn;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  inv_s[0]=1;
  for(int i=1;i<maxn;i++)inv_s[i]=1LL*inv_s[i-1]*inv[i]%mod;
  pw[0]=1;
  for(int i=1;i<maxn;i++)pw[i]=2LL*pw[i-1]%mod;
  scanf("%d%d",&kk,&n);
  for(int s=2;s<=2*kk;s++){
    int t=0;
    int f=0;
    int o=(s%2==0);
    for(int i=1;i<s-i;i++){
      if(s-i<=kk)t++;
    }
    //printf("init %d %d %d\n",s,t,o);
    for(int i=0;i<=t;i++){
      int coef=1LL*C(t,i)*pw[i]%mod;
      for(int j=0;j<=o;j++){
        f=(f+1LL*coef*C(n+kk-2*t-o-1-j,i+kk-2*t-o-1))%mod;
      }
    }
    printf("%d\n",f);
  }
  return 0;
}