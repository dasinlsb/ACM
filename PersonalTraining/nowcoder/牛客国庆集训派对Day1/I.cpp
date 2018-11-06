/*
求出原根后转成指标就变成求(a[i]+a[j])==x，经典fft，另外算一下a[i]%P==0的情况即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
const int maxm=1<<19;
const double PI=acos(-1.0);
int n,P,a[maxn],ind[maxn];
long long ans[maxn];
int Pow(int x,int y,int z){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=1LL*t*x%z;
    x=1LL*x*x%z;
  }
  return t;
}
int get_G(int n){
  static int q[555];
  int t=0;
  for(int i=2;i*i<=n-1;i++){
    if((n-1)%i==0)q[++t]=i,q[++t]=n/i;
  }
  for(int i=2;;i++){
    int j;
    for(j=1;j<=t;j++)if(Pow(i,q[j],n)==1)break;
    if(j>t)return i;
  }
}
int pos[maxm];
struct comp{
  double r,i;
  comp(){}
  comp(double _r,double _i){r=_r,i=_i;}
  comp operator+(comp t){return comp(r+t.r,i+t.i);}
  comp operator-(comp t){return comp(r-t.r,i-t.i);}
  comp operator*(comp t){return comp(r*t.r-i*t.i,r*t.i+i*t.r);}
  comp operator*(double t){return comp(r*t,i*t);}
}f[maxm];
void fft(comp a[],int n,int t){
  for(int i=1;i<n;i++)if(pos[i]>i)swap(a[i],a[pos[i]]);
  for(int k=0;1<<k<n;k++){
    int d=1<<k;
    double o=PI/d*t;
    comp _w=comp(cos(o),sin(o));
    for(int i=0;i<n;i+=d+d){
      comp w=comp(1,0);
      for(int j=0;j<d;j++){
        comp&A=a[i+j],&B=a[i+j+d],C=w*B;
        B=A-C;A=A+C;w=w*_w;
      }
    }
  }
  if(t==-1)for(int i=0;i<n;i++)a[i].r/=n;
}
int main(){
  freopen("aa.in","r",stdin);
  scanf("%d%d",&n,&P);
  int G=get_G(P);
  for(int i=1,j=0;j<P-1;i=1LL*i*G%P){
    ind[i]=j++;
  }
  for(int i=1;i<=n;i++){
    scanf("%d",a+i);
    if(a[i]%P){
      f[ind[a[i]%P]].r+=1.0;
    }
  }
  for(int i=0;i<maxm;i++)pos[i]=pos[i>>1]>>1|((i&1)<<18);
  fft(f,maxm,1);
  for(int i=0;i<maxm;i++)f[i]=f[i]*f[i];
  fft(f,maxm,-1);

  for(int i=0;i<P-1;i++){
    f[i].r+=f[i+P-1].r;
  }
  for(int i=1;i<P;i++){
    ans[i]=(long long)(f[ind[i]].r+0.5);
    // printf("ans %d %d\n",i,ans[i]);
  }
  for(int i=1,j=0;i<=n;i++){
    if(a[i]%P==0)ans[0]+=i*2-1,j++;
    else ans[0]+=j*2;
  }
  for(int i=1;i<=n;i++){
    printf("%lld\n",a[i]>=P?0LL:ans[a[i]]);
  }
  return 0;
}