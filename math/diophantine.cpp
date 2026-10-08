#include <template.h>

// ---------- 1. Euclides extendido ----------
// Devuelve g = gcd(a,b) y x,y tales que a*x + b*y = g   (a,b >= 0)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

// ---------- 2. Una solución cualquiera de a*x + b*y = c ----------
// Soporta a,b negativos. Requiere (a,b) != (0,0).
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = extgcd(llabs(a), llabs(b), x0, y0);
    if (c % g != 0) return false;
    x0 = (ll)((lll)x0 * (c / g));   // __int128 para evitar overflow
    y0 = (ll)((lll)y0 * (c / g));
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// ---------- 3. Desplazar a la siguiente solución ----------
// Todas las soluciones: x = x0 + k*(b/g),  y = y0 - k*(a/g)
// (aquí a,b ya vienen divididos entre g)
void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

// ---------- 4. Contar soluciones con x en [minx,maxx], y en [miny,maxy] ----------
// Devuelve la cantidad; lx..rx es el rango de x válidos (paso |b/g|).
// Requiere a != 0 y b != 0 (los casos a=0 o b=0 se tratan aparte).
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy,
                      ll &lx, ll &rx) {
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g)) return 0;
    a /= g; b /= g;
    ll sa = a > 0 ? 1 : -1, sb = b > 0 ? 1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx) shift_solution(x, y, a, b, sb);
    if (x > maxx) return 0;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift_solution(x, y, a, b, -sb);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny) shift_solution(x, y, a, b, -sa);
    if (y > maxy) return 0;
    ll lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shift_solution(x, y, a, b, sa);
    ll rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    lx = max(lx1, lx2);
    rx = min(rx1, rx2);
    if (lx > rx) return 0;
    return (rx - lx) / llabs(b) + 1;
}

// ---------- 5. Solución con x >= 0 mínimo ----------
bool min_nonneg_x(ll a, ll b, ll c, ll &x, ll &y) {
    ll g;
    if (!find_any_solution(a, b, c, x, y, g)) return false;
    ll step = llabs(b / g);
    x = ((x % step) + step) % step;
    y = (ll)(((lll)c - (lll)a * x) / b);
    return x >= 0 && y >= 0;
}

// ---------- 6. Congruencia lineal: a*x ≡ b (mod m) ----------
// Soluciones: x = x0 + k*step, con step = m/g. x0 es el menor >= 0.
bool lincong(ll a, ll b, ll m, ll &x0, ll &step) {
    a = ((a % m) + m) % m;
    b = ((b % m) + m) % m;
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (b % g != 0) return false;
    step = m / g;
    x0 = (ll)(((lll)x * (b / g)) % step);
    if (x0 < 0) x0 += step;
    return true;
}

// ---------- 7. Inverso modular (m no necesita ser primo) ----------
// Devuelve -1 si no existe (gcd(a,m) != 1)
ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(((a % m) + m) % m, m, x, y);
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}