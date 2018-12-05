/*
可行的位置肯定会组成0101..这样交错的序列，在每一段中选取一个位置丢掉也同样会把这一段分割成两段独立的交错序列
对所有1<=i<=n预处理长度为i的交错序列的SG值然后暴力枚举先手第一步扔哪个就行了
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=5005;
int n,vis[1<<14],g[maxn],col[maxn],pre[maxn],suf[maxn];
char s[maxn];
int main(){
  freopen("aa.in","r",stdin);
  scanf("%s",s+1);
  n=strlen(s+1);
  for(int k=1;k<=n;k++){
    for(int i=2;i<k;i++){
      vis[g[i-1]^g[k-i]]=k;
    }
    for(g[k]=0;vis[g[k]]==k;g[k]++);
  }
  for(int i=1;i<n;){
    int j=i+1;
    for(;j<n && s[j+1]==s[j-1];j++);
    for(int k=i+1;k<j;k++)col[k]=1;
    i=j;
  }
  int now=0;
  int sum=0;
  for(int i=2;i<=n;i++){
    if(col[i-1]){
      now++;
      pre[i]=sum^g[now+2];
    }else{ 
      sum^=g[now+2];
      now=0;
      pre[i]=sum;
    }
  }
  now=sum=0;
  for(int i=n-1;i;i--){
    if(col[i+1]){
      now++;
      suf[i]=sum^g[now+2];
    }else{
      sum^=g[now+2];
      now=0;
      suf[i]=sum;
    }
  }
  int ans=0;
  for(int i=2;i<n;i++){
    if(col[i] && (pre[i-1]^suf[i+1])==0){
      ans=i;
      break;
    }
  }
  if(ans==0)puts("Second");
  else{
    printf("First\n%d\n",ans);
  }
  return 0;
}