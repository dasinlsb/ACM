/*
对于一个询问(x,k,p)，所有可能的gcd肯定只会从x的因数中产生
从大到小枚举x的所有因数，某个因数d算重的部分就是能被d整除的x的其他因数，可以再枚举每个因数的因数来求出每个数出现的准确次数，最后还原即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
vector<int>yue[maxn];
int cnt[maxn],f[maxn];
int Pow(long long x,int y,int p){
  long long t=1;
  for(;y;y>>=1){
    if(y&1)t=x*t%p;
    x=x*x%p;
  }
  return t;
}
int main(){
  freopen("aa.in","r",stdin);
  for(int i=1;i<maxn;i++){
    for(int j=i;j<maxn;j+=i){
      yue[j].push_back(i);
    }
  }
  int n;scanf("%d",&n);
  vector< pair<int,int> > q;
  for(;n--;){
    int x,k,p;scanf("%d%d%d",&x,&k,&p);
    for(int d:yue[x])cnt[d]++;
    int res=0;
    for(int i=int(yue[x].size())-1;i>=0;i--){
      int d=yue[x][i];
      if(cnt[d]){
        res=(res+1LL*cnt[d]*Pow(d,k,p))%p;
      }
      for(int e:yue[d])if(e!=d){
        cnt[e]-=cnt[d];
        q.push_back(make_pair(e,cnt[d]));
      }
    }
    for(;q.size();){
      cnt[q.back().first]+=q.back().second;
      q.pop_back();
    }
    printf("%d\n",res);
  }
  return 0;
}