#include <template.h>

const int N = 2e5 + 5;
vi g[N], st, cs;
int tin[N], low[N], comp[N], it[N], T, C;   // comp[u] = id de la SCC (empieza en 1)

void tarjan(int s) {
    tin[s] = low[s] = ++T; st.pb(s); cs.pb(s);
    while (!cs.empty()) {
        int u = cs.back();
        if (it[u] < sz(g[u])) {
            int v = g[u][it[u]++];
            if (!tin[v]) tin[v] = low[v] = ++T, st.pb(v), cs.pb(v);
            else if (!comp[v]) low[u] = min(low[u], tin[v]);
        } else {
            if (low[u] == tin[u]) {
                int v; C++;
                do v = st.back(), st.pop_back(), comp[v] = C; while (v != u);
            }
            cs.pop_back();
            if (!cs.empty()) low[cs.back()] = min(low[cs.back()], low[u]);
        }
    }
}
