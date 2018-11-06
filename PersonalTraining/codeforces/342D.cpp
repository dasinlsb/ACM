/*
如果直接把O当作X，会有2种情况算重，
--|
|O|
|--

|--
|O|
--|
判一下O的位置是否在边缘，如果不在的话把周围9格格子全部变成X然后在跑一遍
转移要一列一列地转移，否则难以避免会算重
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=10005;
const int mod=1e9+7;
const int dr[4]={-1,0,1,0};
const int dc[4]={0,1,0,-1};
int n,ban[maxn];
char str[3][maxn],_str[3][maxn];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int f[maxn][8][8];
int DP(){
  for(int i=1;i<=n;i++){
    ban[i]=0;
    for(int j=0;j<3;j++){
      if(str[j][i]=='X')ban[i]|=1<<j;
    }
  }
  memset(f,0,sizeof f);
  f[0][ban[1]][ban[2]]=1;
  for(int i=0;i<n;i++){
    for(int sl=0;sl<8;sl++){
      for(int sr=0;sr<8;sr++){
        if(!f[i][sl][sr])continue;
        // printf("f %d %d %d: %d\n",i,sl,sr,f[i][sl][sr]);
        if(sl==7){
          up(f[i+1][sr][ban[i+3]],f[i][sl][sr]);
          continue;
        }
        for(int p=0;p<2;p++){
          if((~sl>>p&1) && (~sl>>p+1&1)){
            int w=3-p-p-1;
            if(sl>>w&1){
              up(f[i+1][sr][ban[i+3]],f[i][sl][sr]);
            }else
            if(~sr>>w&1){
              up(f[i+1][sr|1<<w][ban[i+3]],f[i][sl][sr]);
            }
          }
        }
        int flag=1;
        int _sr=sr;
        for(int p=0;p<3;p++){
          if(~sl>>p&1){
            if(sr>>p&1)flag=0;
            else _sr|=1<<p;
          }
        }
        if(flag)up(f[i+1][_sr][ban[i+3]],f[i][sl][sr]);

      }
    }
  }
  return f[n][0][0];
}
int main(){
  freopen("aa.in","r",stdin);
  // freopen("mine.out","w",stdout);
  scanf("%d",&n);//n>=3
  for(int i=0;i<3;i++){
    scanf("%s",str[i]+1);
    str[i][n+1]='.';
  }
  int R,C;
  for(int i=0;i<3;i++){
    for(int j=1;j<=n;j++){
      if(str[i][j]=='O'){
        R=i,C=j;
        str[i][j]='X';
      }
    }
  }
  int ans=DP();
  // printf("ans %d\n",ans);
  if(R==1 && C>1 && C<n){
    for(int i=-1;i<=1;i++){
      for(int j=-1;j<=1;j++){
        str[R+i][C+j]='X';
      }
    }
    int cut=DP()*2%mod;
    up(ans,mod-cut);
  }
  printf("%d\n",ans);
  return 0;
}
