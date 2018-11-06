#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const long long inf=(long long)1e18;
int p[2],q[2];
long long ans;
void calc(long long x,long long y){
  if(x>300*10000 || y>300*10000)return;
  ans=min(ans,p[1]*x*x+p[0]*x+q[1]*y*y+q[0]*y);
}
int exgcd(int a,int b,int&x,int&y){
  if(!b)return x=1,y=0,a;
  int d=exgcd(b,a%b,y,x);
  y-=a/b*x;
  return d;
}
int main(){
  //freopen("aa.in","r",stdin);
  int a,b,c;
  scanf("%d%d%d",&a,&b,&c);
  scanf("%d%d",&p[0],&p[1]);
  scanf("%d%d",&q[0],&q[1]);
  int x,y;
  int d=exgcd(a,b,x,y);
  if(c%d)return puts("Kuon"),0;
  a/=d;
  b/=d;
  c/=d;
  ans=inf;
  for(int i=-2*maxn;i<2*maxn;i++){
    long long x0=1LL*c*x+1LL*b*i;
    long long y0=1LL*c*y-1LL*a*i;
 
    calc(x0,y0);
  }
  printf("%lld\n",ans);
  return 0;
}