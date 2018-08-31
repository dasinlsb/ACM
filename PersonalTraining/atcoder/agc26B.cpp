/*
我本来是转化成询问是否存在k使得(A+k*D)%B>C成立，发现不会做
考虑在第i天，可以确定的是剩余量x_i==A-i*B(mod D)
还有一个限制就是关于最值，某一天某一时刻如果出现最小肯定是上一天留了C+1下来，那么买了B之后还剩C+1-B
先排除掉D<B的情况，那么当天数趋于正无穷的时候最大值肯定是C-B+D
在[C+1-B,C-B+D]这个长度为D的区间中，x_i由上面的式子必定可以唯一确定
也就是说假设我们允许负数存在，同时满足上述两个式子的x_i肯定能被取到，这一点可能不是很显然(对我来说)，上面两个条件如果单独看的话都有点问题，但实际上是两个独立的限制，只不过考虑答案的时候取交
C-B+D>=C>0，也就是说只要存在C-B+1<=x_i<0，且x_i==A-i*B(mod D)那就无解
对于所有正整数i都存在k使得x_i=A-i*B+k*D，也就是x_i==A_i(mod gcd(B,D))
*/
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long x,long long y){
  return y==0?x:gcd(y,x%y);
}
int main(){
  freopen("aa.in","r",stdin);
  int _;scanf("%d",&_);
  for(;_--;){
    long long A,B,C,D;
    scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
    if(A<B||D<B){puts("No");continue;}
    if(C>=B-1){puts("Yes");continue;}
    long long G=gcd(B,D);
    A%=G;
    if(-G+A>=C-B+1)puts("No");
    else puts("Yes");
  }
  return 0;
}