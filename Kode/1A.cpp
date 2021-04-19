#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int STAR = 10;
const int CNTOUT = 10;

// Knuth-Morris-Pratt Algorithm, receive a string s and will compute a failure function
typedef vector<int> vi;
vi pi(const string& s) {
  vi p(sz(s));
  rep(i, 1, sz(s)) {
    int g = p[i - 1];
    while (g && s[i] != s[g]) g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}

// Match a string s with pattern pat
vi match(const string& s, const string& pat) {
  vi p = pi(pat + '\0' + s), res;
  rep(i, sz(p) - sz(s), sz(p))
  if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
  return res;
}

// Match a string non overlapping
vi specialMatch(const string& s, const string& pat) {
  vi res = match(s, pat), ret;
  rep(i, 0, sz(res)) if (i == 0 || res[i - 1] + sz(pat) > res[i])
    ret.pb(i);
  return ret;
}


// Proper order
bool cmp(string a, string b) {
  if (sz(a) != sz(b)) return sz(a) < sz(b);
  return a < b;
}

void uniquize(vector<string> &res) {
  sort(all(res), cmp);
  res.erase(unique(all(res)), res.end());
}

vector <string> concat(const vector<string> &A, const vector<string> &B) {
  vector <string> res;
  trav(a, A) trav(b, B) res.pb(a + b);
  uniquize(res);
  return res;
}

// Weird case of concat
vector <string> concat2(const vector<string> &A, const vector<string> &B) {
  vector <string> res;
  trav(a, A) trav(b, B) if (sz(a) == sz(b) && a != b) res.pb(a + b);
  uniquize(res);
  return res;
}

vector <string> power(const vector <string> &A, int expo){
  vector <string> base(1);
  for (int i = 1; i <= expo; i++) base = concat(A, base);
  return base;
}

// res = power(A, start) ∪ power(A, start + 1) ∪ … ∪ power(A, end - 1) ∪ power(A, end)

vector <string> kleene(const vector <string> &A, int st, int ed) {
  vector <string> base = power(A, st);
  vector <string> res = base;
  for (int i = st + 1; i <= ed; i++) {
    base = concat(A, base);
    res.insert(res.end(), all(base));
    uniquize(res);
  }
  return res;
}

vector <string> kleeneStar(const vector <string> &A){
  return kleene(A, 0, STAR);
}

vector <string> kleenePlus(const vector <string> &A){
  return kleene(A, 1, STAR);
}

bool isValid(const string &S) {
  return 1;
  // return 1;
  // return 1;
  // return sz(match(S, "aaa")) == 1;
  // L1 = {w {a, b}* : (4#a(w) < 2#b(w) - 4 )  (|w| ≥ 5)}
  // map <char, int> cnt;
  // trav(cur, S) cnt[cur]++;
  // return (2 * cnt['a'] < cnt['b'] - 2) && S.length() > 5;
  // return cnt['a'] >= cnt['b'];
  // return cnt['a'] && cnt['b'] && 2 * cnt['a'] <= cnt['b'] && cnt['b'] <= 3 * cnt['a'];

  // int cari = S.find("ca");
  // if(cari != sz(S) && cari != -1) return 0;
  // cari = S.find("bb");
  // if(cari != sz(S) && cari != -1) return 0;
  // return 1;
}

vector <string> reverse(const vector <string> &L) {
  vector <string> res;
  trav(cur, L) {
    string tmp = cur; reverse(all(tmp));
    res.pb(tmp);
  }
  return res;
}

bool eachPrefix(const string &S) {
  string curpref = "";
  trav(ch, S) {
    curpref += ch;
    if (!isValid(curpref)) return 0;
  }
  return 1;
}

vector <string> intersection(const vector<string> &L1, const vector<string> &L2, bool isSubtract = 0){
  vector <string> ret;
  set <string> tmp(all(L2));
  trav(S, L1) if(isSubtract^tmp.count(S)) ret.pb(S);
  return ret;
}

int main() {

  vector <string> L2 = {"ca", "c"};
  // vector <string> L3 = {"", "aaa", "cb", "ba", "bbbb"};
  // vector <string> L4 = {"ca", "cb"};

  // vector <string> L1 = concat(L4, L3);
  // vector <string> L5 = concat(kleene(L2, STAR),
  //   kleene(intersection(L2, concat(L4, L3)), STAR));

  // vector <string> L1 = {"a", "ab", "ca", "cc"};
  // vector <string> L2 = {"", "aa", "cb"};
  // vector <string> L3 = {};

  // vector <string> isi = concat(L1, L2);


  // vector <string> A = kleene({"aaa","b"}, 10);
  // vector <string> isi = A;
  // trav(cur, A) if(specialValid(cur, "aaa")) isi.pb(cur);
  // }
  // vector <string> B = A;
  vector <string> isi = kleenePlus(L2);
  isi = kleeneStar(L2);
  isi = kleene(L2, 2, 2);

  // vector <string> B = kleene({"b"}, 12);
  // vector <string> isi = concat2(A, B);
  // vector <string> isi = L2;
  // isi.insert(isi.end(), F1.begin(), F1.end());
  // trav(S, A) if(eachPrefix(S)) isi.pb(S);
  // Filter isi here
  int cntout = CNTOUT;
  uniquize(isi);
  trav(cur, isi) {
    if (isValid(cur)) {
      cout << (cur == "" ? "^" : cur) << endl;
      if (--cntout <= 0) break;
    }
  }
}