const int INF = 4e18;

struct line {
    int k = 0, b = -INF; // b = -INF - прямой нет
    int operator() (int x) {
        return k * x + b;
    }
};

struct node {
    int L = 0, R = 0;
    line ln, up = {0, 0}; // up - прибавить ко всем прямым ниже
};

vector <node> t; // t.pb({}), t.pb({}) - вершина 0 пустая, 1 - корень

int mk(int v) {
    if (v)
        return v;
    t.pb({});
    return t.size() - 1;
}

void app(int v, line a) {
    if (!v)
        return;
    if (t[v].ln.b != -INF)
        t[v].ln.k += a.k, t[v].ln.b += a.b;
    t[v].up.k += a.k, t[v].up.b += a.b;
}

void push(int v) {
    app(t[v].L, t[v].up);
    app(t[v].R, t[v].up);
    t[v].up = {0, 0};
}
// max= nw на всём [l, r]
int ins(int v, int l, int r, line nw) {
    v = mk(v);
    int md = l + (r - l) / 2;
    if (t[v].ln(md) < nw(md))
        swap(t[v].ln, nw);
    if (l == r || nw.b == -INF)
        return v;
    push(v);
    if (t[v].ln(l) < nw(l))
        t[v].L = ins(t[v].L, l, md, nw);
    else if (t[v].ln(r) < nw(r))
        t[v].R = ins(t[v].R, md + 1, r, nw);
    return v;
}
// max= nw на [_l, _r]
int upd(int v, int l, int r, int _l, int _r, line nw) {
    if (_l <= l && r <= _r)
        return ins(v, l, r, nw);
    v = mk(v);
    push(v);
    int md = l + (r - l) / 2;
    if (_l <= md)
        t[v].L = upd(t[v].L, l, md, _l, _r, nw);
    if (md + 1 <= _r)
        t[v].R = upd(t[v].R, md + 1, r, _l, _r, nw);
    return v;
}
// += a на [_l, _r]
void add(int v, int l, int r, int _l, int _r, line a) {
    if (!v)
        return;
    if (_l <= l && r <= _r) {
        app(v, a);
        return;
    }
    push(v);
    int md = l + (r - l) / 2;
    line ln = t[v].ln;
    t[v].ln = {};
    if (ln.b != -INF) { // Изменится только на части [l, r]
        t[v].L = ins(t[v].L, l, md, ln);
        t[v].R = ins(t[v].R, md + 1, r, ln);
    }
    if (_l <= md)
        add(t[v].L, l, md, _l, _r, a);
    if (md + 1 <= _r)
        add(t[v].R, md + 1, r, _l, _r, a);
}

int get(int v, int l, int r, int x) {
    if (!v)
        return -INF;
    int md = l + (r - l) / 2;
    int res;
    if (x <= md)
        res = get(t[v].L, l, md, x);
    else
        res = get(t[v].R, md + 1, r, x);
    if (res != -INF)
        res += t[v].up(x);
    return max(res, t[v].ln(x));
}
// Main
upd(1, lo, hi, l, r, {k, b});
add(1, lo, hi, l, r, {k, b});
get(1, lo, hi, x);
