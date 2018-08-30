/*
如果按照从左到右的顺序构造方案必定要记录之前的状态，无法接受
考虑从右往左构造hash去表示结果的状态，设当前从右往左已经构造出了S这个hash值，现在要讨论S左边一位的操作c
c=='+':S=S+1;
c=='-':S=S-1;
c=='>':S=S/x;
c=='<':S=S*x;
为避免冲突，多随机选取几个x
*/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int((x).size()))
#define fi first
#define se second
#define pb push_back
#define VI vector<int>
typedef long long ll;
typedef pair<int,int> pii;
const int maxN=250005;
const int mod=1000*1000*1000+7;
int n,root[5][2],f[5][maxN],g[5][maxN];
pii cof[5][maxN];
char str[maxN];
map<tuple<int,int,int,int,int>,int>map_cnt;
int pw(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
void trans(pii&x,pii y,char c,int sed[2]){
  if(c=='+')x=pii(y.fi,(mod-y.fi+y.se)%mod);
  if(c=='-')x=pii(y.fi,(y.fi+y.se)%mod);
  if(c=='>')x=pii((ll)y.fi*sed[0]%mod,y.se);
  if(c=='<')x=pii((ll)y.fi*sed[1]%mod,y.se);
}
int main(){
  srand(time(0));
  freopen("aa.in","r",stdin);
  int i,j;
  scanf("%d%s",&n,str+1);
  for(i=0;i<5;++i){
    root[i][0]=rand()%(1000*1000*1000);
    root[i][1]=pw(root[i][0],mod-2);
    //printf("root val %d %d\n",root[i][0],root[i][1]);
    int bas=0;
    for(j=n;j;--j){
      if(str[j]=='+')bas=(bas+1)%mod;
      if(str[j]=='-')bas=(bas+mod-1)%mod;
      if(str[j]=='>')bas=(ll)bas*root[i][1]%mod;
      if(str[j]=='<')bas=(ll)bas*root[i][0]%mod;
    }
    cof[i][n+1]=pii(1,0);
    //printf("root %d\n",i);
    for(j=n;j;--j){
      trans(cof[i][j],cof[i][j+1],str[j],root[i]); 
      f[i][j]=cof[i][j].se;
      g[i][j]=((ll)cof[i][j].fi*bas+cof[i][j].se)%mod;
      //printf("f[%d] g[%d]\n",f[i][j],g[i][j]);
    }
    //printf("g %d %d\n",i,g[i][1]);
  }
  
  ll ans=0;
  map_cnt[make_tuple(0,0,0,0,0)]++;
  for(i=n;i;--i){
    //int pre=ans;
    auto nowg=make_tuple(g[0][i],g[1][i],g[2][i],g[3][i],g[4][i]);
    ans+=map_cnt[nowg];
    //if(ans-pre)printf("ans %d %d\n",i,ans-pre);
    auto nowf=make_tuple(f[0][i],f[1][i],f[2][i],f[3][i],f[4][i]);
    map_cnt[nowf]++;
  }
  printf("%lld\n",ans);
  return 0;
}