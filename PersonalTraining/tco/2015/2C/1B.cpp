/*
想要通过一些枚举去判断数值上的冲突十分困难
考虑用差分约束来解决数值上的问题，剩下只要枚举一下哪些人坐着，坐着的人的排列即可
对于每种枚举的情况，依次考虑每个人，都会加入一些限制
源点和汇点可以互相连边权为L,-L的边形成零环来达到恰好等于L的限制
不过对于站着的人，他们产生的限制是实数范围的，可以适当扩充原数据范围来用整数代替
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=12;
const long long inf=(long long)1e15;
struct Edge{int u,v;long long w;};
vector<Edge>qe;
void adde(int x,int y,long long z){
  qe.push_back((Edge){x,y,z});
}
long long dist[maxn];
int test(int n,int Ost){
  for(int i=0;i<n;i++)dist[i]=inf;
  dist[Ost]=0;
  for(int cl=1;cl<n;cl++){
    for(Edge&e:qe){
      if(dist[e.v]>dist[e.u]+e.w){
        dist[e.v]=dist[e.u]+e.w;
      }
    }
  }
  for(Edge&e:qe){
    if(dist[e.v]>dist[e.u]+e.w){
      return 0;
    }
  }
  return 1;
}
int id[maxn],pos[maxn];
int reach[maxn];
vector<string>solve(vector<long long>width,long long L){
  int n=width.size();
  int Ost=n;
  int Oed=n+1;
  width.resize(n+2,0);
  memset(reach,0,sizeof(reach));
  for(int S=0;S<1<<n;S++){
    int m=0;
    id[0]=Ost;
    for(int i=0;i<n;i++)if(S>>i&1){
      id[++m]=i;
    }
    id[m+1]=Oed;
    do{
      qe.clear();
      for(int i=1;i<=m;i++)pos[id[i]]=i;
      int fit_self=1;
      for(int i=0;i<n;i++){
        if(S>>i&1){
          int r=pos[i];
          for(;r<=m && id[r]>=i;r++);
          int l=pos[i];
          for(;l>=1 && id[l]>=i;l--);
          adde(pos[i],l,-width[id[l]]);
          adde(r,pos[i],-width[i]);
        }else{
          int pre=0;
          for(int j=1;j<=m;j++)if(id[j]<i){
            adde(pre,j,width[id[pre]]+width[i]-1);
            pre=j;
          }
          if(pre==0){
            if(width[i]<=L){
              fit_self=0;
              break;
            }
            continue;
          }
          adde(pre,m+1,width[id[pre]]+width[i]-1);
        }
      }
      if(!fit_self)continue;
      adde(0,m+1,L);
      adde(m+1,0,-L);
      for(int i=1;i<=m;i++){
        adde(i,0,0);
        adde(m+1,i,-width[id[i]]);
      }
      if(test(m+2,0)){
        // puts("");
        // printf("S %d\n",S);
        // if(S==3){
        // for(int i=1;i<=m;i++){
        //   printf("id %d %d\n",i,id[i]);
        // }
        // for(Edge&e:qe){
        //   printf("qe %d %d %lld\n",e.u,e.v,e.w);
        // }
        // puts("");
      // }
        for(int i=0;i<n;i++){
          reach[i]|=(1<<(S>>i&1));
        }
        break;
      }
    }while(next_permutation(id+1,id+1+m));
  }
  vector<string>res;
  for(int i=0;i<n;i++){
    if(reach[i]==3)res.push_back("Unsure");
    else if(reach[i]==2)res.push_back("Sit");
    else if(reach[i]==1)res.push_back("Stand");
    else assert(0);
  }
  return res;
}
int gcd(int x,int y){
  return y?gcd(y,x%y):x;
}
class LongSeat{
	public:
	vector <string> canSit(int L, vector <int> width){
		// $CARETPOSITION$
    int n=width.size();
    long long offset=1;
    for(int i=1;i<=n;i++)offset=offset*i/gcd(offset,i);
    // printf("offset %lld\n",offset);
    vector<long long>w;
    for(int i=0;i<n;i++)w.push_back(offset*width[i]);
    return solve(w,offset*L);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, canSit(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arr1[] = {100, 2, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Stand", "Sit", "Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, canSit(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 37; int Arr1[] = {3, 7, 5, 6, 4, 4, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Sit", "Sit", "Unsure", "Unsure", "Unsure", "Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, canSit(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 400; int Arr1[] = {92, 65, 99, 46, 24, 85, 95, 84}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Sit", "Unsure", "Unsure", "Unsure", "Unsure", "Stand", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, canSit(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000000000; int Arr1[] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, canSit(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 1; int Arr1[] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, canSit(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	LongSeat ___test;  
 	 ___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
