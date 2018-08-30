/*
暴力枚举一下天数i判断即可
注意可重复点同一种菜
*/
//#line 2 "MysteriousRestaurant.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

int change(char x){
  if(x>='0'&&x<='9')return x-'0';
  if(x>='A'&&x<='Z')return x-'A'+10;
  if(x>='a'&&x<='z')return x-'a'+36;
}
const int maxN=55;
int cost[maxN][maxN];
class MysteriousRestaurant {
	public:  
	int maxDays(vector <string> prices, int budget)  {  
		// $CARETPOSITION$  
    int totDay=SZ(prices);
    int totDish=SZ(prices[0]);
    for(int i=0;i<totDish;i++){
      for(int j=0;j<totDay;j++){
        cost[i][j+1]=(j>6?cost[i][j-6]:0)+change(prices[j][i]);
      }
    }
    int day;
    for(day=1;day<=totDay;day++){
      int totCost=0;
      for(int pre=max(day-6,1);pre<=day;pre++){
        int tmp=cost[0][pre];
        for(int i=0;i<totDish;i++){
          tmp=min(tmp,cost[i][pre]);
        }
        totCost+=tmp;
      }
      if(totCost>budget)break;
    }
    return day-1;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"26", "14", "72", "39", "32", "85", "06"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; int Arg2 = 5; verify_case(0, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"26", "14", "72", "39", "32", "85", "06", "91"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; int Arg2 = 8; verify_case(1, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"SRM", "512"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 0; verify_case(2, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"Dear", "Code", "rsHa", "veFu", "nInT", "heCh", "alle", "ngeP", "hase", "andb", "ecar", "eful"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 256; int Arg2 = 10; verify_case(3, Arg2, maxDays(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	MysteriousRestaurant ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
