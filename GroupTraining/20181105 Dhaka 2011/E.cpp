/*
原问题的划分连通块的过程可以看作划分两行1-n的排列，两行中的数分别对应点的行和列
为了避免重复计数，可以强制规定第一行的所有划分的第一个数必须是块内最小，对应原图就是从连通块的行号最小的那个开始计数，但是行号最小的有两个，所以每个连通块的答案还要除以2
显然对第一行做这样的限制之后第二行不会受到任何限制，最后全排列即可，现在单独考虑第一行排列的划分
f[i][j]表示i个连通块,1-j的排列的答案
为了避免重复计数，可以枚举包含1的那个连通块的大小为k，那么可以得到如下转移
f[i][j]=\sum_{2<=k<=j-2}f[i-1][j-k]*C(j-1,k-1)*(k-1)!
这个可以前缀和优化到O(nk)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxk=55;
const int maxn=100005;
const int mod=1e9+7;
int sum[maxn],f[maxk][maxn];
int fac[maxn],inv[maxn],inv2[maxk];
int main(){
  freopen("aa.in","r",stdin);
  fac[0]=1;
  for(int i=1;i<maxn;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv[0]=inv[1]=1;
  for(int i=2;i<maxn;i++)inv[i]=mod-1LL*mod/i*inv[mod%i]%mod;
  for(int i=1;i<maxn;i++)inv[i]=1LL*inv[i]*inv[i-1]%mod;
  inv2[0]=1;
  for(int i=1;i<maxk;i++)inv2[i]=1LL*inv2[i-1]*inv[2]%mod;
  for(int i=2;i<maxn;i++){
    f[1][i]=fac[i-1];
  }
  for(int i=2;i<maxk;i++){
    for(int j=1;j<maxn;j++){
      sum[j]=(sum[j-1]+1LL*f[i-1][j]*inv[j])%mod;
    }
    for(int j=2*i;j<maxn;j++){
      f[i][j]=(f[i][j]+1LL*fac[j-1]*sum[j-2])%mod;
    }
  }
  for(int i=1;i<maxk;i++){
    for(int j=1;j<maxn;j++){
      f[i][j]=1LL*f[i][j]*fac[j]%mod*inv2[i]%mod;
    }
  }
  int _;scanf("%d",&_);
  for(int Case=1;Case<=_;Case++){
    int n,k;scanf("%d%d",&n,&k);
    printf("Case %d: %d\n",Case,f[k][n]);
  }
  return 0;
}