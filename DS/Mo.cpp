#include <template.h>

struct Mo {
    int B; vector<array<int,3>> qs;
    Mo(int n) : B(max(1, (int)sqrt(n))) {}
    void add_q(int l, int r) { qs.pb({l, r, sz(qs)}); }   // 0-indexado
    template<class A, class R, class G>
    vll run(A add, R rem, G get) {
        sort(all(qs), [&](auto &x, auto &y) {
            int bx = x[0] / B, by = y[0] / B;
            if (bx != by) return bx < by;
            return (bx & 1) ? x[1] > y[1] : x[1] < y[1];  // zigzag
        });
        vll ans(sz(qs));
        int L = 0, R = -1;
        for (auto [l, r, id] : qs) {
            while (L > l) add(--L);      // primero ampliar
            while (R < r) add(++R);
            while (L < l) rem(L++);      // despues reducir
            while (R > r) rem(R--);
            ans[id] = get();
        }
        return ans;
    }
};
