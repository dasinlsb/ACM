#include <bits/stdc++.h>
using namespace std;

const int maxn=1000005;
int n,m,a[maxn];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  sort(a+1,a+1+n);
  int ans=n;
  for(int i=1;i<n;i++){
    if(abs(a[i]-a[i+1])<=m){
      ans--;
    }
  }
  printf("%d\n",ans);
  return 0;
}