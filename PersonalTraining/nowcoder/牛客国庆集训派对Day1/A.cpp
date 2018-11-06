#include <bits/stdc++.h>
using namespace std;

int main(){
  freopen("aa.in","r",stdin);
  int a[6];
  for(int i=0;i<6;i++)scanf("%d",a+i);
  int ans=min(a[0],a[4])+min(a[1],a[5])+min(a[2],a[3]);
  printf("%d\n",ans);
  return 0;
}