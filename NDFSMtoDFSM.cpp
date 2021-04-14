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

const vector <char> CH = {EMPTY, 'a', 'b'};
const int N = 6;
const int initial = 0;

namespace NDFSM {
int accept;
vector<vector<vector<char>>> edge;
vector<int> eps;
vector<int> activeStates;
vector<int> acceptingStates;

void addEdge(char a, char b, char s) {
  edge[getIndex(a)][getIndex(b)].pb(s);
}

int transformToBits(vector <char> c) {
  int ret = 0;
  trav(ch, c) {
    BIT_SET(ret, getIndex(ch));
  }
  return ret;
}

void makeEdge() {
  edge.resize(N, vector<vector<char>>(N));
  eps.resize(N);
  accept = transformToBits({'C'});
  addEdge('A', 'B', 'b');
  addEdge('A', 'E', EMPTY);
  addEdge('B', 'C', 'a');
  addEdge('C', 'D', 'b');
  addEdge('D', 'A', EMPTY);
  addEdge('E', 'F', 'a');
  addEdge('F', 'C', EMPTY);

}

void getEPS() {

  printf("Printing q Eps(q)\n");

  for (int i = 0; i < N; i++) {
    BIT_SET(eps[i], i);
    for (int j = 0; j < N; j++) {
      if (count(all(edge[i][j]), EMPTY)) {
        BIT_SET(eps[i], j);
      }
    }
  }

  for (int iter = 0; iter < N; iter++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (BIT_CHECK(eps[i], j)) {
          eps[i] |= eps[j];
        }
      }
    }
  }

  for (int i = 0; i < N; i++) {
    cout << makeChar(i) << ":";
    for (int j = 0; j < N; j++) {
      if (BIT_CHECK(eps[i], j))
        cout << " " << makeChar(j);
    }
    cout << endl;
  }

}

string getStringState(int s) {
  string res = "";
  for (int j = 0; j < N; j++) {
    if (BIT_CHECK(s, j)) res += makeChar(j);
  }
  if (res == "") res = "∅";
  return res;
}

void printActiveState() {
  cout << "Active states = {";
  trav(cur, activeStates) {
    cout << getStringState(cur) << ", ";
  }
  cout << "}" << endl;
}

void transformToDFSM() {
  // Push active states
  activeStates.pb(eps[initial]);
  for (int i = 0; i < sz(activeStates); i++) {
    printActiveState();
    int act = activeStates[i];
    string state = getStringState(act);
    cout << "Computing " << state << endl;
    for (int c = 1; c < sz(CH); c++) {
      vector <int> to;
      for (int j = 0; j < N; j++) if (BIT_CHECK(act, j)) {
          int curTo = 0;
          for (int k = 0; k < N; k++) {
            if (count(all(edge[j][k]), CH[c])) {
              BIT_SET(curTo, k);
            }
          }
          to.pb(curTo);
        }
      printf("δ(%s, %c) = eps(", state.c_str(), CH[c]);
      int totalTos = 0;
      string tos = "";
      if (to.empty()) {
        tos = "∅";
      } else {
        tos = getStringState(to[0]);
        totalTos |= to[0];
        for (int j = 1; j < sz(to); j++) {
          tos += " ∪ " + getStringState(to[j]);
          totalTos |= to[j];
        }
      }
      int nx = 0;
      for (int j = 0; j < N; j++) if (BIT_CHECK(totalTos, j)) {
          nx |= eps[j];
        }
      printf("%s) = eps(%s) = %s\n", tos.c_str(),
             getStringState(totalTos).c_str(), getStringState(nx).c_str());
      if (!count(all(activeStates), nx)) activeStates.pb(nx);
    }
  }
  printActiveState();
  printf("Active states tidak bertambah.\n");
  printf("Accepting state = {");
  trav(cur, activeStates) {
    if (cur & accept) cout << getStringState(cur) << ", ";
  }
  cout << "}\n";
}

}

int main() {
  NDFSM::makeEdge();
  NDFSM::getEPS();
  NDFSM::transformToDFSM();
  return 0;
}