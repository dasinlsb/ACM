/*
每一段黑白的比例肯定就是全局黑白的比例，所以可以直接扫，每次加入颜色c之后如果可以分离出可行区间的话肯定是把另一张颜色用完，然后颜色c留下若干个，注意这个若干个不能超过这一轮加入的颜色c的个数
中间为了避免浮点误差要把除法改成乘法，会爆long long
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;

int n,color[maxn],cnt[maxn];
long long total[2],now[2];
struct Num{
  const long long B=1e9;
  long long a[4];
  int n;
  Num(){n=0;memset(a,0,sizeof a);}
  Num(long long x){for(n=0;x;x/=B)a[n++]=x%B;}
  Num operator*(Num t){
    Num res;
    res.n=n+t.n-1;
    for(int i=0;i<n;i++){
      for(int j=0;j<t.n;j++){
        res.a[i+j]+=a[i]*t.a[j];
      }
    }
    for(int i=0;i<res.n;i++){
      res.a[i+1]+=res.a[i]/B;
      res.a[i]%=B;
    }
    if(res.a[res.n])res.n++;
    return res;
  }
  long long operator /(long long t){
    long long res=0;
    long long s=0;
    for(int i=n-1;i>=0;i--){
      s=s*B+a[i];
      res=res*B+s/t;
      s%=t;
    }
    if(s)return -1;
    return res;
  }
  bool operator >=(Num t){
    for(int i=3;i>=0;i--){
      if(a[i]>t.a[i])return 1;
      if(a[i]<t.a[i])return 0;
    }
    return 1;
  }
  void print(){
    printf("%d\n",a[0]);
  }
};
int main(){
  freopen("aa.in","r",stdin);
  char str[4];
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    memset(total,0,sizeof total);
    memset(now,0,sizeof now);
    for(int i=1;i<=n;i++){
      scanf("%d%s",cnt+i,str);
      color[i]=str[0]=='W';
      total[color[i]]+=cnt[i];
    }
    if(!total[0]){
      printf("%I64d\n",total[1]);
      continue;
    }
    if(!total[1]){
      printf("%I64d\n",total[0]);
      continue;
    }
    int ans=0;
    for(int p=1;p<=n;p++){
      int c=color[p];
      now[c]+=cnt[p];
      if(now[0] && now[1]){
        if(Num(now[c])*Num(total[c^1])>=Num(now[c^1])*Num(total[c])){
          long long need=Num(total[c])*Num(now[c^1])/total[c^1];
          if(~need && now[c]-need<=cnt[p]){
            now[c]-=need;
            now[c^1]=0;
            ans++;
          }
        }
      }
    }
    printf("%d\n",ans);
  }
  return 0;
}