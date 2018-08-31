/*
考虑枚举所有n^2个点对构成的向量，方便起见将这些向量的端点平移到原点，显然不会失去最优解
假设将枚举的某条向量作为三角形的底，那么剩下的问题实际上只要在全体点集中找到和这个向量距离最大的点即可
如果每次重新排序肯定是无法接受的，但是如果我们是按照顺时针或逆时针来枚举这些向量，假设一开始这些点都已经按距离排好序，那么每次点的顺序的变化是很小的
画一下可以发现假设当前枚举的点对是(i,j)，rank[i]和rank[j]在这一轮之后的顺序是交换的，其他点的位置都没有变

*/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=2005;
int n;
ll S;
int rk[maxN],pos[maxN];
struct P{
  ll x,y;
  P(){}
  P(ll _x,ll _y){x=_x,y=_y;}
  void read(){scanf("%I64d%I64d",&x,&y);}
  void print(){printf("%I64d %I64d\n",x,y);}
  P operator-(P t){return P(x-t.x,y-t.y);}
}p[maxN];;
ll cross(P a,P b){
  return a.x*b.y-a.y*b.x;
}
pair<double,int>d[maxN*maxN];
void print(int a,int b,int c){
  puts("Yes");
  p[a].print();
  p[b].print();
  p[c].print();
  exit(0);
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%I64d",&n,&S);S<<=1;
  for(int i=1;i<=n;i++){
    p[i].read();
  }
  sort(p+1,p+1+n,[&](P a,P b){
    return a.y==b.y?a.x<b.x:a.y<b.y;
  });
  int m=0;
  for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
      d[++m]=make_pair(atan2((p[j]-p[i]).y,(p[j]-p[i]).x),i<<11|j);
    }
  }
  sort(d+1,d+1+m,[&](pair<double,int>a,pair<double,int>b){
    return a.fi<b.fi;
  });
  for(int i=1;i<=n;i++){
    rk[i]=pos[i]=i;
  }
  for(int i=1;i<=m;i++){
    int a=d[i].se>>11;
    int b=d[i].se&2047;
    int l=1+1,r=rk[a]-1;
    for(;l<=r;){
      int mid=(l+r)/2;
      int k=pos[mid];
      ll _S=cross(p[a]-p[k],p[b]-p[k]);
      if(_S==S)print(a,b,k);
      if(_S>S)l=mid+1;
      else r=mid-1;
    }
    l=rk[a]+1+1,r=n;
    for(;l<=r;){
      int mid=(l+r)/2;
      int k=pos[mid];
      ll _S=cross(p[a]-p[k],p[b]-p[k]);
      if(_S==S)print(a,b,k);
      if(_S>S)r=mid-1;
      else l=mid+1;
    }
    swap(rk[a],rk[b]);
    swap(pos[rk[a]],pos[rk[b]]);
  }
  puts("No");
  return 0;
}