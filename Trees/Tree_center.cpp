// Devuelve el/los centro(s): 1 o 2 nodos. O(n)
#include <template.h>

vi center(const vector<vi> &g) {
    int n = sz(g), l = 0, rem = n; vi d(n), q;
    for (int i = 0; i < n; i++) if ((d[i] = sz(g[i])) <= 1) q.pb(i);
    while (rem > 2) {
        int r = sz(q); rem -= r - l;            // se quita toda la capa actual de hojas
        for (; l < r; l++) for (int v : g[q[l]]) if (--d[v] == 1) q.pb(v);
    }
    return vi(q.begin() + l, q.end());
}