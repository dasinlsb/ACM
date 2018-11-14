#include <bits/stdc++.h>
using namespace std;
const int maxn=205;
int f[maxn],g[maxn];
pair<int,int>pos[10];
int check(int n){
  vector<int>a;
  for(;n;n/=10)a.push_back(n%10);
  reverse(a.begin(),a.end());
  for(int i=1;i<a.size();i++){
    if(pos[a[i]].first<pos[a[i-1]].first || 
      pos[a[i]].second<pos[a[i-1]].second)return 0;
  }
  return 1;
}
int main(){
  freopen("aa.in","r",stdin);
  for(int i=1;i<=3;i++){
    for(int j=1;j<=3;j++){
      pos[(i-1)*3+j]=make_pair(i,j);
    }
  }
  pos[0]=make_pair(4,2);
  for(int i=1;i<=200;i++){
    if(check(i))f[i]=1;
  }
  for(int i=1;i<=200;i++){
    for(int j=0;j<=200;j++){
      if(i-j>=1 && f[i-j])g[i]=i-j;
      if(i+j<=200 && f[i+j])g[i]=i+j;
      if(g[i])break;
    }
  }
  int _;scanf("%d",&_);
  for(;_--;){
    int n;scanf("%d",&n);
    printf("%d\n",g[n]);
  }
  return 0;
}