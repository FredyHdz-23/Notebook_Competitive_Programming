#include <template.h>
// ---------- Dinic O(V^2*E), unitario O(E*sqrt(V)) ----------
const int N=1e5+5, M=4e5+5; const ll INF=1e18;
vi g[N]; int to[M], ec, lv[N], it[N]; ll cp[M];

void add(int a,int b,ll c,ll r=0){ // r=c si es no dirigida
    g[a].pb(ec); to[ec]=b; cp[ec++]=c;
    g[b].pb(ec); to[ec]=a; cp[ec++]=r;
}
void reset(int n){ ec=0; for(int i=0;i<=n;i++) g[i].clear(); }

bool bfs(int s,int t,int n){
    fill(lv,lv+n+1,-1); queue<int> q; q.push(s); lv[s]=0;
    while(sz(q) && lv[t]<0){ // corte temprano
        int u=q.front(); q.pop();
        for(int id:g[u]) if(cp[id]>0 && lv[to[id]]<0) lv[to[id]]=lv[u]+1, q.push(to[id]);
    }
    return lv[t]>=0;
}
ll dfs(int u,int t,ll f){
    if(u==t) return f;
    ll p=0;
    for(int &i=it[u];i<sz(g[u]);i++){
        int id=g[u][i];
        if(cp[id]>0 && lv[to[id]]==lv[u]+1){
            ll r=dfs(to[id],t,min(f-p,cp[id]));
            if(r){ cp[id]-=r; cp[id^1]+=r; p+=r; if(p==f) return p; }
        }
    }
    lv[u]=-1; // callejón sin salida en esta fase
    return p;
}
ll dinic(int s,int t,int n){
    ll fl=0;
    while(bfs(s,t,n)){ fill(it,it+n+1,0); fl+=dfs(s,t,INF); }
    return fl;
}

vector<pii> mincut(int s,int n){ // llamar DESPUÉS de dinic; devuelve aristas (a,b) del corte
    vector<char> v(n+1,0); queue<int> q; q.push(s); v[s]=1;
    while(sz(q)){
        int u=q.front(); q.pop();
        for(int id:g[u]) if(cp[id]>0 && !v[to[id]]) v[to[id]]=1, q.push(to[id]);
    }
    vector<pii> r;
    for(int a=1;a<=n;a++) if(v[a])
        for(int id:g[a]) if(!(id&1) && !v[to[id]]) r.pb({a,to[id]});
    return r;
}
