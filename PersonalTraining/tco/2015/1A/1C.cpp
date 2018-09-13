/*
直接上Hall定理，枚举左边点的子集，把边权加到右边对应点上，然后贪心删即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=20;
int w[maxn];
class Revmatching{
public:
int smallest(vector<string>A){
  int n=A.size();
  int ans=10000;
  for(int S=1;S<1<<n;S++){
    memset(w,0,sizeof(w));
    int bit=0;
    for(int i=0;i<n;i++)if(1<<i&S){
      bit++;
      for(int j=0;j<n;j++)w[j]+=A[i][j]-'0';
    }
    sort(w,w+n);
    int res=0;
    for(int i=0;i<n-bit+1;i++)res+=w[i];
    ans=min(ans,res);
  }
  return ans;
}
};
int main(){
  return 0;
}