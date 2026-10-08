#include <template.h>

struct RDSU {
    vi p; vector<pii> st; int comps;
    RDSU(int n) : p(n, -1), comps(n) {}
    int find(int x) { while (p[x] >= 0) x = p[x]; return x; }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        st.pb({b, p[b]});
        p[a] += p[b]; p[b] = a; comps--;
        return true;
    }
    int snap() { return sz(st); }
    void rollback(int s) {
        while (sz(st) > s) {
            auto [b, old] = st.back(); st.pop_back();
            p[p[b]] -= old; p[b] = old; comps++;
        }
    }
};