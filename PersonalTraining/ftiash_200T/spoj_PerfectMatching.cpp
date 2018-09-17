/*
考虑行列式的定义，就是每行取一个位置构成列的排列再乘起来再乘上(-1)^k再加起来，二分图的每个完备匹配都对应邻接矩阵对应行列式中的1或-1
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=305;
char a[maxn][maxn];
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++){
      scanf("%s",a[i]);
    }
    int ans=1;
    for(int i=0;i<n;i++){
      int k;
      for(k=i;k<n&&a[k][i]=='0';k++);
      if(k==n){
        ans=0;break;
      }
      if(k!=i){
        for(int j=0;j<n;j++)swap(a[i][j],a[k][j]);
      }
      for(int j=i+1;j<n;j++)if(a[j][i]=='1'){
        for(int k=i;k<n;k++)a[j][k]=((a[j][k]-'0')^(a[i][k]-'0'))+'0';
      }
    }
    puts(ans?"Odd":"Even");
  }
  return 0;
}
