struct node {
    int L = 0, R = 0, mn = 1e9;
};

const int N = 1e5 + 9;
int n, a[N], rt[N]; // Позиции 1..n, $"rt"_i$ - ДО вершины i Фенвика
set <int> ps[N];    // Позиции значения x, а также 0 и n + 1
vector <node> t;    // t.pb({}) - вершина 0, пустое дерево

int upd(int v, int l, int r, int x, int val) {
    if (!v) {
        v = t.size();
        t.pb({});
    }
    if (l == r) {
        t[v].mn = val;
        return v;
    }
    int md = (l + r) / 2;
    if (x <= md)
        t[v].L = upd(t[v].L, l, md, x, val);
    else
        t[v].R = upd(t[v].R, md + 1, r, x, val);
    t[v].mn = min(t[t[v].L].mn, t[t[v].R].mn);
    return v;
}
// Вершины Фенвика, покрывающие j: пересчитать в них значение x
void fix(int x, int j) {
    for (int i = j; i > 0; i -= i & -i) {
        auto it = ps[x].lower_bound(i); // Первый пропуск с R + 1 >= i
        int L = *it < i + (i & -i) ? *prev(it) + 1 : 1e9;
        rt[i] = upd(rt[i], 0, n, x, L);
    }
}
// Добавить (d = 1) или убрать (d = 0) значение x в позиции p
void change(int p, int x, bool d) {
    if (x > n)
        return;
    if (d)
        ps[x].in(p);
    else
        ps[x].erase(p);
    fix(x, p);
    fix(x, *ps[x].upper_bound(p));
}

void build() {
    t.pb({});
    for (int x = 0; x <= n; ++x) {
        ps[x] = {0, n + 1};
        fix(x, n + 1);
    }
    for (int p = 1; p <= n; ++p)
        change(p, a[p], 1);
}

void assign(int p, int x) {
    change(p, a[p], 0);
    change(p, a[p] = x, 1);
}

int mex(int l, int r) {
    vector <int> c;
    for (int i = r + 1; i <= n + 1; i += i & -i)
        c.pb(rt[i]);
    int lo = 0, hi = n;
    while (lo < hi) {
        int md = (lo + hi) / 2;
        bool lf = 0;
        for (int v : c)
            lf |= t[t[v].L].mn <= l;
        for (int &v : c)
            v = lf ? t[v].L : t[v].R;
        if (lf)
            hi = md;
        else
            lo = md + 1;
    }
    return lo;
}
