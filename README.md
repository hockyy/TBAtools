# Theory of Computation Tools

### FSM to Regex

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

