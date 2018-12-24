/*
相当于在原序列中依次选取k+1个元素，Imp可以不断拒绝，而且可以在任意时刻接受
考虑这k+1个元素中任意两个元素i,j，当i排在j前面，这个二元组对答案的贡献是min{v[i]-c[i],v[j]-c[j]-c[i]}(答案对这个表达式取min)
反之如果j排在i前面，贡献是min{v[j]-c[j],v[i]-c[i]-c[j]}，观察一下可以发现只要满足v[i]<=v[j]，就有v[i]-c[i]>=v[i]-c[i]-c[j] && v[j]-c[j]-c[i]>=v[i]-c[i]-c[j]，即可推出前一个贡献恒不劣于后一个贡献，也就是说i排在j前面最优
那么可以用f[i][j]表示前i个物品，已经选了j个的答案，对于一个物品可以选也可以不选，如果选的话Imp也可以选或不选，这里如果Imp不选的话会到达一个终止状态即无法继续向后转移，可以特判或者倒过来dp
时间复杂度O(nk)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=150005;
const int maxk=10;
const long long inf=1e18;
int n,kk;
long long f[maxn][maxk];
struct Item{int v,c;}a[maxn];
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    scanf("%d%d",&n,&kk);
    for(int i=1;i<=n;i++){
      scanf("%d%d",&a[i].v,&a[i].c);
    }
    sort(a+1,a+1+n,[&](Item x,Item y){
      return x.v>y.v;
    });
    for(int j=0;j<=kk;j++){
      f[0][j]=0;
    }
    for(int i=1;i<=n;i++){
      for(int j=0;j<=kk;j++){
        long long choose=a[i].v-a[i].c;
        if(j)choose=min(choose,f[i-1][j-1]-a[i].c);
        f[i][j]=max(f[i-1][j],choose);
      }
    }
    long long ans=f[n][kk];
    printf("%I64d\n",ans);
  }
  return 0;
}