#include <template.h>

const int N = 100005;
pll p[N], h[2*N];
int n;

// producto cruz de (b-a) x (c-a): >0 izquierda, <0 derecha, 0 colineal
ll cr(pll a, pll b, pll c){
    return (b.ff-a.ff)*(c.ss-a.ss) - (b.ss-a.ss)*(c.ff-a.ff);
}

// deja el hull en h[0..k-1], antihorario; devuelve k
int hull(){
    sort(p, p+n);
    n = unique(p, p+n) - p;
    if(n < 3){
        for(int i = 0; i < n; i++) h[i] = p[i];
        return n;
    }
    int k = 0;
    // cadena inferior: izquierda -> derecha
    for(int i = 0; i < n; i++){
        while(k >= 2 && cr(h[k-2], h[k-1], p[i]) <= 0) k--;   // el del medio sobra
        h[k++] = p[i];
    }
    // cadena superior: derecha -> izquierda
    // t = k+1 evita sacar puntos de la cadena inferior ya armada
    for(int i = n-2, t = k+1; i >= 0; i--){
        while(k >= t && cr(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }

    return k - 1;                          // el último repite al primero
}