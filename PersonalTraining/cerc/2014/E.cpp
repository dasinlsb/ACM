/*
显然在任一时刻合法序列的形态都是中间高两边低
可以用f[i][j]表示已经考虑前i块，显然左半边的状态是j,其中j用二进制数来表示合并后的结果
右半边可以用前缀和直接算出
当左边或右边的二进制表示只有一位，且这一位不低于另一边的最高位时要向另一边合并
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
const int maxm=1<<13;
int n,a[maxn],sum[maxn],bit[maxm+1],maxBit[maxm+1];
int f[maxn][maxm+1],pre[maxn][maxm+1];
char op[maxn][maxm+1];
char ans[maxn];
void up(int i,int j,int s,char c){
  f[i][j]=1;
  pre[i][j]=s;
  op[i][j]=c;
}
int main(){
  freopen("aa.in","r",stdin);
  for(int i=1;i<=maxm;i++){
    bit[i]=bit[i>>1]+i%2;
    int x=i;
    for(;bit[x]>1;x^=(x&-x));
    maxBit[i]=x;
  }
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
      scanf("%d",a+i);
      sum[i]=sum[i-1]+a[i];
    }
    for(int cur=0;cur<=n;cur++){
      memset(f[cur],0,(maxm+1)*sizeof(int));
    }
    f[0][0]=1;
    for(int cur=0;cur<n;cur++){
      for(int sumL=0;sumL<=maxm;sumL++){
        if(!f[cur][sumL])continue;
        int sumR=sum[cur]-sumL;
        if(!((a[cur+1]-1)&sumL)){
          int _sumL=sumL+a[cur+1];
          if(bit[_sumL]==1 && _sumL>=maxBit[sumR]){
            _sumL=0;
          }
          up(cur+1,_sumL,sumL,'l');
        }
        if(!((a[cur+1]-1)&sumR)){
          int _sumL=sumL;
          int _sumR=sumR+a[cur+1];
          if(bit[_sumR]==1 && _sumR>=maxBit[sumL]){
            _sumL=sum[cur+1];
          }
          up(cur+1,_sumL,sumL,'r');
        }
      }
    }
    if(bit[sum[n]]>1 || !f[n][0]){
      puts("no");
      continue;
    }
    ans[n+1]=0;
    for(int cur=n,s=0;cur;cur--){
      ans[cur]=op[cur][s];
      s=pre[cur][s];
    }
    puts(ans+1);
  }

  return 0;
}