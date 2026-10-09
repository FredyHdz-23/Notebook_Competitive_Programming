// sa[i] = posición donde empieza el i-ésimo sufijo en orden lexicográfico
// lcp[i] = longitud del prefijo común entre sa[i] y sa[i-1]
#include <template.h>

struct SA {
    string s; int n; vi sa, rk, lcp;
    SA(string t) : s(t + '$'), n(sz(s)), sa(n), rk(n), lcp(n) {
        vi tmp(n); iota(all(sa), 0);
        for (int i = 0; i < n; i++) rk[i] = s[i];
        for (int k = 1; k < n; k <<= 1) {
            auto key = [&](int a) { return pii(rk[a], a + k < n ? rk[a + k] : -1); };
            sort(all(sa), [&](int a, int b) { return key(a) < key(b); });
            for (int i = 0; i < n; i++)
                tmp[sa[i]] = i ? tmp[sa[i-1]] + (key(sa[i-1]) < key(sa[i])) : 0;
            rk = tmp;
            if (rk[sa[n-1]] == n - 1) break;
        }
        for (int i = 0; i < n; i++) rk[sa[i]] = i;      // rk = inversa de sa (Kasai)
        for (int i = 0, k = 0; i < n; i++) {
            if (!rk[i]) { k = 0; continue; }
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[rk[i]] = k; if (k) k--;
        }
    }
};