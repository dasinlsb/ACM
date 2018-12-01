#include <bits/stdc++.h>
using namespace std;
const int N=10000;
clock_t _st;

int calc(int n,int sqrtn){
  static int last[105][N+5],vis[105][N+5];
  vector<int> a;
  int u=sqrtn;
  int d=1;
  for(int t=1;;t++){
    // printf("calc %d %d %d\n",n,u,d);
    if(vis[u][d]==n){
      return t-last[u][d];
    }
    last[u][d]=t;
    vis[u][d]=n;
    int tmp=n-u*u;
    assert(tmp%d==0);
    d=tmp/d;
    int A=(u+sqrtn)/d;
    u-=A*d;
    u=-u;
    a.push_back(A);
  }
}
int solve(){
  int ans=0;
  for(int i=1;i*i<N;i++){
    int l=i*i+1;
    int r=min(N,(i+1)*(i+1)-1);
    for(int j=l;j<=r;j++){
      // printf("start %d\n",j);
      int len=calc(j,i);
      if(len&1){
        ans++;
      }
    }
  }
  return ans;
}

int main(){
  //freopen("aa.in","r",stdin);
  _st=clock();
  printf("found %d\n",solve());
  clock_t _ed=clock();
  printf("time %.6lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
  return 0;
}