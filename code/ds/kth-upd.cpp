struct node {
    int L = 0, R = 0, sm = 0;
};

const int N = 1e5 + 9;
int n, m, rt[N]; // Позиции 1..n, значения [0, m), $"rt"_i$ - ДО вершины i Фенвика
vector <node> t; // t.pb({}) - вершина 0, пустое дерево

int add(int v, int l, int r, int p, int x) {
    if (!v) {
        v = t.size();
        t.pb({});
    }
    t[v].sm += x;
    if (l == r)
        return v;
    int md = (l + r) / 2;
    if (p <= md)
        t[v].L = add(t[v].L, l, md, p, x);
    else
        t[v].R = add(t[v].R, md + 1, r, p, x);
    return v;
}
// Кол-во значений p в позиции i меняется на x
void change(int i, int p, int x) {
    for (; i <= n; i += i & -i)
        rt[i] = add(rt[i], 0, m - 1, p, x);
}
// k-е с 0 значение на [l, r]
int kth(int l, int r, int k) {
    vector <int> a, b;
    for (; r > 0; r -= r & -r)
        a.pb(rt[r]);
    for (--l; l > 0; l -= l & -l)
        b.pb(rt[l]);
    int lo = 0, hi = m - 1;
    while (lo < hi) {
        int md = (lo + hi) / 2, s = 0;
        for (int v : a)
            s += t[t[v].L].sm;
        for (int v : b)
            s -= t[t[v].L].sm;
        bool lf = k < s;
        for (int &v : a)
            v = lf ? t[v].L : t[v].R;
        for (int &v : b)
            v = lf ? t[v].L : t[v].R;
        if (lf)
            hi = md;
        else
            lo = md + 1, k -= s;
    }
    return lo;
}
