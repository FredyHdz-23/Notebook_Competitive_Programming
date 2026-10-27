#include <template.h>
//O(E)

const int N=1e5+5, M=2e5+5;
vector<pll> g[N]; bool us[M]; int pt[N], dg[N], m;

vi euler(int s){ // recorrido desde s; válido si sz()==m+1
    vi st={s}, r;
    while(sz(st)){
        int u=st.back();
        while(pt[u]<sz(g[u]) && us[g[u][pt[u]].ss]) pt[u]++;
        if(pt[u]==sz(g[u])) r.pb(u), st.pop_back();
        else{ auto [v,id]=g[u][pt[u]++]; us[id]=1; st.pb(v); }
    }
    reverse(all(r)); return r;
}

int start(int n){ // vértice inicial o -1 si es imposible
    int s=-1, odd=0;
    for(int i=1;i<=n;i++) if(dg[i]&1 && ++odd==1) s=i;
    if(odd!=0 && odd!=2) return -1;
    if(s<0) for(int i=1;i<=n;i++) if(dg[i]){ s=i; break; }
    return s;
}
