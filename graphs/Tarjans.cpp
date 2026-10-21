#include <template.h>

// Tarjan iterativo. Retorna cantidad de SCC; comp[u] = id de su componente.
// Los ids salen en orden topologico inverso (0 = sumidero, cnt-1 = fuente).
int tarjan(const vector<vi> &g, vi &comp) {
    int n = sz(g), timer = 0, cnt = 0;
    vi tin(n, -1), low(n), it(n, 0), st, call;
    comp.assign(n, -1);
    for (int s = 0; s < n; s++) {
        if (tin[s] != -1) continue;
        tin[s] = low[s] = timer++;
        st.pb(s); call.pb(s);
        while (!call.empty()) {
            int u = call.back();
            if (it[u] < sz(g[u])) {
                int v = g[u][it[u]++];
                if (tin[v] == -1) {
                    tin[v] = low[v] = timer++;
                    st.pb(v); call.pb(v);
                } else if (comp[v] == -1) low[u] = min(low[u], tin[v]);
            } else {
                if (low[u] == tin[u]) {
                    int v;
                    do { v = st.back(); st.pop_back(); comp[v] = cnt; } while (v != u);
                    cnt++;
                }
                call.pop_back();
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[u]);
            }
        }
    }
    return cnt;
}
