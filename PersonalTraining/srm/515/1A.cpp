//#line 2 "RotatedClock.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
  
class RotatedClock {
	public:  
	string getEarliest(int hourHand, int minuteHand)  {  
		// $CARETPOSITION$  
    int m=minuteHand;
    int h=hourHand;
    for(int i=0;i<12;i++){
      if(m%6==0&&m==(h%30)*12){
        char s[5];
        if(h/30<10)s[0]='0',s[1]=h/30+'0';
        else s[0]=(h/30)/10+'0',s[1]=(h/30)%10+'0';
        s[2]=':';
        if(m/6<10)s[3]='0',s[4]=m/6+'0';
        else s[3]=(m/6)/10+'0',s[4]=(m/6)%10+'0';
        return string(s,5);
      }
      m=(m+30)%360;
      h=(h+30)%360;
     //printf("%d %d\n",m,h);
    }
    return "";
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 70; int Arg1 = 300; string Arg2 = "08:20"; verify_case(0, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 90; int Arg1 = 120; string Arg2 = "11:00"; verify_case(1, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 240; int Arg1 = 36; string Arg2 = ""; verify_case(2, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 19; int Arg1 = 19; string Arg2 = ""; verify_case(3, Arg2, getEarliest(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 12; string Arg2 = "00:02"; verify_case(4, Arg2, getEarliest(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RotatedClock ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
