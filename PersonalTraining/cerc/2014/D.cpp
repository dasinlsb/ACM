/*
由于保证合法，所以直接通过bf传递公有的线速度即可，每次传递取相反数
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n,val[maxn],vis[maxn];
struct Node{
  int x,y,r;
  void read(){scanf("%d%d%d",&x,&y,&r);}
}a[maxn];
int gcd(int x,int y){
  return y?gcd(y,x%y):x;
}
int sq(int x){
  return x*x;
}
int touched(int i,int j){
  if(sq(a[i].x-a[j].x)+sq(a[i].y-a[j].y) == sq(a[i].r+a[j].r))return 1;
  return 0;
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
      a[i].read();
      vis[i]=val[i]=0;
    }
    queue<int>q;
    val[1]=a[1].r;
    vis[1]=1;
    q.push(1);
    for(;q.size();){
      int x=q.front();q.pop();
      for(int v=1;v<=n;v++){
        if(vis[v] || !touched(x,v))continue;
        val[v]=-val[x];
        vis[v]=1;
        q.push(v);
      }
    }
    for(int i=1;i<=n;i++){
      if(!val[i]){
        puts("not moving");
        continue;
      }
      int x=abs(val[i]);
      int y=a[i].r;
      int d=gcd(x,y);
      x/=d,y/=d;
      printf("%d",x);
      if(y!=1)printf("/%d",y);
      if(val[i]>0)puts(" clockwise");
      else puts(" counterclockwise");
    }
  }
  return 0;
}