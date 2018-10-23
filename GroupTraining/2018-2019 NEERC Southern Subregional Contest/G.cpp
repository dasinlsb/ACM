/*
枚举一下终点ed，然后分别从ed->1,ed+1->n以及ed-1->1,ed->n合并检验一下是否合法
以终点左边为例，每一个后缀可以用二元组(x,y)表示至少需要x才能走，走了之后改变y
一旦遇到英雄，如果y>=0，那么说明这个后缀是十分安全的，英雄的初始hp没有影响，只要可以走就走就行了
如果y<0，那么这段后缀是劣的，也是能走就走
这些必须走的英雄打个标记，这些先顺序输出，剩下的任意即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=105;
const int maxm=1000005;
int n,m;
int at[maxn],a[maxn],tag[maxn];
pair<int,int>init[maxn],hero[maxn];

void up(pair<int,int>&now,int i){
  if(at[i]){
    if(a[i]>=now.first && a[i]+now.second>=0){
      tag[i]=1;
      now=make_pair(0,0);
    }
  }else{
    now.first=max(now.first-a[i],0);
    now.second+=a[i];
  }
}
int brute(int pos,int dir){
  pair<int,int>now=init[pos];
  if(dir==-1){
    for(int i=pos-1;i>0;i--){
      up(now,i);
    }
    return pos<=hero[1].first || tag[hero[1].first];
  }else{
    for(int i=pos+1;i<=n;i++){
      up(now,i);
    }
    return pos>=hero[m].first || tag[hero[m].first];
  }
}
void output(int pos){

}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int x,y;scanf("%d%d",&x,&y);
    at[x]=i;a[x]=y;
    hero[i]=make_pair(x,y);
  }
  sort(hero+1,hero+1+m);
  for(int i=1;i<=n;i++){
    int x;scanf("%d",&x);
    if(!at[i])a[i]=x;
  }
  for(int i=1;i<=n;i++){
    if(!at[i])init[i]=make_pair(max(-a[i],0),a[i]);
  }
  for(int ed=1;ed<=n;ed++){
    memset(tag,0,sizeof(tag));
    if(brute(ed,-1) && brute(ed+1,1)){
      if(hero[1].first>ed)ed++;
      printf("%d\n",ed);
      vector<int>ans;
      for(int i=ed;i;i--)if(tag[i])ans.push_back(at[i]);
      for(int i=ed+1;i<=n;i++)if(tag[i])ans.push_back(at[i]);
      for(int i=1;i<=n;i++)if(at[i] && !tag[i])ans.push_back(at[i]);
      for(int i:ans)printf("%d ",i);
      return 0;
    }
  }
  puts("-1");
  return 0;
}