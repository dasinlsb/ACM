/*
正着做比较困难，因为加入一条边之后需要带回溯的搜索才能确定答案
正着做困难的一个重要原因是题中要求的点集组成条件很严格，反之打破这个条件相对就会容易
考虑反着做，一开始把全部边加进来，然后for一遍全部点，不断地把非法的点及其相邻点删除就是最后一次询问的答案
接下来考虑删除一条边对答案带来的影响，显然和之前的判定过程一样，一旦这条边相连的两个点度数减到kk以下就从它们开始不断地删除非法点即可
时间可以做到线性，不过用set存邻接表更好写
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,m,kk,sum,ans[maxn],del[maxn];
pair<int,int >qe[maxn];
set<int >G[maxn];
void remove(int x){
  if(del[x])return;
  del[x]=1;
  sum--;
  for(int v:G[x]){
    G[v].erase(x);
    if(G[v].size()<kk){
      remove(v);
    }
  }
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&kk);
  for(int i=1;i<=m;i++){
    int x,y;scanf("%d%d",&x,&y);
    qe[i]=make_pair(x,y);
    G[x].insert(y);
    G[y].insert(x);
  }
  sum=n;
  for(int i=1;i<=n;i++)if(G[i].size()<kk){
    remove(i);
  }
  for(int i=m;i;i--){
    ans[i]=sum;
    int x=qe[i].first;
    int y=qe[i].second;
    G[x].erase(y);
    G[y].erase(x);
    if(G[x].size()<kk)remove(x);
    if(G[y].size()<kk)remove(y);
  }
  for(int i=1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
  return 0;
}