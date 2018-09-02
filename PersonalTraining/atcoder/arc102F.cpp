/*
这道题有个很暴力的做法，按数值从小到大考虑暴力移，不过时间复杂度是O(n^2)，还需要分析一些性质
不妨反着考虑，初始序列是{1,2,3...n}，判断是否能生成目标序列
首先一点是一旦在(i-1,i,i+1)处发生交换，那么会在i这个地方形成一个类似屏障的东西，屏障两边的序列相互独立，两边的元素不可能跨过i
这个性质可以推出一个更直接有用的性质，那就是每个元素的移动都是严格单调的
然后是任意两个交换不可能发生在相邻位置，这也十分显然，有这两个性质其实就可以开始考虑具体做法了
从左到右扫描，所有a_i==i的位置都应该直接跳过，考虑遇到的第一个a_i!=i的位置i,这个a_i最终一定会被放到后面去，也就是必定存在以i+1为中心的交换
也就是a_{i+2}!=i+2也必定成立，不妨继续向右扩展，直到遇到某个j使得j==i(mod 2)&&(a[j-1]!=j-1||a[j]==j),这样的j显然是不能和i归到同一段的，所以从j-1往后要划分成另一个独立的问题，接下来考虑判断[i,j-2]是否合法
根据上面推出的移动方向单调的性质，不难得出发生矛盾当且仅当a[i],a[i+2],a[i+4]...a[j-2]形成的序列中存在某个位置，它前面有比它大的，后面有比它小的，然后发现这就等价于[最长下降子序列]长度>=3
时间复杂度O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=300005;
int a[maxn];
int chk(int l,int r){
  static int q[maxn];
  //printf("chk %d %d\n",l,r);
  int mx=1,mn=maxn;
  for(int i=l;i<=r;i++){
    mx=max(mx,a[i]);
    mn=min(mn,a[i]);
  }
  if(mx!=r||mn!=l)return 0;
  int top=0;
  for(int i=l;i<=r;i+=2){
    int x=top;
    for(;x&&a[i]>a[q[x]];x--);
    if(x==top)top++;
    if(top==3)return 0;
    q[++x]=i;
  }
  return 1;
}
int main(){
  freopen("aa.in","r",stdin);
  int n;scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
  }
  for(int i=1;i<=n;i++)if(a[i]!=i){
    int j=i+2;
    for(;j<=n&&a[j]!=j&&a[j-1]==j-1;j+=2);j-=2;
    if(!chk(i,j))return puts("No"),0;
    i=j;
  }
  puts("Yes");
  return 0;
}