/*
枚举一下两点，两边和一定，肯定越平均越好，正着反着各预处理一下即可
*/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
#define VI vector<int>
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=200005;
const ll inf=(ll)1e15;
int n,a[maxN];
ll b[maxN];
pair<ll,ll>pre[maxN],suf[maxN];
ll Abs(ll x){return x>0?x:-x;}
ll sum(int l,int r){
  return b[r]-b[l-1];
}
int main(){
  freopen("aa.in","r",stdin);
  int i,j;
  scanf("%d",&n);
  for(i=1;i<=n;++i){
    scanf("%d",a+i);
    b[i]=b[i-1]+a[i];
  }
  for(j=1,i=2;i<=n;++i){
    for(;j<i-1&&Abs(sum(j+2,i)-sum(1,j+1))<Abs(sum(j+1,i)-sum(1,j));++j);
    pre[i]=make_pair(sum(1,j),sum(j+1,i));
    //printf("pre %d %lld %lld\n",i,pre[i].fi,pre[i].se);
  }
  for(j=n,i=n-1;i;--i){
    for(;i<j-1&&Abs(sum(i,j-2)-sum(j-1,n))<Abs(sum(i,j-1)-sum(j,n));--j);
    suf[i]=make_pair(sum(j,n),sum(i,j-1));
    //printf("suf %d %lld %lld\n",i,suf[i].fi,suf[i].se);
  }
  ll ans=inf;
  for(i=2;i<=n-2;++i){
    ll x=max(max(pre[i].fi,pre[i].se),max(suf[i+1].fi,suf[i+1].se));
    ll y=min(min(pre[i].fi,pre[i].se),min(suf[i+1].fi,suf[i+1].se));
    ans=min(ans,x-y);
  }
  printf("%lld\n",ans);
  return 0;
}