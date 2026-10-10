#include <template.h>

map<vi,int> mp;   // global: así los IDs son comparables entre árboles distintos
// ID canónico del árbol g enraizado en root (iterativo, sin riesgo de stack overflow)
int canon(const vector<vi> &g, int root) {
    int n = sz(g);
    vi par(n, -1), ord{root}, id(n);
    vector<vi> ch(n);
    for (int i = 0; i < sz(ord); i++)
        for (int v : g[ord[i]]) if (v != par[ord[i]]) par[v] = ord[i], ord.pb(v);
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        sort(all(ch[u]));
        if (!mp.count(ch[u])) { int k = sz(mp); mp[ch[u]] = k; }   // firma nueva => siguiente ID
        id[u] = mp[ch[u]];
        if (par[u] >= 0) ch[par[u]].pb(id[u]);
    }
    return id[root];
}

// 1 o 2 centroides del árbol
vi centroids(const vector<vi> &g) {
    int n = sz(g); vi s(n, 1), par(n, -1), ord{0}, r;
    for (int i = 0; i < sz(ord); i++)
        for (int v : g[ord[i]]) if (v != par[ord[i]]) par[v] = ord[i], ord.pb(v);
    for (int i = n - 1; i > 0; i--) s[par[ord[i]]] += s[ord[i]];
    for (int u : ord) {
        int mx = n - s[u];
        for (int v : g[u]) if (v != par[u]) mx = max(mx, s[v]);
        if (2 * mx <= n) r.pb(u);
    }
    return r;
}

// ID canónico del árbol sin raíz
int tree_id(const vector<vi> &g) {
    int r = INT_MAX;
    for (int c : centroids(g)) r = min(r, canon(g, c));
    return r;
}
// uso 
// con raíz dada:   canon(g1, r1) == canon(g2, r2)
// sin raíz:        tree_id(g1) == tree_id(g2)