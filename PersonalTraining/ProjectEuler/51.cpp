#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
const int maxm=maxn*11;
int pn,prim[maxm/5],vis[maxm];
int solve(int G){
  for(int i=2;i<maxm;i++){
    if(!vis[i])prim[++pn]=i;
    for(int j=1;j<=pn && i*prim[j]<maxm;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0)break;
    }
  }
  vector<int> ten;
  ten.push_back(1);
  for(int i=1;i<10;i++)ten.push_back(ten[i-1]*10);
  for(int n=1;n<maxn;n++){
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
      for(int bS=0;bS<1<<bit.size();bS++){
        int sum=0;
        for(int i=0;i<bit.size();i++)if(bS>>i&1)sum+=bit[i];
        vector<int> q;
        for(int k=sum>=ten[num.size()-1]?1:0;k<10;k++){
          int _num=n+(k-num[cur])*sum;
          if(!vis[_num])q.push_back(_num);
        }
        if(q.size()==G){
          for(int x:q)printf("%d ",x);puts("");
          return n;
        }
      }
    }
  }
  return -1;
}
int main(){
  // freopen("aa.in","r",stdin);
  printf("%d\n",solve(8));
  return 0;
}