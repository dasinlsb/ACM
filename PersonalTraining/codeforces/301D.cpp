/*
由于是排列，合法的值对仅有nlogn，暴力预处理这些值对，然后扫描线过去，都在右端点处计算每个值对的贡献以及答案即可
时间复杂度O(nlog^2n)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,m,a[maxn],pos[maxn],ans[maxn],t[maxn];
vector< pair<int,int> >qry[maxn];
vector<int>need[maxn];

void add(int x,int v){
  for(;x<=n;x+=x&-x)t[x]+=v;
}
int ask(int x){
  int v=0;
  for(;x>0;x-=x&-x)v+=t[x];
  return v;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    pos[a[i]]=i;
  }
  for(int i=1;i<=m;i++){
    int l,r;scanf("%d%d",&l,&r);
    qry[r].push_back(make_pair(l,i));
  }
  for(int i=1;i<=n;i++){
    for(int j=i;j<=n;j+=i){
      int x=pos[i];
      int y=pos[j];
      if(x>y)swap(x,y);
      need[y].push_back(x);
    }
  }
  for(int i=1;i<=n;i++){
    for(int x:need[i])add(x,1);
    for(pair<int,int>x:qry[i])ans[x.second]=ask(i)-ask(x.first-1);
  }
  for(int i=1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
  return 0;
}