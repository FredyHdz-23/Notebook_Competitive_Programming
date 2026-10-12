#include <template.h>
// O(k^3 log n)

typedef vector<vll> Mat;
Mat mul(const Mat &a, const Mat &b) {
    int n = sz(a); Mat c(n, vll(n));
    for (int i = 0; i < n; i++) for (int k = 0; k < n; k++) if (a[i][k])
        for (int j = 0; j < n; j++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}
Mat mpow(Mat a, ll e) {
    int n = sz(a); Mat r(n, vll(n));
    for (int i = 0; i < n; i++) r[i][i] = 1;
    for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
}