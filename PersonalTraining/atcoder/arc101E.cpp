/*
如果直接用树形dp计算合法的方案,涉及到子树之间有多少pair可以匹配，另外有多少要贡献到父亲，复杂度十分高
考虑容斥，f[S]表示有S这个边集中的边没有被任何一条路径经过而其他边任意，的方案数
对于一个给定的S，显然把S中的边全部移除后每个联通块答案独立
设某个联通块大小为k,当k为奇数时这个联通块必定没有合法匹配，方案为0
当k为偶数时，假设联通块内的点依次为1,2,3...k,从左到右考虑每个未匹配点有多少种可选的匹配方案，答案即(i-1)*(i-3)*(i-5)*...*1
剩下的问题显然也可以用树形dp解决，设f[x][i][0/1]表示x子树，树顶即x所在联通块有i个点，删边数的奇偶性为0/1的方案数
这个dp有一种比较方便的写法，假设当前在x，某个儿子为v，如果删掉(x,v)那么第三维的奇偶性会反转，否则不变
答案的正负性可以在转移时维护，不必记录第三维
在转移的时候把卷积上界用size压住这个dp就可以做到O(n^2)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=5005;
const int mod=1000*1000*1000+7;
int n,ed,fir[maxn],sz[maxn];
int a[maxn],f[maxn][maxn],g[maxn];
struct Edge{
  int v,nxt;
}e[maxn*2];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void adde(int x,int y){
  e[++ed].v=y;e[ed].nxt=fir[x];fir[x]=ed;
}
void dfs(int x,int y){
  sz[x]=1;
  f[x][1]=1;
  for(int i=fir[x];i;i=e[i].nxt)if(e[i].v!=y){
    dfs(e[i].v,x);
    for(int j=1;j<=sz[x];j++){
      g[j]=f[x][j];
      f[x][j]=0;
    }
    for(int j=1;j<=sz[x];j++){
      for(int k=1;k<=sz[e[i].v];k++){
        up(f[x][j+k],1LL*g[j]*f[e[i].v][k]%mod);
        up(f[x][j],mod-1LL*g[j]*f[e[i].v][k]%mod*a[k]%mod);
      }
    }
    sz[x]+=sz[e[i].v];
  }
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<n;i++){
    int x,y;scanf("%d%d",&x,&y);
    adde(x,y);adde(y,x);
  }
  a[0]=1;
  for(int i=2;i<=n;i+=2)a[i]=1LL*a[i-2]*(i-1)%mod;
  dfs(1,0);
  int ans=0;
  for(int i=1;i<=n;i++){
    up(ans,1LL*f[1][i]*a[i]%mod);
  }
  printf("%d\n",ans);
  return 0;
}