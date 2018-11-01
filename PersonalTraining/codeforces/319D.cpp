/*
显然按顺序处理的子串长度单调不降，并且每一种长度肯定是从左到右不相交的若干段
枚举子串长度len,可以把k*len作为关键点，共有n/len个，用hash可以在n/len*log(len)的复杂度找出所有可能的位置
显然对于固定的len，如果没有找到合法位置则hash可以不用重构
找位置的复杂度是O(n*log^2(n))，删除子串并维护hash的复杂度是O(n*sqrt(n))
*/
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull B=31;
const int maxn=50005;
int n,ban,s[maxn],tag[maxn];
char _s[maxn];
ull h[maxn],pw[maxn];
ull calc_hash(int l,int r){
  return h[r]-h[l-1]*pw[r-l+1];
}
void init_hash(){
  for(int i=1;i<=n;i++){
    h[i]=h[i-1]*B+s[i];
  }
}
int get_lcs_L(int x,int y){
  int l=1,r=x-ban;
  for(;l<=r;){
    int mid=l+r>>1;
    if(calc_hash(x-mid+1,x)!=calc_hash(y-mid+1,y))r=mid-1;
    else l=mid+1;
  }
  return r;
}
int get_lcs_R(int x,int y){
  int l=1,r=n-y+1;
  for(;l<=r;){
    int mid=l+r>>1;
    if(calc_hash(x,x+mid-1)!=calc_hash(y,y+mid-1))r=mid-1;
    else l=mid+1;
  }
  return r;
}
void del(int x,int y,int z){
  for(int i=x;i<=y;i++)tag[i]=z;
}
void print(){
  for(int i=1;i<=n;i++)putchar(s[i]+'a');puts("");
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%s",_s+1);
  n=strlen(_s+1);
  pw[0]=1;
  for(int i=1;i<=n;i++)pw[i]=pw[i-1]*B;
  for(int i=1;i<=n;i++)s[i]=_s[i]-'a';
  init_hash();
  for(int len=1;len+len<=n;len++){
     int find=0;
     ban=0;
     for(int i=len;i+len<=n;i+=len){
        if(s[i]!=s[i+len])continue;
        int dL=get_lcs_L(i,i+len);
        int dR=get_lcs_R(i+1,i+len+1);
        if(dL+dR>=len){
          del(i-dL+1,i-dL+len,len);
          ban=i-dL+len;
          find=1;
          // printf("round %d:",len);print();
        }
     }
     if(find){
       int t=0;
       for(int i=1;i<=n;i++)if(tag[i]!=len)s[++t]=s[i];
       n=t;
       init_hash();
     }
     
  }
  print();
  return 0;
}