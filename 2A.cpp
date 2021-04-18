#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const ll NN = 2e5 + 5;
const ll mo = 1e9 + 7;
const ld eps = 1e-9;
ll n, k, mx = 7, mx2;
vector<char> w;
ll nx[NN][256], fin[NN];
vector<string> isi, state;
map<string, string> p;
string ver(ll x)
{
    if(x)return "Accept";
    return "Reject";
}
ll harus(string s, string a, string b) // Setiap kemunculan a harus segera diikuti b
{
    ll sz = s.length();
    ll az = a.length();
    ll bz = b.length();
    for(ll i = 0; i + az - 1 < sz; i++)
        if(s.substr(i, az) == a)
            if((i + az + bz - 1 >= sz) || (s.substr(i + az, bz) != b))return 0;
    return 1;
}
string rev(string s) // S^R
{
    string ret = s;
    reverse(ret.begin(), ret.end());
    return ret;
}
ll pref(string s, string pf) // Mengandung Prefix pf?
{
    if(s.length() < pf.length())return 0;
    if(s.substr(0, pf.length()) == pf)return 1;
    return 0;
}
ll suff(string s, string sf) // Mengandung Suffix sf?
{
    reverse(s.begin(), s.end());
    reverse(sf.begin(), sf.end());
    return pref(s, sf);
}
ll cnt(string s, char a) // #
{
    ll ret = 0;
    for(auto ch : s)
        if(ch == a)
            ret++;
    return ret;
}
ll substringNonOverlap(string s, string a) 
{
    ll sz = s.length();
    ll az = a.length();
    ll cnt = 0;
    ll i = 0;
    while (i <= sz - az) {
        if (s.substr(i, az) == a) {
            cnt++;
            i += az;
        } else i++;
    }
    return cnt;
}
ll cek(string s) // Cek
{
    ll sz = s.length();

    // return (substringNonOverlap(s, "abca"));
    // return harus(s, "a", "bb");
    // return (cnt(s, 'a') == cnt(s, 'b'));
    // return (pref(s, "101") == 1 && suff(s, "1100") == 0);
    return (suff(s, "101") == 0 && suff(s, "1100") == 0);
}
void rek(string s)
{
    if(s.length() == mx)return;
    isi.pb(s);
    for(auto ch : w)
        rek(s + ch);
}
bool cmp(string a, string b)
{
    if(a.length() < b.length())return 1;
    if(a.length() > b.length())return 0;
    return (a < b);
}
ll sama(string a, string b)
{
    for(auto kata : isi)
        if(cek(a + kata) != cek(b + kata))
            return 0;
    return 1;
}
string gab(string a, string b)
{
    for(auto kata : isi)
        if(cek(a + kata) != cek(b + kata))
            return kata;
    return "x";
}
string ct(string s)
{
    if(s == "")
        return "^";
    return s;
}
int main()
{
    // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    w = {'0', '1'};
    k = w.size();
    mx = 10;
    rek("");
    sort(isi.begin(), isi.end(), cmp);
    for(auto kata : isi)
    {
        ll baru = 1;
        for(auto kata2 : state)
            if(sama(kata, kata2))
            {
                p[kata] = p[kata2];
                baru = 0;
                break;
            }
        if(!baru)continue;

        p[kata] = kata;
        state.pb(kata);
    }
    cout << "State (Final): {";
    ll udh = 0;
    for(auto st : state)
    {
        if(udh)cout << ", ";udh = 1;
        if(cek(st))cout << "(";
        cout << ct(st);
        if(cek(st))cout << ")";
    }
    cout << "}\n";
    for(auto st : state)
    {
        for(auto ch : w)
        {
            cout << "[" << ct(st) << "] " << ch << " [" << ct(p[st + ch]) << "]\n";
            // cout << ct(st) << " :" << ch << " = " << ct(p[st + ch]) << "\n"; 
        }
    }
    
}
    