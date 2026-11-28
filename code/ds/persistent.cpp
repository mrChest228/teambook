struct node {
    int L = 0, R = 0, up = 0;
};

vector <node> t;
vector <int> roots;
// Пустое дерево на [l, r]: roots.pb(mk(0, m - 1))
int mk(int l, int r) {
    int v = t.size();
    t.pb({});
    if (l == r)
        return v;
    int md = (l + r) / 2;
    t[v].L = mk(l, md);
    t[v].R = mk(md + 1, r);
    return v;
}
// Новая версия: v с +x на [_l, _r]
int upd(int v, int l, int r, int _l, int _r, int x) {
    t.pb(t[v]);
    v = t.size() - 1;
    if (_l <= l && r <= _r) {
        t[v].up += x;
        return v;
    }
    int md = (l + r) / 2;
    if (_l <= md)
        t[v].L = upd(t[v].L, l, md, _l, _r, x);
    if (md + 1 <= _r)
        t[v].R = upd(t[v].R, md + 1, r, _l, _r, x);
    return v;
}
// Значение в точке p версии v
int get(int v, int l, int r, int p) {
    if (l == r)
        return t[v].up;
    int md = (l + r) / 2;
    if (p <= md)
        return get(t[v].L, l, md, p) + t[v].up;
    else
        return get(t[v].R, md + 1, r, p) + t[v].up;
}
