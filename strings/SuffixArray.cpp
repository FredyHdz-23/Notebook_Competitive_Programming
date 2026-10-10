// sa[i] = posición donde empieza el i-ésimo sufijo en orden lexicográfico
// lcp[i] = longitud del prefijo común entre sa[i] y sa[i-1]
#include <template.h>

struct SA {
    string s; int n; vi sa, rk, lcp;
    SA(string t) : s(t + '$'), n(sz(s)), sa(n), rk(n), lcp(n) {
        vi c(n), p(n), q(n), d(n), cnt(n);
        iota(all(p), 0);
        sort(all(p), [&](int a, int b) { return s[a] < s[b]; });   // única vez que se usa sort
        int cl = 1; c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = c[p[i-1]] + (s[p[i]] != s[p[i-1]]), cl = c[p[i]] + 1;
        for (int k = 1; k < n && cl < n; k <<= 1) {
            auto nx = [&](int x) { return x + k >= n ? x + k - n : x + k; };
            for (int i = 0; i < n; i++) { int x = p[i] - k; q[i] = x < 0 ? x + n : x; }
            fill(all(cnt), 0);
            for (int i = 0; i < n; i++) cnt[c[q[i]]]++;
            for (int i = 1; i < cl; i++) cnt[i] += cnt[i-1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[c[q[i]]]] = q[i];
            d[p[0]] = 0;
            for (int i = 1; i < n; i++)
                d[p[i]] = d[p[i-1]] + (c[p[i]] != c[p[i-1]] || c[nx(p[i])] != c[nx(p[i-1])]);
            cl = d[p[n-1]] + 1; swap(c, d);
        }
        sa = p;
        for (int i = 0; i < n; i++) rk[sa[i]] = i;                 // inversa de sa
        for (int i = 0, k = 0; i < n; i++) {                       // Kasai
            if (!rk[i]) { k = 0; continue; }
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[rk[i]] = k; if (k) k--;
        }
    }
};