/*
首先砖块下落的顺序交换肯定对答案没有影响
然后有砖块的位置肯定不需要考虑
考虑dp用f[i]表示只考虑前i个，第i个没有砖块直接下落，而且也不会由左边的砖块移动得到的方案数
可以枚举左边最近的空砖块位置j转移，保证(j,i)全黑即可，也就是这个区间落的砖块数恰好等于区间长度
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
const int mod=1e9+7;
int n,m,a[maxn],s[maxn];
int f[maxn],g[maxn*2];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int x;scanf("%d",&x);
    a[x]++;
  }
  for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
  g[0+maxn]=1;
  for(int i=1;i<=n+1;i++)if(a[i]==0){
    f[i]=g[s[i-1]-(i-1)+maxn];
    up(g[s[i]-i+maxn],f[i]);
  }
  printf("%d\n",f[n+1]);
  return 0;
}