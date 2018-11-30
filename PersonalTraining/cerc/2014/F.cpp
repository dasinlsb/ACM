/*
将三个串用'a'-1补齐至长度相同
设f[i][0/1][0/1]表示后i位，串A字典序</=串B,串B字典序</=串C的方案数
如果可以枚举串B要填的字母那可以用O(n*4*26)的复杂度做dp，但是n<=1e6，复杂度无法接受
显然每个i的转移系数只和三个串这一位的字母有关，也就是可以考虑预处理(26+2)^3种状态下4*4的转移矩阵
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
const int mod=1e9+9;
int A='a'-2;
int Z='z';
string str[3];
int f[2][2][2];
int g[36000][2][2][2][2];
int getL(int c){return c=='a'-2?'a':c;}
int getR(int c){return c=='a'-2?'z':c;}
int ask(int l1,int r1,int l2,int r2){
  return max(min(r1,r2)-max(l1,l2)+1,0);
}
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void init(){
  int L[3],R[3],c[3];
  for(c[0]=A;c[0]<=Z;c[0]++){
    for(c[1]=A;c[1]<=Z;c[1]++){
      for(c[2]=A;c[2]<=Z;c[2]++){
        int S=0;
        for(int i=0;i<3;i++){
          S=S*30+c[i]-'a'+3;
          L[i]=getL(c[i]);
          R[i]=getR(c[i]);
        }
        for(int c1=L[1];c1<=R[1];c1++){
          up(g[S][1][1][0][0],1LL*ask(A,c1-1,L[0],R[0])*ask(c1+1,Z,L[2],R[2])%mod);
          up(g[S][1][0][0][0],1LL*ask(A,c1-1,L[0],R[0])*ask(c1,c1,L[2],R[2]) %mod);
          up(g[S][0][1][0][0],1LL*ask(c1,c1,L[0],R[0])* ask(c1+1,Z,L[2],R[2])%mod);
          up(g[S][0][0][0][0],1LL*ask(c1,c1,L[0],R[0])* ask(c1,c1,L[2],R[2]) %mod);
          up(g[S][1][1][0][1],1LL*ask(A,c1-1,L[0],R[0])*ask(A,Z,L[2],R[2])   %mod);
          up(g[S][0][1][0][1],1LL*ask(c1,c1,L[0],R[0])* ask(A,Z,L[2],R[2])   %mod);
          up(g[S][1][1][1][0],1LL*ask(A,Z,L[0],R[0])*   ask(c1+1,Z,L[2],R[2])%mod);
          up(g[S][1][0][1][0],1LL*ask(A,Z,L[0],R[0])*   ask(c1,c1,L[2],R[2]) %mod);
          up(g[S][1][1][1][1],1LL*ask(A,Z,L[0],R[0])*   ask(A,Z,L[2],R[2])   %mod);
        }
      }
    }
  }
}
int main(){
  freopen("aa.in","r",stdin);
  init();
  int _;cin>>_;
  for(;_--;){
    int maxLen=0;
    for(int i=0;i<3;i++){
      cin>>str[i];
      maxLen=max(maxLen,(int)str[i].size());
    }
    for(int i=0;i<3;i++){
      str[i].resize(maxLen,'a'-1);
    }
    memset(f,0,sizeof f);
    f[0][1][1]=1;
    for(int i=1;i<=maxLen;i++){
      int S=0;
      for(int j=0;j<3;j++){
        char c=str[j][maxLen-i];
        if(c=='?')c='a'-2;
        S=S*30+c-'a'+3;
      }
      for(int x=0;x<4;x++){
        f[i&1][x>>1][x&1]=0;
      }
      for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
          up(f[i&1][x>>1][x&1],1LL*g[S][y>>1][y&1][x>>1][x&1]*f[~i&1][y>>1][y&1]%mod);
        }
      }
    }
    int ans=f[maxLen&1][0][0];
    cout<<ans<<endl;
  }
  return 0;
}