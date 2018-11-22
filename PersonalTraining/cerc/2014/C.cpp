#include <bits/stdc++.h>
using namespace std;
int n;
void output(int l,int r){
  r=l+r-1;
  printf("%d = ",n);
  for(int i=l;i<r;i++)printf("%d + ",i);
  printf("%d\n",r);  
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    int find=0;
    for(int i=2;i*i+i<=2*n;i++){
      if(2*n%i)continue;
      int s=2*n/i+1-i;
      if(s%2)continue;
      find=1;
      output(s>>1,i);
      break;
    }
    if(!find)puts("IMPOSSIBLE");
  }

  return 0;
}