/*
把每个数按照它所包含的数字集合分到2^10个类，然后枚举两个类更新答案即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<10;
int bit[maxn],cnt[maxn];
class Similars{
  public:
  int maxsim(int L, int R){
    for(int i=1;i<1<<10;i++){
      bit[i]=bit[i>>1]+(i&1);
    }
    for(int i=L;i<=R;i++){
      int s=0;
      for(int j=i;j;j/=10)s|=1<<(j%10);
      cnt[s]++;
    }
    int ans=0;
    for(int i=0;i<1<<10;i++)if(cnt[i]){
      if(cnt[i]>=2)ans=max(ans,bit[i]);
      for(int j=i+1;j<1<<10;j++)if(cnt[j]){
        ans=max(ans,bit[i&j]);
      }
    }
    return ans;
  }
};
int main(){
  printf("%d\n",maxsim(1,10));
  return 0;
}