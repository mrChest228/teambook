struct node {
    int u, v, y, sz = 1, par = -1, L = -1, R = -1;
};

const int M = 2e6; // n + 2 * m

int fre[M], freSz;
node nodes[M];

void initPool() {
    static bool inited = false;
    if (inited)
        return;
    for (int i = 0; i < M; ++i)
        fre[M - 1 - i] = i;
    freSz = M;
    inited = true;
}

int nw(int u, int v) {
    assert(freSz);
    int nd = fre[--freSz];
    nodes[nd].y = rnd();
    nodes[nd].u = u;
    nodes[nd].v = v;
    return nd;
}

void del(int v) {
    assert(v != -1);
    nodes[v].sz = 1;
    nodes[v].par = -1;
    nodes[v].L = -1;
    nodes[v].R = -1;
    fre[freSz++] = v;
}

int sz(int v) {
    return (v == -1 ? 0 : nodes[v].sz);
}

pair <int, int> getRoot(int v) {
    int pos = sz(nodes[v].L);
    while (nodes[v].par != -1) {
        if (nodes[nodes[v].par].R == v)
            pos += sz(nodes[nodes[v].par].L) + 1;
        v = nodes[v].par;
    }
    return {v, pos};
}

void calc(int v) {
    nodes[v].sz = 1 + sz(nodes[v].L) + sz(nodes[v].R);
    nodes[v].par = -1;
    if (nodes[v].L != -1) nodes[nodes[v].L].par = v;
    if (nodes[v].R != -1) nodes[nodes[v].R].par = v;
}

int merge(int l, int r) {
    if (l == -1) return r;
    if (r == -1) return l;
    if (nodes[l].y > nodes[r].y) {
        nodes[l].R = merge(nodes[l].R, r);
        calc(l);
        return l;
    }
    else {
        nodes[r].L = merge(l, nodes[r].L);
        calc(r);
        return r;
    }
}

pair <int, int> split(int v, int k) {
    if (v == -1) return {-1, -1};
    if (sz(nodes[v].L) >= k) {
        pair p = split(nodes[v].L, k);
        nodes[v].L = p.s;
        calc(v);
        return {p.f, v};
    }
    else {
        pair p = split(nodes[v].R, k - sz(nodes[v].L) - 1);
        nodes[v].R = p.f;
        calc(v);
        return {v, p.s};
    }
}

int mkFirst(int v) {
    auto [root, pos] = getRoot(v);
    auto [a, b] = split(root, pos);
    return merge(b, a);
}

struct treap {
    int n, *nd;
    unordered_map <long, int> mp;

    treap(int n): n(n) {
        initPool();
        nd = new int[n];
        for (int i = 0; i < n; ++i)
            nd[i] = nw(i, i);
    }

    ~treap() {
        for (int i = 0; i < n; ++i)
            del(nd[i]);
        for (auto u : mp)
            del(u.s);
        delete[] nd;
    }

    bool connected(int x, int y) {
        return getRoot(nd[x]).f == getRoot(nd[y]).f;
    }

    int size(int x) {
        return (sz(getRoot(nd[x]).f) + 2) / 3; // n + (n - 1) * 2
    }

    void link(int x, int y) {
        assert(getRoot(nd[x]).f != getRoot(nd[y]).f);
        int rootX = mkFirst(nd[x]),
            rootY = mkFirst(nd[y]),
            xy = nw(x, y),
            yx = nw(y, x);
        mp[long(x) << 32 | y] = xy;
        mp[long(y) << 32 | x] = yx;
        merge(merge(merge(rootX, xy), rootY), yx);
    }

    void cut(int x, int y) {
        assert(getRoot(nd[x]).f == getRoot(nd[y]).f);
        int root = mkFirst(nd[x]),
            xy = mp[long(x) << 32 | y],
            yx = mp[long(y) << 32 | x];
        auto [ab, c] = split(root, getRoot(yx).s + 1);
        auto [a, b] = split(ab, getRoot(xy).s);
        b = split(b, 1).s;
        b = split(b, sz(b) - 1).f;
        merge(a, c);
        del(xy);
        del(yx);
        mp.erase(long(x) << 32 | y);
        mp.erase(long(y) << 32 | x);
    }
};

// treap tr(n); tr.link(x, y); tr.cut(x, y); tr.connected(x, y); tr.size(x) — O(log n) per operation.
