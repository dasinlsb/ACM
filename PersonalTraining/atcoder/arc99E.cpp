/*
原图中存在的边无法确定额外的信息，但是原图中没有的边一定能保证两端点属于不同颜色
dfs的同时将点黑白染色，如果没有冲突，最后得到的是若干个联通块
两个点不同的联通块之间之所以不连通，是因为他们之间的边是满的
说明联通块之间相互独立，接下来问题转化为给出若干个联通块，每个联通块已经被分成两份，要求将每块的两份分别黑白染色，使得全局黑*全局白尽可能大
显然黑白总数是n，即要求黑白总数尽可能接近，可以dp,f[i][j]表示已经处理了前i块，当前黑白之差为j是否有可能
最后减去重复部分即可
时间复杂度O(n^2)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxN=705;
int n,m,tot,g[maxN][maxN],col[maxN];
int now[maxN][2],bel[maxN],f[maxN][maxN*2];
int dfs(int x){
  bel[x]=tot;
  now[tot][col[x]]++;
  for(int i=1;i<=n;++i)if(i!=x&&!g[x][i]){
    int v=i;
    if(col[v]+col[x]==1)continue;
    if(col[v]==col[x])return 0;
    col[v]=col[x]^1;
    if(!dfs(v))return 0;
  }
  return 1;
}
int main(){
  freopen("aa.in","r",stdin);
  int i,j;
  scanf("%d%d",&n,&m);
  for(i=1;i<=m;++i){
    int x,y;
    scanf("%d%d",&x,&y);
    g[x][y]=g[y][x]=1;
  }
  memset(col,-1,sizeof(col));
  for(i=1;i<=n;++i)if(col[i]==-1){
    ++tot;col[i]=1;
    if(!dfs(i))return puts("-1"),0;
  }
  f[0][n]=1;
  for(i=0;i<tot;++i){
    //printf("blk %d : %d %d\n",i+1,now[i+1][0],now[i+1][1]);
    int d=now[i+1][0]-now[i+1][1];
    for(j=-n;j<=n;++j)if(f[i][j+n]){
      f[i+1][j-d+n]=1;
      f[i+1][j+d+n]=1;
    }
  }
  for(i=0;!f[tot][i+n]&&!f[tot][-i+n];++i);
  //printf("delta %d\n",i);
  assert((n-i)%2==0);
  int x=(n-i)/2;
  int y=x+i;
  int ans=x*y;
  //printf("ans1 : %d\n",ans);
  for(i=1;i<=n;++i){
    for(j=i+1;j<=n;++j){
      if(!g[i][j]&&bel[i]==bel[j]&&col[i]+col[j]==1)--ans;
    }
  }
  printf("%d\n",m-ans);
  return 0;
}