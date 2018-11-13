/*
首先原序列肯定可以分为若干段[1,d[1]],[d[1]+1,d[2]]...[d[k-1]+1,d[k]]
接下来发生交换的两个区间肯定出现在同一段，考虑在同一段中数的组成
肯定是[d[i],e_1],[e_1-1,e_2]...[e_k-1,d[i-1]+1]这样的若干段
那么肯定要交换第一段和最后一段，也就是两个区间肯定分别是同一段的前缀和后缀
进一步分析可以发现前缀后缀之间只隔一小段是最优的，因为前后缀无论长短都分别只能贡献1，而中间一段想要贡献超过1就必须单独成一小段，每个小段中的数的形态又是和之前类似的
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,kk,a[maxn];

void up(pair<int,int>&x,int y){
  x.first=min(x.first,y);
  x.second=max(x.second,y);
}
int solve2(int L,int R,int st){
  int res=0;
  for(int i=L;i<=R;i++){
    pair<int,int>now=make_pair(n,1);
    for(int j=i;j<=R;j++){
      up(now,a[j]);
      if(now==make_pair(st+i-L,st+j-L)){
        res++;
        i=j;
        break;
      }
    }
  }
  // printf("solve2 %d %d %d\n",L,R,res);
  return res;
}
int solve1(int L,int R){
  if(L==R)return 1;
  vector<int>q;
  for(int i=L;i<=R;i++){
    pair<int,int>now=make_pair(n,1);
    for(int j=i;j<=R;j++){
      up(now,a[j]);
      if(now==make_pair(R-(j-L),R-(i-L))){
        q.push_back(solve2(i,j,R-(j-L)));
        assert(q.back()>=1);
        i=j;
        break;
      }
    }
  }
  if(q.size()<=2)return q.size();
  int res=1;
  for(int i=1;i<q.size()-1;i++){
    res=max(res,q[i]+2);
  }
  return res;
}
int main(){
  freopen("aa.in","r",stdin);
    scanf("%d%d",&n,&kk);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    int ans=0;
    int add=0;
    for(int i=1;i<=n;i++){
        pair<int,int>now=make_pair(n,1);
        for(int j=i;j<=n;j++){
            up(now,a[j]);
            if(now==make_pair(i,j)){
              // printf("init %d %d\n",i,j);
              add=max(add,solve1(i,j));
              ans++;
              i=j;
              break;
            }
        }
    }
    assert(add>=1);
    ans+=add-1;
    puts(ans>=kk?"Yes":"Poor Simon");
    return 0;
} 