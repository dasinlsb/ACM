/*
求一次异或前缀和{sum}之后，相当于对于每个1<=i<=n,求(sum_i^sum_j)+sum_j最大
枚举一下0/1发现，相当于在sum_i二进制位的所有0放置mask，若只看这些位，要使sum_j最大
可以预处理g[S]表示二进制位包含S的sum_i最早出现在g[S]这个位置
然后从高位到低逐位确定即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;

int n,a[maxn];
int g[1<<20];
inline void cmin(int&x,int y){
  if(y<x)x=y;
}
int main(){
  // freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    a[i]^=a[i-1];
  }
  int ALL=(1<<20)-1;
  for(int S=0;S<=ALL;S++){
    g[S]=n+1;
  }
  for(int i=0;i<=n;i++){
    cmin(g[a[i]],i);
  }
  for(int S=ALL;~S;S--){
    for(int i=0;i<20;i++)if(S>>i&1)cmin(g[S^(1<<i)],g[S]);
  }
  for(int i=1;i<=n;i++){
    int S=0;
    for(int j=19;~j;j--)if((~a[i]>>j&1) && g[S|1<<j]<=i){
      S|=1<<j;
    }
    printf("%d ",a[i]+S*2);
  }
  return 0;
}