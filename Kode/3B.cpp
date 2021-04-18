/*
Author : Hocky Yudhiono
Thu 15 Apr 2021 12:05:21 AM WIB

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem, think of it when you're making subtasks
   like when problemsetting.
6. Matching problems can be solved with DP and vice versa.
   Counting and optimizing problems can be solved with DP.
   Try bitmasking when N is small. When big, consider greedy-ing.

*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

typedef long long LL;
typedef long long ll;
typedef long double LD;
typedef vector<int> vi;
typedef pair<LL, LL> PLL;
typedef pair<LL, int> PLI;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef vector<vector<LL>> VVL;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define popf pop_front
#define pf push_front
#define popb pop_back
#define mp make_pair
#define pb push_back
#define remove erase
#define fi first
#define se second

// If the time limit is strict, try not to use long double

// Remember to undefine if the problem is interactive
#define endl '\n'
#define DEBUG(X) cout << ">>> DEBUG(" << __LINE__ << ") " << #X << " = " << (X) << endl

const double EPS = 1e-9;
const int INFMEM = 63;
const int INF = 1061109567;
const LL LINF = 4557430888798830399LL;
const double DINF = numeric_limits<double>::infinity();
const LL MOD = 1000000007;
const int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
// Do dir^1 to get reverse direction
const char dch[4] = {'R', 'L', 'D', 'U'};
// const string ds[8] = {"E","W","S","N","SE","NW","SW","NE"};
const double PI = 3.141592653589793;

inline void open(string a) {
  freopen((a + ".in").c_str(), "r", stdin);
  freopen((a + ".out").c_str(), "w", stdout);
}

inline void fasterios() {
  // Do not use if interactive
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  // cout << fixed << setprecision(10);
}

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (((x) & (y)) == (y))   // warning: evaluates y twice
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))

namespace utility {

const char EMPTY = '^';

int getIndex(char ch) {
  if (ch == EMPTY) return -1;
  return ch - 'A';
}

char makeChar(int ch) {
  if (ch == -1) return EMPTY;
  return (char)(ch + 'A');
}

template <class T>
void uniquize(vector <T> &V) {
  sort(all(V));
  V.erase(unique(all(V)), V.end());
}
};

using namespace utility;

const vector <char> CH = {'a', 'b'};
const int N = 7;
const int initial = 0;
const int ALL = (1 << N) - 1;

namespace DFSM {
int accept;
vector<vector<int>> edge;
vector<int> partition;

void addEdge(char a, char b, char s) {
  edge[getIndex(a)][s - 'a'] = getIndex(b);
}

int transformToBits(vector <char> c) {
  int ret = 0;
  trav(ch, c) {
    BIT_SET(ret, getIndex(ch));
  }
  return ret;
}

void makeEdge() {
  edge.resize(N, vector<int>(sz(CH)));
  accept = transformToBits({'B', 'F'});
  addEdge('A', 'B', 'a');
  addEdge('A', 'E', 'b');
  addEdge('B', 'D', 'a');
  addEdge('B', 'C', 'b');
  addEdge('C', 'B', 'a');
  addEdge('C', 'E', 'b');
  addEdge('D', 'D', 'a');
  addEdge('D', 'G', 'b');
  addEdge('E', 'F', 'a');
  addEdge('E', 'G', 'b');
  addEdge('F', 'G', 'a');
  addEdge('F', 'C', 'b');
  addEdge('G', 'D', 'a');
  addEdge('G', 'G', 'b');
}


string getStringState(int s) {
  string res = "";
  bool first = 1;
  for (int j = 0; j < N; j++) {
    if (BIT_CHECK(s, j)){
      if(!first) res += ", ";
      res += makeChar(j);
      first = 0;
    }
  }
  if (res == "") res = "∅";
  return "{" + res + "}";
}

void printPartition() {
  cout << "Partisi = ";
  for(int i = 0;i < sz(partition);i++){
    int cur = partition[i];
    cout << getStringState(cur);
    if(i != sz(partition) - 1) cout << ", ";
  }
  cout << "" << endl;
}

void minimalizeDFSM() {
  partition.pb(accept);
  partition.pb(ALL^accept);
  int deleteIdx;
  do{
    printPartition();
    vector <int> idxPartition(N);
    for(int j = 0;j < sz(partition);j++){
      for(int i = 0;i < N;i++){
        if(BIT_CHECK(partition[j], i))
          idxPartition[i] = j;
      }
    }
    vector <string> changes;
    deleteIdx = -1;
    vector <int> newPartition;
    for(int p = 0;p < sz(partition);p++){
      for(int i = 0;i < sz(CH);i++){
        map <int, int> newTo;
        int part = partition[p];
        // Try to use this character
        for(int j = 0;j < N;j++) if(BIT_CHECK(part, j)){
          BIT_SET(newTo[idxPartition[edge[j][i]]], j);
        }
        if(newTo.size() == 1) continue;
        cout << endl;
        printf("// Partition happening\n");
        for(int j = 0;j < N;j++) if(BIT_CHECK(part, j)){
          printf("δ(%c, %c) = %c\n", makeChar(j), CH[i], makeChar(edge[j][i]));
        }
        for (auto to : newTo) {
          printf("%s akan bertransisi ke partisi %s\n",
            getStringState(to.se).c_str(),
            getStringState(partition[to.fi]).c_str());
        }
        cout << endl;
        printf("%s akan dipartisi menjadi:", getStringState(part).c_str());
        bool first = 1;
        for(auto to : newTo){
          if(!first) printf(", ");
          cout << getStringState(to.se);
          newPartition.pb(to.se);
          first = 0;
        }
        printf("\n");
        deleteIdx = p;
        break;
      }
    }
    if(deleteIdx == -1) break;
    vector <int> nextPartition;
    for(int p = 0;p < sz(partition);p++){
      if(p != deleteIdx){
        nextPartition.pb(partition[p]);
      }else{
        trav(part, newPartition){
          nextPartition.pb(part);
        }
      }
    }
    swap(nextPartition, partition);
  }while(deleteIdx != -1);
}


}

int main() {
  DFSM::makeEdge();
  DFSM::minimalizeDFSM();
  return 0;
}