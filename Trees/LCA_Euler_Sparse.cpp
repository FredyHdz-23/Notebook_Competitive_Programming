// Euler/preorden + sparse
// Preproceso	O(n log n)	
// Consulta O(1)	
// Memoria O(n log n)	Muchísimas consultas, solo LCA
#include <template.h>

struct LCA {
    vector<vi> st; vi tin;
    LCA(const vector<vi> &g, int root = 0) : tin(sz(g)) {
        int n = sz(g), t = 0, LOG = __lg(max(n, 2)) + 1;
        vi par(n, root), stk{root}, ord(n);
        while (!stk.empty()) {                       // preorden iterativo
            int u = stk.back(); stk.pop_back();
            tin[u] = t; ord[t++] = u;
            for (int v : g[u]) if (v != par[u]) par[v] = u, stk.pb(v);
        }
        st.assign(LOG, vi(n));
        for (int i = 0; i < n; i++) st[0][i] = par[ord[i]];
        auto mn = [&](int x, int y) { return tin[x] < tin[y] ? x : y; };
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = mn(st[j-1][i], st[j-1][i + (1 << (j-1))]);
    }
    int lca(int a, int b) {
        if (a == b) return a;
        int l = tin[a], r = tin[b];
        if (l > r) swap(l, r);
        l++;                                         // el rango es (l, r]
        int k = __lg(r - l + 1);
        int x = st[k][l], y = st[k][r - (1 << k) + 1];
        return tin[x] < tin[y] ? x : y;
    }
};