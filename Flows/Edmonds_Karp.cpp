#include <template.h>

// O(E^2 * V)
struct EK {
    struct E { int to; ll cap; };
    vector<E> e; vector<vi> g; vi par;
    EK(int n) : g(n), par(n) {}
    int add(int a, int b, ll c) {
        g[a].pb(sz(e)); e.pb({b, c});
        g[b].pb(sz(e)); e.pb({a, 0});
        return sz(e) - 2;                          // id de la arista
    }
    ll flow(int s, int t) {                        // requiere s != t
        ll r = 0;
        while (true) {
            fill(all(par), -1);
            queue<int> q; q.push(s);
            while (!q.empty() && par[t] < 0) {
                int u = q.front(); q.pop();
                for (int id : g[u]) {
                    int v = e[id].to;
                    if (e[id].cap > 0 && par[v] < 0 && v != s) par[v] = id, q.push(v);
                }
            }
            if (par[t] < 0) break;
            ll f = INF;
            for (int v = t; v != s; v = e[par[v] ^ 1].to) f = min(f, e[par[v]].cap);
            for (int v = t; v != s; v = e[par[v] ^ 1].to) e[par[v]].cap -= f, e[par[v] ^ 1].cap += f;
            r += f;
        }
        return r;
    }
};