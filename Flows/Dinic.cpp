#include <template.h>

const int N=1e5+5, M=4e5+5; const ll INF=1e18;
vi g[N]; int to[M], ec; ll cp[M];
void add(int a,int b,ll c,ll r=0){ // r=c si es no dirigida
    g[a].pb(ec); to[ec]=b; cp[ec++]=c;
    g[b].pb(ec); to[ec]=a; cp[ec++]=r;
}

// ---------- Dinic O(V^2*E), unitario O(E*sqrt(V)) ----------
int lv[N], it[N];
bool bfs(int s,int t,int n){
    fill(lv,lv+n+1,-1); queue<int> q; q.push(s); lv[s]=0;
    while(sz(q)){
        int u=q.front(); q.pop();
        for(int id:g[u]) if(cp[id]>0 && lv[to[id]]<0) lv[to[id]]=lv[u]+1, q.push(to[id]);
    }
    return lv[t]>=0;
}
ll ddfs(int u,int t,ll f){
    if(u==t) return f;
    for(int &i=it[u];i<sz(g[u]);i++){
        int id=g[u][i];
        if(cp[id]>0 && lv[to[id]]==lv[u]+1){
            ll r=ddfs(to[id],t,min(f,cp[id]));
            if(r){ cp[id]-=r; cp[id^1]+=r; return r; }
        }
    }
    return 0;
}
ll dinic(int s,int t,int n){
    ll fl=0,x;
    while(bfs(s,t,n)){ fill(it,it+n+1,0); while(x=ddfs(s,t,INF)) fl+=x; }
    return fl;
}

vector<pii> mincut(int s,int n){ // llamar DESPUÉS del flujo; devuelve las aristas (a,b) del corte
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
