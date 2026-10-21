// Sparse Table - RMQ (Range Minimum Query) estatico, sin updates
// O(n log n) build, O(1) query
#include <template.h>

struct ST {
    vector<vl> sp; vi lg;
    ST(const vl &a) {
        int n = sz(a);
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        sp.assign(lg[n] + 1, vl(n));
        sp[0] = a;
        for (int k = 1; k <= lg[n]; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = min(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);
    }
    ll q(int l, int r) {          // minimo en [l, r], 0-indexado
        int k = lg[r - l + 1];
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
