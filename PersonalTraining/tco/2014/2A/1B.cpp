/*
两个wolf需要到某一端点调整位置当且仅当(st_i<st_j)!=(en_i<en_j)
考虑最右的需要到左端调整位置的那个wolf,起始点在它的左边所有wolf肯定都要到左端去
所以第一种情况是中间不动，两边各向两端点移动
假设枚举的两个分界点为l,r，那么[1,l],[r,n]各自内部的调整已经完毕，但是两者之间可能还需要调整
问题转化为枚举一个分界线l后，[1,l]的都移动到左端点，[l+1,n]都移动到右端点，将两堆点移动到终点
可以反过来考虑，从终点开始移动到当前的状态，显然和之前一样，最优方案也是按终点排序分成左右两份分别移动到左右两端
*/
//#line 2 "NarrowPassage.cpp"  
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
const int inf=20000*10000;
pii seg[maxN];
int change[maxN][maxN],dir[maxN],firL[maxN],firR[maxN],rp[maxN];
int Abs(int x){return x>0?x:-x;}
int ask(int l,int r,int x,int y){
  for(int i=l;i<=r;++i){
    for(int j=x;j<=y;++j)if(change[i][j])return 1;
  }
  return 0;
}
class NarrowPassage {
	public:  
	int minDist(int L, vector <int> a, vector <int> b)  {  
		// $CARETPOSITION$  
    int i,j;
    int n=SZ(a);
    for(i=0;i<n;++i)seg[i+1]=pii(a[i],b[i]);
    sort(seg+1,seg+1+n);
    for(i=1;i<=n;++i){
      change[i][0]=0;
      for(j=1;j<=n;++j)if((seg[i].fi<seg[j].fi)!=(seg[i].se<seg[j].se)){
        change[i][j]=1;
        change[i][0]=1;
      }
    }
    for(i=1;i<=n;++i){
      dir[i]=Abs(seg[i].fi-seg[i].se);
      firL[i]=Abs(seg[i].fi)+Abs(seg[i].se);
      firR[i]=Abs(L-seg[i].fi)+Abs(L-seg[i].se);
    }
    int ans=inf;
    for(int l=0;l<=n;++l){
      for(int r=l+1;r<=n+1;++r){
        if(ask(l+1,r-1,1,n))continue;
        if(ask(1,l,r,n))continue;
        if(ask(r,n,1,l))continue;
        int res=0;
        for(i=1;i<=l;++i)res+=firL[i];
        for(i=l+1;i<r;++i)res+=dir[i];
        for(i=r;i<=n;++i)res+=firR[i];
        ans=min(ans,res);
      }
    }
    //printf("mid %d\n",ans);
    for(i=1;i<=n;++i)rp[i]=seg[i].se;
    sort(rp+1,rp+1+n);
    for(int l=0;l<=n;++l){
      for(int r=0;r<=n;++r){
        int res=0;
        for(i=1;i<=l;++i){
          res+=seg[i].se<=rp[r]?firL[i]:(seg[i].fi*2+firR[i]);
        }
        for(i=l+1;i<=n;++i){
          res+=seg[i].se<=rp[r]?((L-seg[i].fi)*2+firL[i]):firR[i];
        }
        ans=min(ans,res);
      }
    }
    //printf("fin %d\n",ans);
    return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	public:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(0, Arg3, minDist(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arr1[] = {3, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 14; verify_case(1, Arg3, minDist(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 265467; int Arr1[] = {133548, 103861, 29821, 199848, 92684, 219824, 215859, 62821, 172409, 109235,
38563, 148854, 24742, 174068, 205005, 75922, 87316, 5542, 57484, 40792,
25229, 152216, 21547, 22203, 84712, 231522, 235703, 184895, 100787, 174440,
156904, 84898, 185568, 108732, 260098, 89488, 221604, 104555, 165775, 90444,
81952, 149671, 209674, 22185, 45420, 41928, 16098, 65324, 90870, 35243}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {150289, 135139, 69841, 227226, 177427, 230314, 199175, 81572, 220468, 151049,
40009, 145963, 115246, 252932, 263651, 38434, 120096, 69576, 29789, 115046,
33310, 260771, 5723, 80733, 107864, 142447, 235490, 242149, 124564, 134602,
245962, 7078, 215816, 219864, 190499, 210237, 212894, 142760, 126472, 201935,
119308, 120211, 235235, 19446, 87314, 17286, 61990, 102050, 261812, 257}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 7148670; verify_case(2, Arg3, minDist(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1000000; int Arr1[] = {706292, 756214, 490048, 228791, 567805, 353900, 640393, 562496, 217533, 934149,
938644, 127480, 777134, 999144, 41485, 544051, 417987, 767415, 971662, 959022,
670563, 34065, 518183, 750574, 546576, 207758, 159932, 429345, 670513, 271901,
476062, 392721, 774733, 502586, 915436, 120280, 951729, 699859, 581770, 268966,
79392, 888601, 378829, 350198, 939459, 644983, 605862, 721305, 269232, 137587}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {322468, 673534, 83223, 551733, 341310, 485064, 885415, 927526, 159402, 28144,
441619, 305530, 883149, 413745, 932694, 214862, 677401, 104356, 836580, 300580,
409942, 748444, 744205, 119051, 999286, 462508, 984346, 887773, 856655, 245559,
418763, 840266, 999775, 962927, 779570, 488394, 760591, 326325, 206948, 13999,
285467, 401562, 786209, 169847, 171326, 2901, 296531, 572035, 364920, 939046}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 45670501; verify_case(3, Arg3, minDist(Arg0, Arg1, Arg2)); }
void test_case_4() { int Arg0 = 100; int Arr1[] = {2, 98,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 97,99}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 112; verify_case(1, Arg3, minDist(Arg0, Arg1, Arg2)); }
// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	NarrowPassage ___test;  
 	___test.run_test(-1);  
  //___test.test_case_4();
	return 0;  
}  
// END CUT HERE  
