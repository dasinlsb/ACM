/*
直接dp已经选了k个当前memory为S是否先手必胜，不需要状压，直接判一下cards[i]为S子集的个数和k比较一下即可
*/
//#line 2 "FiveHundredEleven.cpp"  
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
int n,f[maxN][512];
VI cards;
int dp(int k,int S){
  if(~f[k][S])return f[k][S];
  int&res=f[k][S];
  if(S==511)return res=1;
  if(k==n)return res=0;
  int small=0;
  for(int i=0;i<SZ(cards);i++){
    if((cards[i]&S)==cards[i]){
      small++;
    }else{
      if(dp(k+1,S|cards[i])==0)return res=1;
    }
  }
  if(small>k){
    if(dp(k+1,S)==0)return res=1;
  }
  return res=0;
}
class FiveHundredEleven {
	public:  
	string theWinner(vector <int> cards)  {  
		// $CARETPOSITION$ 
    n=SZ(cards);
    ::cards=cards;
    memset(f,-1,sizeof(f));
    return dp(0,0)?"Fox Ciel":"Toastman";
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 5, 7, 9, 510}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(0, Arg1, theWinner(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(1, Arg1, theWinner(Arg0)); }
	void test_case_2() { int Arr0[] = {511}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(2, Arg1, theWinner(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 58, 192, 256}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(3, Arg1, theWinner(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	FiveHundredEleven ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
