/*
有个结论{2^0,2^1...2^k}可以到达与原点曼哈顿距离<2^{k+1}的所有点
但这样x+y只能是奇数，偶数的情况直接加个1
从终点(x,y)倒着判断，往上下左右哪个方向走2^k步可以走到{2^0...2^{k-1}}的范围内
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
const char CH[]={'R','D','L','U'};
const long long DR[]={-1,0,1,0};
const long long DC[]={0,1,0,-1};
int n;
long long x[maxn],y[maxn];
int cnt[2];
bool test(long long x,long long y,int d){
  return abs(x)+abs(y)<=(1<<d)-1;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%lld%lld",x+i,y+i);
    cnt[abs(x[i]+y[i])&1]++;
  }
  if(cnt[0] && cnt[1])return puts("-1"),0;
  if(cnt[0]){
    for(int i=1;i<=n;i++){
      x[i]++;
    }
    printf("%d\n%d ",32,1);
  }else printf("%d\n",31);
  for(int i=0;i<=30;i++)printf("%d ",1<<i);
  puts("");
  for(int i=1;i<=n;i++){
    vector<char>op;
    for(int j=30;~j;j--){
      int step=1<<j;
      for(int k=0;k<4;k++){
        if(test(x[i]+DR[k]*step,y[i]+DC[k]*step,j)){
          x[i]+=DR[k]*step;
          y[i]+=DC[k]*step;
          op.push_back(CH[k]);
          break;
        }
      }
    }
    // printf("round %d  :",i);
    if(cnt[0])op.push_back('L');
    reverse(op.begin(),op.end());
    for(char c:op)putchar(c);
    puts("");
  }
  return 0;
}