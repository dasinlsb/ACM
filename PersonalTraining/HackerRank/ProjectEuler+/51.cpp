#include <bits/stdc++.h>
using namespace std;
namespace dasin{
const int maxn=1e8;
int pn,prim[maxn/15];bool vis[maxn];
inline int nextState(int S,int k){
  int x=S&-S;
  int y=S+x;
  return ((S&~y)/x>>1)|y;
}
int solve(int N,int K,int L){
  vector<int> ten;
  ten.push_back(1);
  for(int i=1;i<10;i++)ten.push_back(ten[i-1]*10);
  int Nl=ten[N-1],Nr=ten[N];
  for(int i=2;i<Nr;i++){
    if(!vis[i])prim[++pn]=i;
    for(int j=1;j<=pn && i*prim[j]<Nr;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0)break;
    }
  }
  for(int pi=1;pi<=pn && prim[pi]<Nr;pi++){
    if(prim[pi]<Nl)continue;
    int n=prim[pi];
    vector<int> num;
    for(int i=n;i;i/=10)num.push_back(i%10);
    vector<int> use(num.size(),0);
    for(int cur=0;cur<num.size();cur++){
      if(use[cur])continue;
      vector<int> bit;
      for(int i=cur;i<num.size();i++){
        if(num[i]==num[cur]){
          use[i]=1;
          bit.push_back(ten[i]);
        }
      }
      if(bit.size()<K)continue;
      for(int bS=(1<<K)-1;bS<1<<bit.size();){
        int sum=0;
        for(int i=0;i<bit.size();i++)if(bS>>i&1)sum+=bit[i];
        vector<int> q;
        for(int k=sum>=ten[num.size()-1]?1:0;k<10;k++){
          int _num=n+(k-num[cur])*sum;
          if(!vis[_num])q.push_back(_num);
        }
        if(q.size()>=L){
          sort(q.begin(),q.end());
          for(int i=0;i<L;i++)printf("%d ",q[i]);puts("");
          return 1;
        }
        bS=nextState(bS,K);
      }
    }
  }
  return 0;
}
}
int main(){
  // freopen("aa.in","r",stdin);
  int N,K,L;
  scanf("%d%d%d",&N,&K,&L);
  int status=dasin::solve(N,K,L);
  // printf("status %d\n",status);
  return 0;
}