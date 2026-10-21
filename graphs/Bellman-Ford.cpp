#include <template.h>
// O(n*m)

const int N = 2e5 + 5;
const ll INF = 4e18;
ll d[N];
vector<array<ll,3>> e;           // aristas {u, v, w}

// retorna true si hay ciclo negativo alcanzable desde s
bool bellman(int s, int n) {
    fill(d, d + n, INF);
    d[s] = 0;
    bool ch = 0;
    for (int i = 0; i < n; i++) {
        ch = 0;
        for (auto [u, v, w] : e)
            if (d[u] != INF && d[u] + w < d[v]) d[v] = d[u] + w, ch = 1;
        if (!ch) break;
    }
    return ch;
}
