/*
局面可以转化n个二元组(l_i,r_i)表示第i个robot距离两边最近的exit的距离，二元组可以去重，不影响答案
画一画可以发现某些二元组之间有限制关系，比如，某一个选了左边，另一些可能不能选右边
不妨将所有二元组按a_i升序排列，对于a相同的二元组比如(2,4),(2,3)，显然后者对前者没有任何限制，所以我们可以考虑此时按b_i降序
排列好之后，如果我们从前往后扫，显然右是任何情况都能选的，但是左不一定能选到
具体地，假设当前考虑的二元组为(a_i,b_i)，限制仅来自(a_j,b_j)满足j<i&&b_j>=b_i，这些(a_j,b_j)一旦选了右边，那么(a_i,b_i)就不能选左边
也就是说第i位选左边的前提是这些(a_j,b_j)都选左边，计算并维护这种情况下的方案有一种经典的做法
不妨列出一个二维矩阵,0/1表示选左/右，x表示任选
1xxx
01xx
001x
0001
将之前扫描到的b从上到下升序排列，第i列记录最后一个1在第i行的方案f[i]
那么求[对于所有(a_j,b_j)满足j<i&&b_j>=b_i都选左边]的方案数相当于求这个矩阵从左到右若干列的和
比如b_i==3时相当于要求左下角1*3矩阵全0，即求前3列的答案和
考虑怎么维护这个矩阵，当前二元组(a_i,b_I)选0不会产生修改，选1的话考虑上面这个例子，会在第3，4行之间插入1110，相当于会修改f[4]
区间求和，单点加，树状数组维护即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int mod=1000*1000*1000+7;
int n,m,x[maxn],y[maxn],t[maxn];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void add(int x,int y){
  for(x++;x<maxn;x+=x&-x)up(t[x],y);
}
int ask(int x){
  int y=0;
  for(x++;x>0;x-=x&-x)up(y,t[x]);
  return y;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)scanf("%d",x+i);
  for(int i=1;i<=m;i++)scanf("%d",y+i);
  int p=1;
  vector< pair< int,int > >a;
  vector< int >b;
  for(int i=1;i<=n;i++)if(x[i]>=y[1]&&x[i]<=y[m]){
    for(;y[p]<x[i];p++);
    a.push_back(make_pair(x[i]-y[p-1],x[i]-y[p]));
    b.push_back(y[p]-x[i]);
  }
  sort(a.begin(),a.end());
  a.resize(unique(a.begin(),a.end())-a.begin());
  sort(b.begin(),b.end());
  int ans=1;
  for(int i=0;i<a.size();i++){
    int pos=lower_bound(b.begin(),b.end(),-a[i].second)-b.begin();
    int sum=ask(pos-1)+1;
    up(ans,sum);
    add(pos,sum);
  }
  printf("%d\n",ans);
  return 0;
}