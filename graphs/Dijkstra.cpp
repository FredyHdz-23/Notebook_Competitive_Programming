// Dijkstra - camino mas corto desde una fuente, pesos NO negativos
// O((V + E) log V)
#include <template.h>

const int N = 2e5 + 5;
const ll INF = 4e18;
vector<pair<int,ll>> g[N];
ll d[N];

void dijkstra(int s, int n) {
    fill(d, d + n, INF);
    priority_queue<pll, vector<pll>, greater<>> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (w > d[u]) continue;
        for (auto [v, c] : g[u])
            if (d[u] + c < d[v]) d[v] = d[u] + c, pq.push({d[v], v});
    }
}
