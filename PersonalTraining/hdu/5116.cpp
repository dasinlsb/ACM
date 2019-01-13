/*
可以O(n^3)做，直接做不好做，可以考虑补集转化
全集答案很好求，预处理f[a][b]表示两臂长分别为a,b时的答案，对于每个点(x,y)求出向上向右最多延伸多少即可
考虑如何减去相交的部分
      |
   |  |
---+--|
   |
---|
任意两个L形相交肯定是这样的形态，可以枚举交点(x,y)
预处理c[0]=(x',y')作为右下角且满足(x'>=x,y'=y)和c[1]=(x'=x,y'<=y)的答案
c[0]=(M+R),c[1]=(M+D),M表示恰好以(x,y)为右下角的L形的答案，R,D分别表示右下角在右边和下边的答案
需要减去的是M^2+2*(ML+MR+LR)
这里的M其实是上面已经预处理出来的f，可以直接用
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=205;
const int maxD=200;

int n,has[maxn][maxn];
int cntU[maxn][maxn],cntL[maxn][maxn],attach[2][maxn][maxn];
int one[maxn][maxn],all[maxn][maxn];
int pn,prim[maxn],mu[maxn],vis[maxn];
int main(){
  freopen("aa.in","r",stdin);
  for(int i=1;i<=maxD;i++){
    for(int j=1;j<=maxD;j++){
      one[i][j]=one[i][j-1];
      if(__gcd(i,j)==1)one[i][j]++;
      all[i][j]=all[i-1][j]+one[i][j];
    }
  }
  int _;
  scanf("%d", &_);
  for(int Case=1;Case<=_;Case++){
    scanf("%d",&n);
    memset(has,0,sizeof has);
    for(int i=0;i<n;i++){
      int x,y;
      scanf("%d%d",&x,&y);
      x=maxD-x+1;
      has[x][y]=1;
    }
    long long sum2=0;
    long long sum=0;
    memset(attach,0,sizeof attach);
    for(int i=1;i<=maxD;i++){
      for(int j=maxD;j;j--){
        if(has[i][j]){
          cntU[i][j]=cntU[i][j+1]+1;
          cntL[i][j]=cntL[i-1][j]+1;
          long long tf=all[cntU[i][j]-1][cntL[i][j]-1];
          sum+=tf;
          sum2+=tf*tf;
          int pre=0;  
          for(int k=cntL[i][j];k;k--){
            pre+=one[k-1][cntU[i][j]-1];
            attach[0][i-k+1][j]+=pre;
          }
          pre=0;
          for(int k=cntU[i][j];k;k--){
            pre+=one[k-1][cntL[i][j]-1];
            attach[1][i][j+k-1]+=pre;
          }
        }else{
          cntU[i][j]=0;
          cntL[i][j]=0;
        }
      }
    }
    long long ans=sum*sum;
    for(int i=1;i<=maxD;i++){
      for(int j=1;j<=maxD;j++)if(has[i][j]){
        long long m2=all[cntU[i][j]-1][cntL[i][j]-1];m2*=m2;
        long long mul=1LL*attach[0][i][j]*attach[1][i][j]-m2;
        mul=mul*2LL+m2;
        ans-=mul;
      }
    }
    printf("Case #%d: %lld\n",Case,ans);
  }


  return 0;
}