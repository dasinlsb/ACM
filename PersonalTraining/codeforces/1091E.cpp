/*
https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem
枚举wiki的公式中的k，把不同的k的限制求交即可
对于某个k，讨论一下前k个是否包含d[n+1],可以产生两条不等式取并
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
const pair<int,int> NONE=make_pair(0,-1);
int n,a[maxn],cnt[maxn];
long long sum[maxn];
int find(int l,int v){
  int r=n;
  // printf("find %d %d %d\n",l,r,v);
  for(;l<=r;){
    int mid=l+r>>1;
    if(a[mid]>=v)l=mid+1;
    else r=mid-1;
  }
  return r;
}
pair<int,int> adjust(long long l,long long r){
  if(l<0)l=0;
  if(r>n)r=n;
  return make_pair((int)l,(int)r);
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  sort(a+1,a+1+n);
  reverse(a+1,a+1+n);
  for(int i=1;i<=n;i++){
    sum[i]=sum[i-1]+a[i];
  }
  for(int k=1;k<=n;k++){
    pair<int,int> seg[2];
    seg[0]=NONE;
    int p=find(k+1,k);
    long long lv=sum[k]-1LL*k*(k-1)-1LL*(p-k)*k-(sum[n]-sum[p]);
    if(k>=lv)seg[0]=adjust(lv,a[k]);
    p=find(k,k);
    long long rv=1LL*k*(k-1)-sum[k-1]+1LL*(p-k+1)*k+(sum[n]-sum[p]);
    seg[1]=adjust(a[k],rv);
    sort(seg,seg+2);
    if(seg[0].second>=seg[1].first){
      cnt[seg[0].first]++;
      cnt[max(seg[0].second,seg[1].second)+1]--;
    }else{
      for(int i=0;i<2;i++){
        cnt[seg[i].first]++;
        cnt[seg[i].second+1]--;
      }
    }
  }
  long long rv=1LL*n*(n+1)-sum[n];
  if(rv>n)rv=n;
  if(rv<0)return puts("-1"),0;
  cnt[0]++;
  cnt[rv+1]--;
  vector<int> ans;
  for(int i=0;i<=n;i++){
    if(i)cnt[i]+=cnt[i-1];
    if(cnt[i]==n+1 && (i+sum[n])%2==0){
      ans.push_back(i);
    }
  }
  if(!ans.size())ans.push_back(-1);
  for(int i:ans)printf("%d ",i);
  return 0;
}