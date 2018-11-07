/*
f[i][j][k]表示到达(i,j)还有k单位燃料的最小费用
把状态剪掉一些后建图跑最短路，可以全程用整数二元组(x,y)表示x+sqrt(2)*y避免误差
每个f[i][j]内部先排序然后相邻连边表示在这个点加油的费用，同时每个状态f[i][j][k]向八个方向找唯一的目标点连边
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=22;
const int maxm=450005;
const long long inf=1e9+5;
int n,m,C,tot,ed,fir[maxm],P[maxn][maxn];
vector<int>id[maxn][maxn];

long long sq(long long x){
  return x*x;
}
struct Num{
  long long x,y;
  Num(){}
  Num(long long _x,long long _y){x=_x,y=_y;}
  Num operator+(Num t){return Num(x+t.x,y+t.y);}
  Num operator-(Num t){return Num(x-t.x,y-t.y);}
  Num operator*(long long t){return Num(x*t,y*t);}
  bool operator==(const Num&t)const{
    return x==t.x && y==t.y;
  }
  bool operator<(const Num&t)const{
    return (x>t.x?1LL:-1LL)*sq(x-t.x)<(t.y>y?2LL:-2LL)*sq(t.y-y);
  }
};
vector<Num>fuel[maxn][maxn];
Num dis[maxm];
struct Edge{
  int u,v,nxt;Num w;
}e[maxm*9];
void adde(int x,int y,Num z){
  e[++ed].u=x;e[ed].v=y;e[ed].w=z;e[ed].nxt=fir[x];fir[x]=ed;
}
bool inside(int r,int c){
  return r>=0 && r<=n && c>=0 && c<=m;
}
void dijkstra(int S){
  typedef pair<Num,int> P;
  priority_queue< P,vector<P>,greater<P> >q;
  for(int i=1;i<=tot;i++){
    dis[i]=Num(inf,inf);
  }
  q.push(make_pair(dis[S]=Num(0,0),S));
  for(;q.size();){
    pair<Num,int> t=q.top();q.pop();
    int x=t.second;
    if(dis[x]<t.first)continue;
    for(int i=fir[x];i;i=e[i].nxt){
      if(dis[x]+e[i].w<dis[e[i].v]){
        q.push(make_pair(dis[e[i].v]=dis[x]+e[i].w,e[i].v));
      }
    }
  }
}
int get_fuel(int r,int c,Num t){
  int p=lower_bound(fuel[r][c].begin(),fuel[r][c].end(),t)-fuel[r][c].begin();
  if(p<fuel[r][c].size() && fuel[r][c][p]==t){
    return id[r][c][p];
  }
  return 0;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d%d",&n,&m,&C);
  for(int i=0;i<=n;i++){
    for(int j=0;j<=m;j++){
      scanf("%d",&P[i][j]);
    }
  }
  for(int i=0;i<=n;i++){
    for(int j=0;j<=m;j++){
      for(int a=-(n+m);a<=(n+m);a++){
        for(int b=-(n+m);b<=(n+m);b++){
          if(Num(a,b)<Num(0,0))continue;
          if(Num(C,0)<Num(a,b))break;
          if(Num(max(n-i,m-j)-min(n-i,m-j),min(n-i,m-j))<Num(a,b))break;
          id[i][j].push_back(++tot);
          fuel[i][j].push_back(Num(a,b));
        }
      }
      sort(fuel[i][j].begin(),fuel[i][j].end());
    }
  }
  for(int i=0;i<=n;i++){
    for(int j=0;j<=m;j++){
      for(int k=0;k<id[i][j].size();k++){
        if(k>0){
          adde(id[i][j][k-1],id[i][j][k],(fuel[i][j][k]-fuel[i][j][k-1])*P[i][j]);
        }
        Num&nowf=fuel[i][j][k];
        for(int di=-1;di<=1;di++){
          for(int dj=-1;dj<=1;dj++){
            if(!di && !dj)continue;
            int r=i+di,c=j+dj;
            if(!inside(r,c))continue;
            int nxtp=0;
            if(!di || !dj){
              nxtp=get_fuel(r,c,Num(nowf.x-1,nowf.y));
            }else{
              nxtp=get_fuel(r,c,Num(nowf.x,nowf.y-1));
            }
            if(!nxtp)continue;
            adde(id[i][j][k],nxtp,Num(0,0));
          } 
        }
      }
    }
  }
  dijkstra(id[0][0][0]);
  Num ans=Num(inf,inf);
  for(int x:id[n][m])if(dis[x]<ans)ans=dis[x];
  assert(!(ans==Num(inf,inf)));
  printf("%.10lf\n",ans.x+sqrt(2.0)*ans.y);
  return 0;
}