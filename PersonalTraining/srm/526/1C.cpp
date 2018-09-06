/*
直接暴力dp可以考虑用f[i][j]用了i个，最后匹配到goodSubstring的长度为j的前缀的答案
顺便记录一下概率以及预处理G[i][j]表示goodSubstring的长度为i的前缀和pieces[j]前后拼接起来的串中出现多少次goodSubstring以及最后会落在goodSubstring的哪个前缀上，这样就可以转移了
但是K太大无法接受，实际上在i>=goodSubstring.size()的时候f[i+1][j]-f[i][j]是一个定值，因为前继状态不存在长度比goodSubstring小的情况
算一下f的差分数组的答案就可以了
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
vector<int >getNext(string&s){
  int n=s.size();
  vector<int >nxt(n,-1);
  int j=-1;
  for(int i=1;i<n;i++){
    for(;~j&&s[j+1]!=s[i];j=nxt[j]);
    if(s[j+1]==s[i])nxt[i]=++j;
  }
  return nxt;
}
pair<int,int >G[505][55];
double prob[505][505],f[505];
class DengklekMessage{
	public:
	double theExpected(vector <string> pieces, vector <string> goodSubstring, long long K){
		// $CARETPOSITION$
    string goal;
    for(int i=0;i<goodSubstring.size();i++){
      goal+=goodSubstring[i];
    }
    vector<int >nxtg=getNext(goal);
    for(int pos=0;pos<goal.size();pos++){
      for(int i=0;i<pieces.size();i++){
        G[pos][i]=make_pair(0,0);
        string all=goal.substr(0,pos)+pieces[i];
        int p=-1;
        for(int j=0;j<all.size();j++){
          for(;~p&&all[j]!=goal[p+1];p=nxtg[p]);
          if(goal[p+1]==all[j])p++;
          if(p+1==goal.size()){
            G[pos][i].first++;
            p=nxtg[p];
          }
        }
        G[pos][i].second=p+1;
        assert(p+1<goal.size());
      }
    }
    double step=1.0/pieces.size();
    fill(prob[0],prob[0]+505,0.0);
    fill(f,f+505,0.0);
    prob[0][0]=1.0;
    for(int use=0;use<=goal.size();use++){
      fill(prob[use+1],prob[use+1]+505,0.0);
      for(int pos=0;pos<goal.size();pos++){
        for(int i=0;i<pieces.size();i++){
          prob[use+1][G[pos][i].second]+=step*prob[use][pos];
          f[use+1]+=step*prob[use][pos]*G[pos][i].first;
        }
      }
    }
    double ans=0;
    if(K<=goal.size()){
      for(int i=1;i<=K;i++)ans+=f[i];
    }else{
      for(int i=1;i<=goal.size();i++)ans+=f[i];
      ans+=f[goal.size()+1]*(K-goal.size());
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; double Arg3 = 9.0; verify_case(0, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; double Arg3 = 0.0; verify_case(1, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"0", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 3LL; double Arg3 = 0.5; verify_case(2, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"0", "10", "110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0", "1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5LL; double Arg3 = 2.6666666666666665; verify_case(3, Arg3, theExpected(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"0", "10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"000101000101010100"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 526LL; double Arg3 = 0.25146484375; verify_case(4, Arg3, theExpected(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	DengklekMessage ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
