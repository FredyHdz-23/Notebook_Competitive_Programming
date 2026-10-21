#include <template.h>
//O(E * log(V)) 

ll prim(const vector<vector<pil>> &g) {
    int n = sz(g), usados = 0;
    ll total = 0;
    vector<char> vis(n, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 0});                       // empiezo en el nodo 0 con costo 0
    while (!pq.empty() && usados < n) {
        auto [w, u] = pq.top(); pq.pop();
        if (vis[u]) continue;              // ya estaba en el árbol
        vis[u] = 1; total += w; usados++;
        for (auto [v, c] : g[u])
            if (!vis[v]) pq.push({c, v});
    }
    return usados == n ? total : -1;
}
