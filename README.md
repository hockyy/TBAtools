# Theory of Computation Tools

### 1A. Top 10 Proper Order

[Program 1A](./Kode/1A.cpp)

Cara pakai:

- Ubah fungsi `bool isValid(const string &S);` biar sesuai dengan syarat, bisa pakai fungsi match kalau mau.
- Ubah domain dan letakkan ke `vector <isi>`, bisa pakai `  vector <string> isi = kleene({"a", "b"}, STAR);` Untuk kleene star berapa string pun, bisa juga `kleene({"hock", "yy"}, STAR)`.

### 1B. Pembuktian

Baca-baca materi ini, jangan lupa baca contoh pembuktian juga.

- https://scele.cs.ui.ac.id/pluginfile.php/101649/mod_resource/content/1/HW2101%20v5%20Solusi%20Bag%20B.pdf
- https://cs.lmu.edu/~ray/notes/languagetheory/

### 2A. Membuat DFSM

[Program 2A](./Kode/2A.cpp)

Cara pakai:

- Karakter domainnya ditahan agar jangan kebanyakan, 7-10 mestinya udah cukup
- Modif fungsi `ll cek(string s)` agar menerima string yang diinginkan.
- <img src="README.assets/image-20210418174150693.png" alt="image-20210418174150693" style="zoom:33%;" />
- Jangan lupa mengecek JFF menggunakan text editor, apakah matches nya ada banyak karakter * banyak state dan pastikan kalau dia DFSM. **Jangan lupa menambahkan transisi dari dead state ke dead state juga.**

### [2B. Membuat NDFSM](./2B.cpp)
### [3A. NDFSM -> DFSM](./3A.cpp)
### [3B. Minimalisasi DFSM](./3B.cpp)
### [3C. Kelas Ekivalen](./3C.cpp)
### [4A. Membuat Regex](./4A.cpp)
### [4B. Regex -> NDFSM](.4B.cpp)
### [4C. FSM -> Regex](./4C.cpp)
### [4D. Membuat DFSM dari gabungan beberapa mesin](./4D.cpp)
### [5A. Pumping](./5A.cpp)
### [6A. Regular Grammar](./6A.cpp)
### [6B. CFG](./6A.cpp)
### [6C. CFG -> Chomsky](./6C.cpp)

## FSM to Regex

Use `regex.cpp`.

```c++
void makeEdges() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      edges[i][j] = NONE;
    }
  }
  // You may add the edges here, empty string means ε
  // None means there is no edge
  // Edges are represented by adjacency matrix, with string as its values
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
```

Here is the sample interaction. You can enter each query as `rip <Node>` or `print`, don't rip the last nodes. Please make sure the automata you build at first is already prenormalized with:

- No-self loop Initial Node
- Only one accepting nodes

**First input**

```
rip D
```
```
Ripping D
Old Affected Transitions: 
Self loop: ((D, a+b), D)
((B, a), D)
((D, b), C)
((D, ε), G)
New Transitions: 
((B, a(a+b)*b), C)
((B, a(a+b)*), G)
```
**Second input**

```
print
```
```
((A, b), A)
((A, ε), B)
((A, ε), C)
((B, a), B)
((B, a(a+b)*b), C)
((B, a(a+b)*), G)
((C, b), C)
((C, a), E)
((E, ε), C)
((E, ε), G)
((F, ε), A)
```

## StringGenerator

This will generate the first `CNTOUT`-th string, `uniquize` will remove all `uniquize` 