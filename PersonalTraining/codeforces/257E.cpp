/*
细节比较多的模拟题
我采用的逻辑是维护T,S,P分别表示当前已用时间，当前状态(1/-1表示上升/下降，0表示静止)，当前位置，其中S可以用树状数组来维护题目中的p_up和p_down来动态求出
用两个set分别维护在电梯内的人要去的楼层，以及在电梯外正在等候的人所在的楼层
每次根据S,P求出距离到达下一个要出去的楼层以及要进来的楼层最少还要多少时间arr
由于人的出现可能会改变方向，所以距离如果下一个出现的人的时间间隔<=arr，则优先将其加入
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int timeinf=maxn;
int n,m;
long long ans[maxn];
struct Node{
  int t,s,f,id;
  void read(){scanf("%d%d%d",&t,&s,&f);}
  bool operator<(const Node&node)const{
    return t<node.t;
  }
}person[maxn];
pair<int,int> getNext(int P,int S,set< pair<int,int> >&q){
  pair<int,int> res;
  if(S==1){
    auto it=q.lower_bound(make_pair(P,0));
    if(it==q.end())res.first=timeinf;
    else res=make_pair(it->first-P,it->second);
  }else{
    auto it=q.upper_bound(make_pair(P,n+1));
    if(it==q.begin())res.first=timeinf;
    else if(it==q.end()){
      if(q.size()==0)res.first=timeinf;
      else{
        auto _it=q.rbegin();
        res=make_pair(P-_it->first,_it->second);
      }
    }else{
      it--;
      res=make_pair(P-it->first,it->second);
    }
  }
  assert(res.first>=0);
  if(S==0)assert(res.first==timeinf);
  return res;
}
int tree[maxn];
void add(int x,int y){for(int i=x;i<=m;i+=i&-i)tree[i]+=y;}
int ask(int x){int t=0;for(int i=x;i>0;i-=i&-i)t+=tree[i];return t;}
int getS(int P){
  int x=ask(P-1);
  int y=ask(m);
  if(y==0)return 0;
  return y-x>=x?1:-1;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    person[i].read();
    person[i].id=i;
  }
  sort(person+1,person+1+n,[&](Node a,Node b){
    return a.t<b.t;
  });
  long long T=0;
  int P=1;
  int S=0;
  set< pair<int,int> > inside,outside;
  for(int pi=1;;){
    pair<int,int> nxtLeave=getNext(P,S,inside);
    pair<int,int> nxtPick=getNext(P,S,outside);
    int arr=min(nxtLeave.first,nxtPick.first);
    // printf("TSP %lld %d %d\n",T,S,P);
    // printf("nxtLeave %d %d\n",nxtLeave.first,nxtLeave.second);
    // printf("nxtPick %d %d\n",nxtPick.first,nxtPick.second);
    if(pi<=n){
      long long nxtCome=person[pi].t-T;  
      assert(nxtCome>=0);
      if(arr==timeinf || nxtCome<=arr){
        // printf("nxtCome %lld %d\n",T,person[pi].t);
        P+=(int)(S*nxtCome);
        T+=nxtCome;
        add(person[pi].s,1);
        S=getS(P);
        outside.insert(make_pair(person[pi].s,pi));
        pi++;
        continue;
      }
    }
    if(arr==timeinf)break;
    if(nxtPick.first<=nxtLeave.first){
      int _pi=nxtPick.second;
      outside.erase(make_pair(person[_pi].s,_pi));
      T+=nxtPick.first;
      P+=S*nxtPick.first;
      add(person[_pi].s,-1);
      add(person[_pi].f,1);
      S=getS(P);
      inside.insert(make_pair(person[_pi].f,_pi));
    }else{
      int _pi=nxtLeave.second;
      inside.erase(make_pair(person[_pi].f,_pi));
      T+=nxtLeave.first;
      ans[person[_pi].id]=T;
      P+=S*nxtLeave.first;
      add(person[_pi].f,-1);
      S=getS(P);
    }
  }
  for(int i=1;i<=n;i++){
    printf("%I64d\n",ans[i]);
  }
  return 0;
}