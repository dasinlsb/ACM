/*
预处理每个数的所有质因数
对于每个质数p，预处理所有满足p|a[x]的点x的贡献，也就是x的子树对应dfs序上一段连续区间都可以以x为可能的答案
预处理之后对于一个询问x就可以暴力遍历a[x]的所有质因数，在这些数组中二分找最优，这个预处理可以扫描线解决
由于修改次数很少，对于每个修改a[x]->y都可以暴力重构所有p|a[x]的预处理数组，然后再重构p|y的数组
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxm=2000005;
int n,m,dfn,a[maxn],st[maxn],en[maxn],fa[maxn],dep[maxn],id[maxm];
vector< pair<int,int> >seg[maxn*2],init[maxn*2];
vector<int>G[maxn],prim,use,yue[maxn*2];
bool not_prim[maxm];
struct Node{int op,x,y;}qry[maxn];
void dfs(int x){
  st[x]=++dfn;
  for(int v:G[x])if(v!=fa[x]){
    fa[v]=x;
    dep[v]=dep[x]+1;
    dfs(v);
  }
  en[x]=dfn;
}
void prepare(int p){
    sort(seg[p].begin(),seg[p].end());
    set< pair<int,int> >S;
    pair<int,int>pre=make_pair(1,0);
    for(int i=0;i<seg[p].size();){
      pair<int,int>x=seg[p][i];
      if(x.first-1>=pre.first){
        // if(pre.second!=0)printf("add %d : %d %d\n",p,x.first-1,pre.second);
        init[p].push_back(make_pair(x.first-1,pre.second));
      }
      int j=i;
      for(;j<seg[p].size() && seg[p][j].first==seg[p][i].first;j++){
        int k=seg[p][j].second;
        if(k<0)S.insert(make_pair(dep[-k],-k));
        else S.erase(make_pair(dep[k],k));
      }
      i=j;
      pre.first=x.first;
      pre.second=S.size()?S.rbegin()->second:0;
    }
    // if(pre.second!=0)printf("add %d : %d %d\n",p,n,pre.second);
    if(n>=pre.first){
      assert(pre.second==0);
      init[p].push_back(make_pair(n,pre.second));
    }
}
int main(){
  freopen("aa.in","r",stdin);
  // freopen("mine.out","w",stdout);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    use.push_back(a[i]);
  }
  for(int i=1;i<n;i++){
    int x,y;scanf("%d%d",&x,&y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dep[0]=-1;
  dfs(1);
  for(int i=1;i<=m;i++){
    scanf("%d%d",&qry[i].op,&qry[i].x);
    if(qry[i].op==2){
      scanf("%d",&qry[i].y);
      use.push_back(qry[i].y);
    }
  }
  sort(use.begin(),use.end());
  // for(int x:use)printf("%d ",x);puts("");
  for(int i=0;i<use.size();i++)id[use[i]]=i+1;
  for(int i=1;i<=n;i++)a[i]=id[a[i]];
  for(int i=1;i<=m;i++)if(qry[i].op==2){
    qry[i].y=id[qry[i].y];
  }
  for(int i=2;i<maxm;i++)if(!not_prim[i]){
    if(id[i])yue[id[i]].push_back(prim.size());
    for(int j=i+i;j<maxm;j+=i){
      not_prim[j]=1;
      if(id[j])yue[id[j]].push_back(prim.size());
    }
    prim.push_back(i);
  }
  for(int i=1;i<=n;i++){
    for(int d:yue[a[i]]){
      seg[d].push_back(make_pair(st[i]+1,-i));
      seg[d].push_back(make_pair(en[i]+1,i));
    }
  }
  for(int i=0;i<prim.size();i++){
    prepare(i);
  }
  for(int k=1;k<=m;k++){
    int op=qry[k].op,x=qry[k].x,y=qry[k].y;
    if(op==1){
      int res=0;
      for(int d:yue[a[x]]){
        pair<int,int>t=*lower_bound(init[d].begin(),init[d].end(),make_pair(st[x],-1));
        if(dep[t.second]>dep[res])res=t.second;
      }
      printf("%d\n",res?res:-1);
    }else{
      for(int d:yue[a[x]]){
        init[d].clear();
        seg[d].clear();
        for(int i=1;i<=n;i++)if(i!=x && use[a[i]-1]%prim[d]==0){
          seg[d].push_back(make_pair(st[i]+1,-i));
          seg[d].push_back(make_pair(en[i]+1,i));
        }
        prepare(d);
      }
      a[x]=y;
      for(int d:yue[a[x]]){
        init[d].clear();
        seg[d].clear();
        for(int i=1;i<=n;i++)if(use[a[i]-1]%prim[d]==0){
          seg[d].push_back(make_pair(st[i]+1,-i));
          seg[d].push_back(make_pair(en[i]+1,i));
        }
        prepare(d);
      }
    }
  }
  return 0;
}
/*
-1 1 2 -1 1
*/