#include <template.h>

struct DSU {
    vi p; int comps; // comps = componentes actuales
    DSU(int n) : p(n, -1), comps(n) {}
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);   // a = raíz del componente más grande
        p[a] += p[b]; p[b] = a; comps--;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -p[find(x)]; }
};
