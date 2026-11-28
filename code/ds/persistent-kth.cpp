struct node {
    int L = 0, R = 0, sm = 0;
};

vector <node> t;
vector <int> roots;
// Новая версия: v с +1 в точке p
int add(int v, int l, int r, int p) {
    t.pb(t[v]);
    v = t.size() - 1;
    ++t[v].sm;
    if (l == r)
        return v;
    int md = (l + r) / 2;
    if (p <= md)
        t[v].L = add(t[v].L, l, md, p);
    else
        t[v].R = add(t[v].R, md + 1, r, p);
    return v;
}
// k-е с 0 значение в мультимножестве a + b - c - d: спуск по 4 версиям
int kth(int a, int b, int c, int d, int l, int r, int k) {
    if (l == r)
        return l;
    int md = (l + r) / 2;
    int s = t[t[a].L].sm + t[t[b].L].sm - t[t[c].L].sm - t[t[d].L].sm;
    if (k < s)
        return kth(t[a].L, t[b].L, t[c].L, t[d].L, l, md, k);
    else
        return kth(t[a].R, t[b].R, t[c].R, t[d].R, md + 1, r, k - s);
}
