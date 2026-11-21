#include <template.h>

const int N=1<<17; int n;

struct Lazy{
    ll t[4*N], d[4*N];
    void ap(int x,int l,int r,ll v){t[x]+=v*(r-l+1); d[x]+=v;}
    void push(int x,int l,int r){
        if(d[x]){int m=l+r>>1; ap(2*x,l,m,d[x]); ap(2*x+1,m+1,r,d[x]); d[x]=0;}
    }
    void build(vector<ll>&a,int x=1,int l=0,int r=n-1){
        if(l==r){t[x]=a[l];return;}
        int m=l+r>>1; build(a,2*x,l,m); build(a,2*x+1,m+1,r);
        t[x]=t[2*x]+t[2*x+1];
    }
    void upd(int a,int b,ll v,int x=1,int l=0,int r=n-1){
        if(b<l||r<a) return;
        if(a<=l&&r<=b){ap(x,l,r,v);return;}
        push(x,l,r); int m=l+r>>1;
        upd(a,b,v,2*x,l,m); upd(a,b,v,2*x+1,m+1,r);
        t[x]=t[2*x]+t[2*x+1];
    }
    ll get(int a,int b,int x=1,int l=0,int r=n-1){
        if(b<l||r<a) return 0;
        if(a<=l&&r<=b) return t[x];
        push(x,l,r); int m=l+r>>1;
        return get(a,b,2*x,l,m)+get(a,b,2*x+1,m+1,r);
    }
};