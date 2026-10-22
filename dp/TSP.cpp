const ll INF = 4e18;

#include <template.h>

// d[i][j] = costo de ir de i a j. Retorna el costo minimo del ciclo, o INF si no existe.
ll tsp(const vector<vll> &d) {
    int n = sz(d), full = (1 << n) - 1;
    vector<vll> dp(1 << n, vll(n, INF));
    dp[1][0] = 0;
    for (int mask = 1; mask <= full; mask++) {
        if (!(mask & 1)) continue;                      // todo camino parte de 0
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1) || dp[mask][i] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (mask >> j & 1) continue;            // j ya visitada
                int nm = mask | (1 << j);
                dp[nm][j] = min(dp[nm][j], dp[mask][i] + d[i][j]);
            }
        }
    }
    ll ans = INF;
    for (int i = 0; i < n; i++)
        if (dp[full][i] < INF && d[i][0] < INF) ans = min(ans, dp[full][i] + d[i][0]);
    return ans;
}
