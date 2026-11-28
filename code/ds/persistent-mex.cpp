#undef int // Все числа < $2^31$
struct node {
    int L = 0, R = 0, mn = -1;
};

vector <node> t;
vector <int> roots;
// Новая версия: $p_x = i$
int upd(int v, int l, int r, int x, int i) {
    t.pb(t[v]);
    v = t.size() - 1;
    if (l == r) {
        t[v].mn = i;
        return v;
    }
    int md = (l + r) / 2;
    if (x <= md)
        t[v].L = upd(t[v].L, l, md, x, i);
    else
        t[v].R = upd(t[v].R, md + 1, r, x, i);
    t[v].mn = min(t[t[v].L].mn, t[t[v].R].mn);
    return v;
}
// Мин. x с $p_x < i$ в версии v
int mex(int v, int l, int r, int i) {
    if (l == r)
        return l;
    int md = (l + r) / 2;
    if (t[t[v].L].mn < i)
        return mex(t[v].L, l, md, i);
    else
        return mex(t[v].R, md + 1, r, i);
}
