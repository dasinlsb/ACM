/*
一个比较直接的想法是f[i][S]表示已经确定i位，且前i位和原串的前j位的lcs压成S
把相邻位的lcs差分一下就可以得到一个0/1序列，可以用2^n的状态压起来
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=15;
const int mod=1000*1000*1000+7;
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int n,m;
int ch_id[300];
int str[maxn],bit[1<<15];
char sstr[maxn];
int g[1<<15][4],f[2][1<<15];
int ans[16];
int calc_g(int S,int ch){
  static int t[maxn],_t[maxn];
  for(int i=0;i<n;i++){
    t[i]=S>>i&1;
    if(i)t[i]+=t[i-1];
  }
  for(int i=0;i<n;i++){
    if(str[i]==ch){
      _t[i]=(i?t[i-1]:0)+1;
    }else{
      _t[i]=max(_t[i-1],t[i]);
    }
  }
  int _S=0;
  for(int i=n-1;i>=0;i--){
    if(i)_t[i]-=_t[i-1];
    if(_t[i])_S|=1<<i;
  }
  return _S;
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  ch_id['A']=0;
  ch_id['T']=1;
  ch_id['G']=2;
  ch_id['C']=3;
  for(int S=1;S<1<<15;S++){
    bit[S]=bit[S>>1]+(S&1);
  }
  for(;_--;){
    scanf("%s%d",sstr,&m);
    n=strlen(sstr);
    for(int i=0;i<n;i++)str[i]=ch_id[sstr[i]];
    for(int S=0;S<1<<n;S++){
      for(int ch=0;ch<4;ch++){
        g[S][ch]=calc_g(S,ch);
      }
    }
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<m;i++){
      for(int S=0;S<1<<n;S++)f[~i&1][S]=0;
      for(int S=0;S<1<<n;S++){
        for(int ch=0;ch<4;ch++){
          up(f[~i&1][g[S][ch]],f[i&1][S]);
        }
      }
    }
    memset(ans,0,sizeof(ans));
    for(int S=0;S<1<<n;S++){
      up(ans[bit[S]],f[m&1][S]);
    }
    for(int i=0;i<=n;i++){
      printf("%d\n",ans[i]);
    }
  }

  return 0;
}