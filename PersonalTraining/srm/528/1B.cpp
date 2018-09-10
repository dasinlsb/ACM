/*
折半爆搜，把前一半乘上相应的2的幂放到map里面就行了
*/
#include<bits/stdc++.h>
using namespace std;  

class SPartition{
	public:
	long long getCount(string s){
		// $CARETPOSITION$
    int n=s.size();
    int m=n/2;
    map<long long,int>cntL[22];
    for(int S=0;S<1<<m;S++){
      long long val[2]={0,0};
      int bit[2]={0,0};
      for(int i=0;i<m;i++){
        int w=S>>i&1;
        val[w]<<=1;
        if(s[i]=='x')val[w]|=1;
        bit[w]++;
      }
      val[0]<<=(m-bit[0]);
      val[1]<<=(m-bit[1]);
      cntL[m-bit[0]][val[0]-val[1]]++;
      cntL[m-bit[1]][val[1]-val[0]]++;
    }
    long long ans=0;
    for(int S=0;S<1<<m;S++){
      int val[2]={0,0};
      int bit[2]={0,0};
      for(int i=0;i<m;i++){
        int w=S>>i&1;
        val[w]<<=1;
        if(s[i+m]=='x')val[w]|=1;
        bit[w]++;
      }
      //printf("latrer %d %d %lld\n",S,bit[1],val[1]);
      int res=cntL[bit[1]][val[0]-val[1]];
      ans+=res;
    }
    return ans/2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "oxox"; long long Arg1 = 2LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { string Arg0 = "oooxxx"; long long Arg1 = 0LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { string Arg0 = "xoxxox"; long long Arg1 = 4LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { string Arg0 = "xo"; long long Arg1 = 0LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { string Arg0 = "ooooxoox"; long long Arg1 = 8LL; verify_case(4, Arg1, getCount(Arg0)); }
	void test_case_5() { string Arg0 = "ooxxoxox"; long long Arg1 = 8LL; verify_case(5, Arg1, getCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	SPartition ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
