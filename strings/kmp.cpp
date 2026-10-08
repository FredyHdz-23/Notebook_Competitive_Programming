#include <template.h>
// O(n+m)

vi pi_fn(const string &s) {
    int n = sz(s); vi p(n);
    for (int i = 1; i < n; i++) {
        int j = p[i-1];
        while (j && s[i] != s[j]) j = p[j-1];
        p[i] = j + (s[i] == s[j]);
    }
    return p;
}

// posiciones (0-indexed) donde t aparece en s
vi find_all(const string &s, const string &t) {
    vi p = pi_fn(t + '#' + s), r;
    for (int i = sz(t) + 1; i < sz(p); i++)
        if (p[i] == sz(t)) r.pb(i - 2 * sz(t));
    return r;
}