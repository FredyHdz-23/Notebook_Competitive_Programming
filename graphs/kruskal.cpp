// Kruskal - Minimum Spanning Tree usando DSU
// O(E log E)
#include <template.h>
vector<tuple<ll,int,int>> E;   // E.pb({w, a, b}), nodos 0..n-1
// vector<tuple<ll,int,int>> M; para reconstruir en cada if M.pb(w, a, b)

// ll kruskal(int n) {
//     sort(all(E)); DSU d(n); ll c = 0;
//     for (auto [w, a, b] : E) if (d.unite(a, b)) c += w;
//     return d.comps == 1 ? c : -1;   // -1 si el grafo no es conexo
// }
