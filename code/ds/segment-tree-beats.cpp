struct STB {
    long sum,
         mx, sx, mn, sn, lz;
    int cx, cn; // Количество максимумов и минимумов
} t[4 * N];

void merge(int v) {
    int L = v << 1, R = L + 1;
    t[v].sum = t[L].sum + t[R].sum;
    if (t[L].mx == t[R].mx) {
        t[v].mx = t[L].mx;
        t[v].cx = t[L].cx + t[R].cx;
        t[v].sx = max(t[L].sx, t[R].sx);
    }
    elif (t[L].mx > t[R].mx) {
        t[v].mx = t[L].mx;
        t[v].cx = t[L].cx;
        t[v].sx = max(t[L].sx, t[R].mx);
    }
    else {
        t[v].mx = t[R].mx;
        t[v].cx = t[R].cx;
        t[v].sx = max(t[L].mx, t[R].sx);
    }
    if (t[L].mn == t[R].mn) {
        t[v].mn = t[L].mn;
        t[v].cn = t[L].cn + t[R].cn;
        t[v].sn = min(t[L].sn, t[R].sn);
    }
    elif (t[L].mn < t[R].mn) {
        t[v].mn = t[L].mn;
        t[v].cn = t[L].cn;
        t[v].sn = min(t[L].sn, t[R].mn);
    }
    else {
        t[v].mn = t[R].mn;
        t[v].cn = t[R].cn;
        t[v].sn = min(t[L].mn, t[R].sn);
    }
}
void chAdd(int v, long x, int len) {
    if (x == 0)
        return;
    t[v].sum += x * len;
    t[v].mx += x;
    t[v].mn += x;
    t[v].lz += x;
    if (t[v].sx != -oo)
        t[v].sx += x;
    if (t[v].sn != oo)
        t[v].sn += x;
}
void chMin(int v, long x, int len) { // Min=
    if (t[v].mx <= x)
        return;
    t[v].sum -= (t[v].mx - x) * t[v].cx;
    t[v].mx = x;
    if (t[v].mn > x)
        t[v].mn = x;
    if (t[v].sn > x)
        t[v].sn = x;
    if (t[v].mn == t[v].mx) {
        t[v].sx = -oo;
        t[v].sn = oo;
        t[v].cx = t[v].cn = len;
    }
}
void chMax(int v, long x, int len) { // Max=
    if (t[v].mn >= x)
        return;
    t[v].sum += (x - t[v].mn) * t[v].cn;
    t[v].mn = x;
    if (t[v].mx < x)
        t[v].mx = x;
    if (t[v].sx < x)
        t[v].sx = x;
    if (t[v].mn == t[v].mx) {
        t[v].sx = -oo;
        t[v].sn = oo;
        t[v].cx = t[v].cn = len;
    }
}
void push(int v, int l, int r) {
    int L = v << 1, R = L + 1, m = (l + r) >> 1;
    chAdd(L, t[v].lz, m - l + 1);
    chAdd(R, t[v].lz, r - m);
    t[v].lz = 0;
    chMin(L, t[v].mx, m - l + 1); chMax(L, t[v].mn, m - l + 1);
    chMin(R, t[v].mx, r - m); chMax(R, t[v].mn, r - m);
}
void build(int v, int l, int r) {
    t[v].lz = 0;
    if (l == r) {
        t[v].sum = t[v].mx = t[v].mn = a[l];
        t[v].sx = -oo;
        t[v].sn = oo;
        t[v].cx = t[v].cn = 1;
        return;
    }
    int m = (l + r) >> 1;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    merge(v);
}
void updMin(int v, int l, int r, int ql, int qr, long x) { // Min=
    if (l > qr || r < ql || t[v].mx <= x)
        return;
    if (l >= ql && r <= qr && t[v].sx < x) {
        chMin(v, x, r - l + 1);
        return;
    }
    push(v, l, r);
    int m = (l + r) >> 1;
    updMin(2 * v, l, m, ql, qr, x);
    updMin(2 * v + 1, m + 1, r, ql, qr, x);
    merge(v);
}
void updMax(int v, int l, int r, int ql, int qr, long x) { // Max=
    if (l > qr || r < ql || t[v].mn >= x)
        return;
    if (l >= ql && r <= qr && t[v].sn > x) {
        chMax(v, x, r - l + 1);
        return;
    }
    push(v, l, r);
    int m = (l + r) >> 1;
    updMax(2 * v, l, m, ql, qr, x);
    updMax(2 * v + 1, m + 1, r, ql, qr, x);
    merge(v);
}
void updAdd(int v, int l, int r, int ql, int qr, long x) {
    if (l > qr || r < ql)
        return;
    if (l >= ql && r <= qr) {
        chAdd(v, x, r - l + 1);
        return;
    }
    push(v, l, r);
    int m = (l + r) >> 1;
    updAdd(2 * v, l, m, ql, qr, x);
    updAdd(2 * v + 1, m + 1, r, ql, qr, x);
    merge(v);
}
long get(int v, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
        return 0;
    if (l >= ql && r <= qr)
        return t[v].sum;
    push(v, l, r);
    int m = (l + r) >> 1;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m + 1, r, ql, qr);
}
// Main
build(1, 0, n - 1);
updAdd/updMax/updMin (1, 0, n - 1, l, r, x);
get(1, 0, n - 1, l, r);
