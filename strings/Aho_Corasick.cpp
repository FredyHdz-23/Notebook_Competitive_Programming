#include <template.h>

struct AC {
    vector<array<int,26>> g{array<int,26>{}};   // g[u][c]: transición (autómata completo tras build)
    vi lk{0}, cnt{0};                            // lk: suffix link, cnt: patrones que terminan en u o en sus sufijos
    int add(const string &s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!g[u][c]) g[u][c] = sz(g), g.pb({}), lk.pb(0), cnt.pb(0);
            u = g[u][c];
        }
        cnt[u]++;
        return u;                                // nodo donde termina el patrón
    }
    void build() {
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < 26; c++) {
                int v = g[u][c];
                if (v) { lk[v] = u ? g[lk[u]][c] : 0; cnt[v] += cnt[lk[v]]; q.push(v); }
                else g[u][c] = g[lk[u]][c];
            }
        }
    }
};


