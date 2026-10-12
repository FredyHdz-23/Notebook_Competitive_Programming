#include <template.h>

// devuelve {F(n), F(n+1)} mod MOD, con F(0)=0, F(1)=1
pll fib(ll n) {
    if (!n) return {0, 1};
    auto [a, b] = fib(n >> 1);
    ll c = a * ((2 * b - a + MOD) % MOD) % MOD;     // F(2k)
    ll d = (a * a + b * b) % MOD;                   // F(2k+1)
    return n & 1 ? pll(d, (c + d) % MOD) : pll(c, d);
}

//matriz
typedef array<array<ll,2>,2> M;
M mul(const M &a, const M &b) {
    M c{};
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++)
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}
ll fibm(ll n) {
    M r = {{{1, 0}, {0, 1}}}, b = {{{1, 1}, {1, 0}}};
    for (; n; n >>= 1, b = mul(b, b)) if (n & 1) r = mul(r, b);
    return r[0][1];
}