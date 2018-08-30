#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
#define VI vector<int>
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=(1<<18)+5;
int n,a[maxN];
pii f[maxN];
void up(int k,pii&p){
  if(a[k]>a[p.fi])p.se=p.fi,p.fi=k;
  else if(k!=p.fi&&a[k]>a[p.se])p.se=k;
}
int main(){
  freopen("aa.in","r",stdin);
  int i,j;
  scanf("%d",&n);
  for(i=0;i<1<<n;++i){
    scanf("%d",a+i);
    f[i].fi=i;
    f[i].se=1<<n;
  }
  a[1<<n]=0;
  int ans=0;
  for(int k=0;k<1<<n;++k){
    //printf("f %d : %d %d\n",k,f[k].fi,f[k].se);
    for(i=0;i<n;++i)up(f[k].fi,f[k|1<<i]);
    if(k){
      ans=max(ans,a[f[k].fi]+a[f[k].se]);
      printf("%d\n",ans);
    }
  }
  return 0;
}