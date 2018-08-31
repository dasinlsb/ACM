/*
题解的做法很妙啊...
考虑删掉一个点降低问题规模，假设删除某个点x以及它的所有出边
假设可以求出剩下的子图的合法答案点集S，讨论一下S是否能通过某条有向边到达x
假设有，那么显然S也是原图的合法解
假设没有，说明x和S相互独立，可以选，而且为了防止x出边连到孤立点，这个x必须选
具体实现可以先按任意顺序扫描所有点，假设当前点x没被删除，将x加入候选点集，同时把x出边连到的点彻底删除
然后反向扫描候选点集，如果当前候选点x可以选就选上，同时如果x的某些出边连到其他候选点，将那些候选点删除
*/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=1000005;
int n,m,ed,fir[maxN];
int del[maxN];
struct Edge{
  int v,nxt;
}e[maxN];
void adde(int x,int y){
  e[++ed].v=y;e[ed].nxt=fir[x];fir[x]=ed;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    adde(x,y);
  }
  for(int x=1;x<=n;x++)if(!del[x]){
    for(int i=fir[x];i;i=e[i].nxt)if(e[i].v>x){
      del[e[i].v]=1;
    }
  }
  vector<int>ans;
  for(int x=n;x;x--)if(!del[x]){
    ans.pb(x);
    for(int i=fir[x];i;i=e[i].nxt){
      del[e[i].v]=1;
    }
  }
  sort(ans.begin(),ans.end());
  printf("%d\n",SZ(ans));
  for(int i=0;i<SZ(ans);i++){
    printf("%d ",ans[i]);
  }
  return 0;
} 