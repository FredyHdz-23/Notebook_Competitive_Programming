// Segment Tree - min/suma de rango con update puntual
// O(log n) query/update, O(n) build

#include <template.h>

struct segTree{
    vector<ll> v; int n; ll nulo = 0;
    ll op(ll a, ll b) {return a+b;}
    segTree (int n) : n(n) {v.assign(2*n,nulo);}
    void upd(int i, ll nv){
        for (v[i+=n]=nv; i>1; i>>=1) v[i>>1] = op(v[i],v[i^1]);
    }
    ll get(int l, int r){
        ll vl = nulo, vr = nulo;
        for (l+=n, r+=n+1; l<r; l>>=1, r>>=1){
            if (l&1) vl = op(vl,v[l++]);
            if (r&1) vr = op(v[--r], vr);
        }
        return op(vl,vr);
    }
};
