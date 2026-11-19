#include <template.h>

const int N = 200005;
pll p[N];
int n;

// devuelve la menor distancia AL CUADRADO entre dos puntos distintos
ll closest(){
    sort(p, p+n);                          // por x
    set<pll> s;                            // puntos activos como (y, x): ordenados por y
    ll best = LLONG_MAX;                   // mejor distancia² hasta ahora
    int j = 0;                             // p[j..i-1] son los que siguen en el set

    for(int i = 0; i < n; i++){
        ll d = (ll)ceil(sqrtl((long double)best));    // radio de búsqueda

        // 1) sacar del set los que están a >= d en x (ya no pueden mejorar)
        while(j < i && p[i].ff - p[j].ff >= d){
            s.erase({p[j].ss, p[j].ff});
            j++;
        }

        // 2) mirar solo los que tienen y dentro de [y-d, y+d]
        auto it = s.lower_bound({p[i].ss - d, LLONG_MIN});
        for(; it != s.end() && it->ff - p[i].ss < d; ++it){
            ll dx = p[i].ff - it->ss;
            ll dy = p[i].ss - it->ff;
            best = min(best, dx*dx + dy*dy);
        }

        // 3) agregar el punto actual al set
        s.insert({p[i].ss, p[i].ff});
    }
    return best;
}