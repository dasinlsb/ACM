/*
考虑两个操作[0,K-1],[1,K],两个操作之后只有0和K的状态发生翻转，类似的，所有i,j只要满足i%K==j%K就能同时翻转
根据%K将原串分成K份，显然每份只要不是初始奇数个0，其他情况都能全部点亮，如果有奇数个0，就贪心的选出a_i最小的那个另外考虑
现在序列上分布着若干个%K各不相等的熄灭的灯，接下来要么再用一次操作，把这些全部点亮，同时必须熄灭一些已经点亮的灯，要么不懂
这些灯虽然可能不是连续的K个，但是根据上面的推断必定可以转化成连续K个，只要贪心的取每份最小的那个考虑就可以了
*/
//#line 2 "BrightLamps.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=2505;
int mina[maxN],status[maxN];
class BrightLamps {
	public:  
	int maxBrightness(string init, vector <int> a, int K)  {  
		// $CARETPOSITION$  
    int n=SZ(init);
    for(int i=0;i<K;i++){
      mina[i]=1000;
      status[i]=0;
    }
    int suma=0;
    for(int i=0;i<n;i++){
      mina[i%K]=min(mina[i%K],a[i]);
      status[i%K]^=(init[i]=='0');
      suma+=a[i];
    }
    int tmp=0;
    for(int i=0;i<K;i++){
      if(status[i]){
        suma-=mina[i];
        tmp+=mina[i];
      }else{
        tmp-=mina[i];
      }
    }
    return suma+max(tmp,0);
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "011"; int Arr1[] = {3, 2, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 7; verify_case(0, Arg3, maxBrightness(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "0010100101"; int Arr1[] = {1, 1, 1, 3, 4, 3, 4, 5, 1, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 28; verify_case(1, Arg3, maxBrightness(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "1111111111"; int Arr1[] = {5, 5, 3, 3, 4, 3, 5, 1, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; int Arg3 = 33; verify_case(2, Arg3, maxBrightness(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "0010000001"; int Arr1[] = {8, 3, 10, 8, 3, 7, 4, 6, 3, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 55; verify_case(3, Arg3, maxBrightness(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "00001001010101100001100000010000011001000000001011"; int Arr1[] = {99, 29, 22, 50, 17, 49, 50, 54, 43, 29, 30, 33, 38, 53, 71, 48, 82, 25, 62, 93, 90, 64, 43, 95, 68,
35, 79, 11, 13, 47, 51, 44, 35, 55, 4, 34, 7, 10, 25, 38, 29, 58, 36, 34, 77, 90, 37, 58, 20, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 17; int Arg3 = 2068; verify_case(4, Arg3, maxBrightness(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	BrightLamps ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
