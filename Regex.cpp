#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define trav(a, x) for(auto& a : x)

const string NONE = "^";
const string EMPTY = "ε";

const int N = 20; // Number of nodes
string edges[N][N];

int getIndex(char ch) { return ch - 'A'; }

string makeChar(int ch) {
  string ret = "";
  ret += (char)(ch + 'A');
  return ret;
}

void addEdge(char a, char b, string s) {
  edges[getIndex(a)][getIndex(b)] = s;
}

void makeEdges() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      edges[i][j] = NONE;
    }
  }
  addEdge('A', 'A', "b");
  addEdge('A', 'C', EMPTY);
  addEdge('A', 'B', EMPTY);
  addEdge('B', 'B', "a");
  addEdge('B', 'D', "a");
  addEdge('C', 'C', "b");
  addEdge('C', 'E', "a");
  addEdge('D', 'C', "b");
  addEdge('D', 'G', EMPTY);
  addEdge('D', 'D', "a+b");
  addEdge('E', 'C', EMPTY);
  addEdge('E', 'G', EMPTY);
  addEdge('F', 'A', EMPTY);
}


bool isEmpty(int a, int b) {
  return edges[a][b] == NONE;
}

string mergeString(string a, string b) {
  if (a == NONE) return b;
  if (b == NONE) return a;
  return "(" + a + " + " + b + ")";
}

string concateString(string a, string b) {
  if (a == EMPTY) return b;
  if (b == EMPTY) return a;
  return a + b;
}

string bungkus(string a) {
  if (a == "") return "()";
  return a[0] == '(' ? a : "(" + a + ")";
}

string loopString(string a) {
  if (a == NONE) return "";
  if (a == EMPTY) return EMPTY;
  if (a.length() == 1) return a + "*";
  return bungkus(a) + "*";
}

void printTransition(int a, int b) {
  cout << "((" + makeChar(a) + ", " + edges[a][b] + "), " + makeChar(b) + ")" << endl;
}

// You will make a and c while ripping b
void makeMerge(int a, int b, int c) {
  if (edges[a][c] != NONE) {
    cout << "There exists old transition:" << endl;
    printTransition(a, c);
    cout << "Fixed to:" << endl;
  }
  string newString = concateString(edges[a][b], loopString(edges[b][b]));
  newString = concateString(newString, edges[b][c]);
  newString = mergeString(edges[a][c], newString);
  edges[a][c] = newString;
}

void ripEdge(int pos) {
  cout << "Ripping " << makeChar(pos) << endl;
  vector <int> go[2];
  for (int i = 0; i < N; i++) {
    if (pos == i) continue;
    if (!isEmpty(i, pos)) go[0].pb(i);
    if (!isEmpty(pos, i)) go[1].pb(i);
  }
  if (go[0].empty() || go[1].empty()) {
    cout << makeChar(pos) << " not ripped" << endl;
    return;
  }
  cout << "Old Affected Transitions: " << endl;
  cout << "Self loop: ";
  printTransition(pos, pos);
  trav(from, go[0]) printTransition(from, pos);
  trav(to, go[1]) printTransition(pos, to);
  cout << "New Transitions: " << endl;
  trav(from, go[0]) {
    trav(to, go[1]) {
      makeMerge(from, pos, to);
      printTransition(from, to);
    }
  }
  trav(from, go[0]) {
    edges[from][pos] = NONE;
  }
  trav(to, go[1]) {
    edges[pos][to] = NONE;
  }
  edges[pos][pos] = NONE;
}



int main() {
  // fasterios();
  // Make edges here
  makeEdges();
  string s;
  while (cin >> s) {

    if (s == "rip") {
      char tmp;
      cin >> tmp;
      ripEdge(getIndex(tmp));
    }

    if (s == "print") {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (!isEmpty(i, j)) printTransition(i, j);
        }
      }
    }
    
  }
}