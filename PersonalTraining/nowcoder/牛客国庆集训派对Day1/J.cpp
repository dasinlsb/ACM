/*
用栈模拟括号匹配的过程可以发现可以在出栈的时刻确定所有合法区间，而且这些区间要么包含要么不交
剩下的问题就是给定若干个彼此包含或不交的区间，问给定区间是否能被若干个上述区间组合出来
可以在每个给定区间的右端点挂上左端点的位置，每次向左倍增找即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
const int maxk=21;
inline void read(int&x){
  char c;while((c=getchar())<'0'||c>'9');x=c-'0';
  while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';
}
int pre[maxn][maxk];
int a[maxn],pos[maxn],q[maxn];
int main(){
  freopen("aa.in","r",stdin);
  int n,m,qn;
  read(n);read(m);read(qn);
  for(int i=1;i<=n;i++){
    read(a[i]);
    pre[i][0]=i;
  }
  int top=0;
  for(int i=1;i<=n;i++){
    if(a[i]%2==0){
      q[++top]=a[i]>>1;
      pos[top]=i; 
    }
    else{
      if(!top || q[top]!=a[i]/2){
        top=0;
      }else{
        pre[i][0]=pos[top]-1;
        top--;
      }
    }
  }
  for(int j=1;j<maxk;j++){
    for(int i=1;i<=n;i++){
      pre[i][j]=pre[pre[i][j-1]][j-1];
    }
  }
  for(;qn--;){
    int x,y;scanf("%d%d",&x,&y);
    for(int i=maxk-1;i>=0;i--){
      if(pre[y][i]>=x-1)y=pre[y][i];
    }
    if(y==x-1)puts("Yes");
    else puts("No");
  }
  return 0;
}