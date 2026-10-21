#include <template.h>

struct SQ {
    int n, B; vll a, blk;
    SQ(const vll &v) : n(sz(v)), B(max(1, (int)sqrt(n))), a(v), blk(n / B + 1, 0) {
        for (int i = 0; i < n; i++) blk[i / B] += a[i];
    }
    void upd(int i, ll x) { blk[i / B] += x - a[i]; a[i] = x; }
    ll qry(int l, int r) {       // suma en [l, r], 0-indexado
        ll s = 0;
        while (l <= r && l % B) s += a[l++];             // pedazo suelto inicial
        while (l + B - 1 <= r) s += blk[l / B], l += B;  // bloques completos
        while (l <= r) s += a[l++];                      // pedazo suelto final
        return s;
    }
};
