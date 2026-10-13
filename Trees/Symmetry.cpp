#include <template.h>
//O(n log n)

map<vi,int> mp;
vector<char> sym;   // sym[id de clase]

// ID canónico del árbol enraizado en root; deja sym[] listo para cada clase
int canon(const vector<vi> &g, int root) {
    int n = sz(g);
    vi par(n, -1), ord{root}, id(n);
    vector<vi> ch(n);
    for (int i = 0; i < sz(ord); i++)
        for (int v : g[ord[i]]) if (v != par[ord[i]]) par[v] = ord[i], ord.pb(v);
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        sort(all(ch[u]));
        if (!mp.count(ch[u])) {
            mp[ch[u]] = sz(mp);
            int odd = 0, oddId = -1;
            const vi &c = ch[u];
            for (int a = 0, b; a < sz(c); a = b) {
                for (b = a; b < sz(c) && c[b] == c[a]; b++);
                if ((b - a) & 1) odd++, oddId = c[a];
            }
            sym.pb(odd == 0 || (odd == 1 && sym[oddId]));
        }
        id[u] = mp[ch[u]];
        if (par[u] >= 0) ch[par[u]].pb(id[u]);
    }
    return id[root];
}

// ¿el árbol enraizado en root es simétrico?
bool simetrico(const vector<vi> &g, int root = 0) { return sym[canon(g, root)]; }

// uso: cout << (simetrico(g) ? "YES" : "NO") << "\n";
