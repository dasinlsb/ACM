/*
将S排序后，枚举S中的两个数S_i<S_j，显然可以将S_i当作某个斐波那契数列的第一项，设第二项为x
那么枚举一下S_j是第几项后可以解出x，这个枚举是log级别的，解出x之后可以递推出整个序列，序列长度也是log级别的
那么只要维护一下S中的每个位置往前最多多少位，往后最多多少位
时间复杂度O(n^2log^2(n))
*/
//#line 2 "SubFibonacci.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=55;
const int inf=1000*1000*1000;
void make(VI&q,int x,int y,map<int,int>&vis){
  int num[2]={x,y};
  q.pb(vis[x]);
  if(x<y&&vis.count(y)==1)q.pb(vis[y]);
  for(int k=0;;k^=1){
    num[k]+=num[k^1];
    if(num[k]>inf)break;
    if(vis.count(num[k])==1)q.pb(vis[num[k]]);
  }
}
ll fib[50];
int pre[maxN],suf[maxN];
class SubFibonacci {
	public:  
	int maxElements(vector <int> S)  {  
		// $CARETPOSITION$  
    fib[1]=1;
    for(int i=2;i<=45;i++){
      fib[i]=fib[i-1]+fib[i-2];
    }
    int n=SZ(S);
    map<int,int>map_S;
    sort(S.begin(),S.end());
    for(int i=0;i<n;i++){
      map_S[S[i]]=i;
    }
    for(int i=0;i<n;i++){
      pre[i]=suf[i]=1;
    }
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        for(int k=0;fib[k]*S[i]<S[j];k++){
          if((S[j]-fib[k]*S[i])%fib[k+1]==0){
              VI que;
              make(que,S[i],(S[j]-fib[k]*S[i])/fib[k+1],map_S);
              for(int p=0;p<SZ(que);p++){
                pre[que[p]]=max(pre[que[p]],p+1);
                suf[que[p]]=max(suf[que[p]],SZ(que)-p);
              }
          }
        }
      }
    }
    for(int i=1;i<n;i++){
      pre[i]=max(pre[i],pre[i-1]);
    }
    for(int i=n-1;~i;i--){
      suf[i]=max(suf[i],suf[i+1]);
    }
    //printf("tot %d\n",tot);
    int ans=1;
    for(int i=0;i<n-1;i++){
      ans=max(ans,pre[i]+suf[i+1]);
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {8, 1, 20, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxElements(Arg0)); }
	void test_case_1() { int Arr0[] = {19, 47, 50, 58, 77, 99}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, maxElements(Arg0)); }
	void test_case_2() { int Arr0[] = {512}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, maxElements(Arg0)); }
	void test_case_3() { int Arr0[] = {3, 5, 7, 10, 13, 15, 20, 90}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, maxElements(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(4, Arg1, maxElements(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SubFibonacci ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
