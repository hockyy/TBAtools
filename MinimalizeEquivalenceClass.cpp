#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

namespace utility
{

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

// Do start = isStar ⊕ 1, end = expo
// power(A, start) ∪ power(A, start + 1) ∪ … ∪ power(A, end - 1) ∪ power(A, end)

vector <string> kleene(const vector <string> &A, int expo, bool isStar = 1) {
  vector <string> base = {""};
  vector <string> res = {};
  if (isStar) res.pb("");
  res.insert(res.end(), all(base));
  for (int i = 1; i <= expo; i++) {
    base = concat(A, base);
    res.insert(res.end(), all(base));
  }
  uniquize(res);
  return res;
}

}

const string EMPTY = "^";
vector<string> charList = {"a", "b"};

vector<string> state, isi;
map<string, string> parent;


bool valid(const string &S) {
  return S.find("aaa") != string::npos;
}

bool isSame(string a, string b) {
    trav(kata, isi) if(valid(a + kata) != valid(b + kata)) return 0;
    return 1;
}

string mergeString(string a, string b) {
    for(auto kata : isi) if(valid(a + kata) != valid(b + kata)) return kata;
    return "x";
}

// Normalize string
string normal(string s) { return s == "" ? EMPTY : s; }

int main() {

    isi = utility::kleene(charList, 5);
    utility::uniquize(isi);

    trav(kata, isi){
        bool newState = 1;
        trav(kata2, state) if(isSame(kata, kata2)) {
            parent[kata] = parent[kata2];
            newState = 0;
            break;
        }
        if(!newState) continue;
        parent[kata] = kata;
        state.pb(kata);
    }

    for(auto kata : isi) {
        cout << normal(kata) << "   ";
        if(kata == parent[kata]) {
            printf("Buat [%s]:\n", normal(kata).c_str());
            for(auto kata2 : state) {
                if(kata2 == kata) break;
                printf("distinguishable dengan [%s] karena suffix %s\n",
                    normal(kata2).c_str(), normal(mergeString(kata, kata2)).c_str());
            }
        } else {
            printf("Gabung [%s], karena indistinguishable dengan %s\n",
                normal(parent[kata]).c_str(), normal(parent[kata]).c_str());
        }
        cout << endl;
        if(kata == state.back()) break;
        if(kata.length() > 4) break;
    }
    for(auto st : state) {
        for(auto ch : charList)
            cout << normal(st) << " :" << ch << " = " << normal(parent[st + ch]) << "\n";
    }
    cout << "Final : \n";
    for(auto st : state)
        if(valid(st))
            cout << normal(st) << "\n";
}
