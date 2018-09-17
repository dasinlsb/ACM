/*
每个格子选或不选记为1/0,那么行和列的限制可以写成2*n个异或方程
对于值的限制可以对每个质因数分开考虑，对于每个质数p，所有以p为质因数的位置的异或和必须为0
方程个数不会很多，答案就是2^{自由元个数},注意判无解的情况
有个小优化，如果某个质数p只在一个元素中出现过，那么可以直接确定这个值是0，方程个数可以减少大概一半
不过没有优化也能直接跑过
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=25;
const int maxm=400000;
const int mod=1000*1000*1000+7;
map<int,vector<int> >num;
int np,vis[maxm],prim[maxm];
int a[3000][405];
class PerfectSquare{
public:
int ways(vector<int>x){
  memset(a,0,sizeof(a));
  int n2=x.size();
  int n=1;
  for(;n*n<n2;n++);
  int m=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      a[m][i*n+j]=1;
    }
    a[m][n2]=1;
    m++;
  }
  for(int j=0;j<n;j++){
    for(int i=0;i<n;i++){
      a[m][i*n+j]=1;
    }
    a[m][n2]=1;
    m++;
  }
  for(int i=2;i<maxm;i++){
    if(!vis[i])prim[++np]=i;
    for(int j=1;j<=np && i*prim[j]<maxm;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0){
        break;
      }
    }
  }
  for(int i=0;i<n2;i++){
    int val=x[i];
    for(int j=1;j<np && prim[j]<=val;j++)if(val%prim[j]==0){
      int cnt=0;
      for(;val%prim[j]==0;val/=prim[j])cnt^=1;
      if(cnt){
        num[prim[j]].push_back(i);
      }
    }
    if(val!=1){
      num[val].push_back(i);
    }
  }
  for(auto&item:num){
    for(int i:item.second){
      a[m][i]=1;
    }
    a[m][n2]=0;
    m++;
  }
  int r=0,c=0;
  int free_x=n2;
  for(;c<n2&&r<m;c++){
    int k=-1;
    for(int j=m-1;j>=r;j--)if(a[j][c])k=j;
    if(k==-1){
      continue;
    }
    for(int j=c;j<=n2;j++)swap(a[k][j],a[r][j]);
    for(int j=r+1;j<m;j++)if(a[j][c]){
      for(int k=c;k<=n2;k++)a[j][k]^=a[r][k];
    }
    r++;
    free_x--;
  }
  for(;r<m;r++)if(a[r][n2])return 0;
  int ans=1;
  for(;free_x--;)ans=2LL*ans%mod;
  return ans;
}
};
int main(){
  // freopen("aa.in","r",stdin);
  int a[]=	
    	
{2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2}

;
  int ans=ways(vector<int>(a,a+25));
  printf("%d\n",ans);
  return 0;
}