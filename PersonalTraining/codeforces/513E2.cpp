/*
首先考虑把绝对值拆掉，考虑最优情况下的(i,s[i])化成二维平面上的图像，是大-小-大-小这样轮换，大的贡献系数是2，小的贡献系数是-2，两端是1/-1
不过大-小之间可能还有其他子段和插进来，这样的子段和对答案的贡献是0
考虑把原序列划分成若干个首尾相接的段，每一段可能完全没有贡献，也可能是[前半段+|后半段0]，或者[前半段-|后半段0]，只要证明最优答案肯定是这样的形态且对应的肯定是一个合法划分即可
[大][小]部分的贡献也是显然对的，[大小之间]不取肯定不会比取了更劣
用f[cur][used][sign][choose]表示前cur个，已经分了used段，当前段贡献是sign(+/-)，处于前半段还是后半段(是否被choose以计入贡献)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=30005;
const int maxk=205;
const int inf=0x3f3f3f3f;
int n,kk,a[maxn];
int f[2][maxk][2][2];
void cmax(int&x,int y){
  if(y>x)x=y;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&kk);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  memset(f,-63,sizeof f);
  f[0][0][0][0]=0;
  f[0][0][1][0]=0;
  int ans=0;
  for(int cur=1;cur<=n;cur++){
    for(int used=0;used<=kk;used++){
      for(auto sign:{0,1}){
        for(auto choose:{0,1}){
          int adds=sign?1:-1;
          if(used!=1 && used!=kk)adds*=2;
          adds*=a[cur];
          int&fnow=f[cur&1][used][sign][choose];
          fnow=-inf;
          if(choose){
            if(used)cmax(fnow,f[~cur&1][used-1][sign^1][0]+adds);
            if(used)cmax(fnow,f[~cur&1][used-1][sign^1][1]+adds);
            cmax(fnow,f[~cur&1][used][sign][1]+adds);
          }else{
            cmax(fnow,f[~cur&1][used][sign][1]);
            cmax(fnow,f[~cur&1][used][sign][0]);
            if(used && used!=1 && used!=kk)cmax(fnow,f[~cur&1][used-1][sign][1]);
            if(used && used!=1 && used!=kk)cmax(fnow,f[~cur&1][used-1][sign][0]);
          }
          if(cur==n && used==kk)ans=max(ans,fnow);
        }
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}