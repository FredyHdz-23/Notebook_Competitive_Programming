// Fenwick Tree (BIT) - suma de prefijos con update puntual
// O(log n) por operacion
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT {
    int n;
    vll tree;

    BIT(int n = 0) : n(n), tree(n + 1, 0) {}

    void update(int i, ll delta = 1) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    ll query(int i) { // suma [1, i]
        ll s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }

    ll query(int l, int r) { return query(r) - query(l - 1); } // suma [l, r]
};
