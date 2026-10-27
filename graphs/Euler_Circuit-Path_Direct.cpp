#include <template.h>
//O(e)

const int N=1e5+5, M=2e5+5;
vector<pll> g[N]; bool us[M]; int pt[N], ig[N], og[N], m, D;

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
    int s=-1,a=0,b=0;
    for(int i=1;i<=n;i++){
        if(!D){ if(og[i]&1){ if(++a==1) s=i; } }
        else{ int d=og[i]-ig[i]; if(d==1) a++, s=i; else if(d==-1) b++; else if(d) return -1; }
    }
    if(!D? (a!=0&&a!=2) : (a>1||b>1||a!=b)) return -1;
    if(s<0) for(int i=1;i<=n;i++) if(og[i]){ s=i; break; }
    return s;
}
