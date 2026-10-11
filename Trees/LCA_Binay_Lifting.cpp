// Binary lifting	
// preproceso O(n log n)	
// Consulta O(log n)	
// Memoria O(n log n)	Lo más versátil: kth, dist, pesos en el camino
#include <template.h>

struct LCA {
    int n, LOG; vector<vi> up; vi dep;
    LCA(const vector<vi> &g, int root = 0) : n(sz(g)), LOG(__lg(max(n, 2)) + 1), up(LOG, vi(n, root)), dep(n) {
        vi par(n, -1), ord{root};
        for (int i = 0; i < sz(ord); i++) {
            int u = ord[i];
            for (int v : g[u]) if (v != par[u]) par[v] = up[0][v] = u, dep[v] = dep[u] + 1, ord.pb(v);
        }
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++) up[j][v] = up[j-1][up[j-1][v]];
    }
    int kth(int u, int k) { for (int j = 0; k; j++, k >>= 1) if (k & 1) u = up[j][u]; return u; }
    int lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        a = kth(a, dep[a] - dep[b]);
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--) if (up[j][a] != up[j][b]) a = up[j][a], b = up[j][b];
        return up[0][a];
    }
    int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};