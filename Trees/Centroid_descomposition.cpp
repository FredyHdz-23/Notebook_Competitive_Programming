// Devuelve el/los centroide(s): 1 o 2 nodos. O(n)

#include <template.h>

vi centroids(const vector<vi> &g) {
    int n = sz(g); vi par(n, -1), ord{0}, s(n, 1), mx(n), r;
    for (int i = 0; i < sz(ord); i++)
        for (int v : g[ord[i]]) if (v != par[ord[i]]) par[v] = ord[i], ord.pb(v);
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (max(mx[u], n - s[u]) * 2 <= n) r.pb(u);          // ninguna componente supera n/2
        if (i) s[par[u]] += s[u], mx[par[u]] = max(mx[par[u]], s[u]);
    }
    return r;
}