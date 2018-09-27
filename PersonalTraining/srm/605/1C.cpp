/*
首先需要一些性质，序列中元素的相对顺序永远不会发生变化
而且对于某个位置i,如果存在另一个位置j使得最终a[j]==a[i]，那么原序列i->j或者j->i的最大值肯定就是P[i]
有了这两个性质就可以dp了，设f[i][last][use]表示前i位，第i位放P[last]，已经进行了use次操作的方案数
直接枚举i+1放哪个数，限制就是上面两条性质，一段相同的数最多只会对use贡献1，再加一维[0/1]记录当前段是否贡献过即可
时间复杂度O(n^4)，可以跳过不少无效状态，常数比较小
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=205;
const int mod=1000*1000*1000+7;
int seg[maxn][maxn];
int f[maxn][maxn][maxn][2];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
class AlienAndPermutation{
public:
int getNumber(vector<int>P,int K){
  int n=P.size();
  P.resize(n+1);
  for(int i=n;i;i--)P[i]=P[i-1];
  P[0]=0;
  for(int i=0;i<=n;i++){
    seg[i][i]=P[i];
    for(int j=i+1;j<=n;j++){
      seg[i][j]=max(seg[i][j-1],P[j]);
    }
  }
  memset(f,0,sizeof(f));
  f[0][0][0][0]=1;
  int ans=0;
  for(int i=0;i<=n;i++){
    for(int last=0;last<=n;last++){
      for(int use=0;use<=K;use++){
        for(int updated=0;updated<2;updated++){
          if(!f[i][last][use][updated])continue;
          if(i==n){
            up(ans,f[i][last][use][updated]);
            continue;
          }
          for(int nxt=max(1,last);nxt<=n;nxt++){
            int seg_mx=nxt<=i+1?seg[nxt][i+1]:seg[i+1][nxt];
            if(seg_mx!=P[nxt])continue;
            up(f[i+1][nxt][use+(nxt==last && !updated || nxt!=last && nxt!=i+1)][nxt==last || nxt!=last && nxt!=i+1],f[i][last][use][updated]);
          }
        }
      }
    }
  }
  return ans;
}
};
int main(){
  // freopen("aa.in","r",stdin);
  int a[]={1};
  int b=1;
  	AlienAndPermutation x;
    printf("ans %d\n",x.getNumber(vector<int>(a,a+1),b));
  return 0;
}
