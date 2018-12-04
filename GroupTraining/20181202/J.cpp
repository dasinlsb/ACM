/*
设a[],b[]分别表示字符串的前缀0和前缀1个数
相当于求
满足 b[r]-b[l-1]<=K
最大化 a[r]-a[l-1]+min(K-(b[r]-b[l-1]),a[n]-(a[r]-a[l-1]))
即min(a[n],cnt[0]-cnt[1]+K)最大化，cnt[0/1]分别表示区间内0/1的个数
单调队列搞搞
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,a[maxn],b[maxn],q[maxn];
char s[maxn];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%s",s+1);
  n=strlen(s+1);
  for(int i=1;i<=n;i++){
    a[i]=a[i-1]+(s[i]=='0');
    b[i]=b[i-1]+(s[i]=='1');
  }
  int qn;scanf("%d",&qn);
  for(;qn--;){
    int kk;scanf("%d",&kk);
    int ans=0;
    int h=0,t=-1;
    q[++t]=0;
    for(int i=1;i<=n;i++){
      for(;h<=t && a[i]-b[i]<a[q[t]]-b[q[t]];t--);
      q[++t]=i;
      for(;h<=t && b[i]-b[q[h]]>kk;h++);
      if(h>t)continue;
      ans=max(ans,a[i]-b[i]-(a[q[h]]-b[q[h]])+kk);
    }
    ans=min(ans,a[n]);
    printf("%d\n",ans);
  }
  return 0;
}