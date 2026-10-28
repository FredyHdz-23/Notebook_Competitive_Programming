#include <template.h>
(DFS) O(E*F)

const int N=1e5+5, M=4e5+5; const ll INF=1e18;
vi g[N]; int to[M], ec; ll cp[M];
void add(int a,int b,ll c,ll r=0){ // r=c si es no dirigida
    g[a].pb(ec); to[ec]=b; cp[ec++]=c;
    g[b].pb(ec); to[ec]=a; cp[ec++]=r;
}

int vis[N], T;
ll fdfs(int u,int t,ll f){
    if(u==t) return f;
    vis[u]=T;
    for(int id:g[u]) if(cp[id]>0 && vis[to[id]]!=T){
        ll r=fdfs(to[id],t,min(f,cp[id]));
        if(r){ cp[id]-=r; cp[id^1]+=r; return r; }
    }
    return 0;
}
ll ff(int s,int t){ ll fl=0,x; while(T++, x=fdfs(s,t,INF)) fl+=x; return fl; }
