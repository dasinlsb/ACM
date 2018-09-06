/*
除了N以外的其他数，如果是质数肯定是属于对手的局面，合数肯定是自己的局面
维护质数合数及其必胜必败一共4个单调队列即可
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=500005;
int not_prim[maxn];
/*
not_prim=1||N is you
not_prim=0 is the other one 
*/
class PrimeCompositeGame{
	public:
	int theOutcome(int N, int K){
		// $CARETPOSITION$
    if(N<2)return 0;
    memset(not_prim,0,sizeof(not_prim));
    for(int i=2;i<=N;i++)if(!not_prim[i]){
      for(int j=i*2;j<=N;j+=i){
        not_prim[j]=1;
      }
    }
    deque<pair<int,int > >q[2][2];
    for(int i=2;i<=N;i++){
      int A=not_prim[i]||i==N;
      int B=A^1;
      for(int j=0;j<2;j++){
        for(;q[B][j].size()&&q[B][j].front().first<i-K;){
          q[B][j].pop_front();
        }
      }
      pair<int,int >now;
      if(q[B][0].size()){
        now=make_pair(i,q[B][0].front().second+1);
        if(i==N)return now.second;
        for(;q[A][1].size()&&now.second>q[A][1].back().second;){
          q[A][1].pop_back();
        }
        q[A][1].push_back(now);
      }else{
        now=make_pair(i,q[B][1].size()?q[B][1].front().second+1:0);
        if(i==N)return -now.second;
        for(;q[A][0].size()&&now.second<q[A][0].back().second;){
          q[A][0].pop_back();
        }
        q[A][0].push_back(now);
      }
    }
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; verify_case(0, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 58; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 30; int Arg1 = 3; int Arg2 = -2; verify_case(2, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 1; verify_case(3, Arg2, theOutcome(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 526; int Arg1 = 58; int Arg2 = 19; verify_case(4, Arg2, theOutcome(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	PrimeCompositeGame ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
