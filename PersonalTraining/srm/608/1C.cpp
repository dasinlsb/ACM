/*
考虑暴力枚举B然后在枚举A的时候快速维护答案
假设没有左右界限制的时候折线最左最右能到达[-L,R]，那么对于一个固定的B，当A慢慢减小的时候，在某一时刻碰到-L，这个折线会产生一个单位的偏移量，这会在右界上产生一个反方向的一个单位的偏移量，这两个偏移量刚好能够相互抵消
可以发现ans[A][B]和ans[A-1][B+1]是十分相关的，稍微画一画就能得出递推式，边界直接暴力即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=5005;
int f[maxn][maxn];
class OneDimensionalRobot{
public:
long long theSum(vector<string>commands1,vector<string>commands2,int minA,int maxA,int minB,int maxB){
  string str;
  // int minA,maxA,minB,maxB;
  // cin>>str>>minA>>maxA>>minB>>maxB;
  for(string&s:commands1)str+=s;
  for(string&s:commands2)str+=s;
  int pre_sum=0;
  int topA=0;
  int topB=0;
  for(int i=0;i<str.size();i++){
    pre_sum+=(str[i]=='R'?1:-1);
    topA=max(topA,-pre_sum);
    topB=max(topB,pre_sum);
  }
  long long ans=0;
  for(int A=minA;A<=maxA;A++){
    for(int B=minB;B<=maxB;B++){
      if(A-1>=minA && B+1<=maxB){
        f[A][B]=f[A-1][B+1];
        if(A<=topA || B+1<=topB){
          f[A][B]--;
        }
      }else if(A>=topA && B>=topB){
        f[A][B]=pre_sum;
      }else{
        int sum=0;
        for(int i=0;i<str.size();i++){
          sum+=(str[i]=='R'?1:-1);
          sum=max(sum,-A);
          sum=min(sum,B);
        }
        f[A][B]=sum;
      }
      ans+=f[A][B];
    }
  }
  return ans;
}
};
int main(){
  // freopen("aa.in","r",stdin);
  printf("solve %d\n",solve());
  return 0;
}