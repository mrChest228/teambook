int to[N][K], g[N][K], suf[N], par[N], pc[N], cnt[N], sz = 1;

void init() {
    fill(&g[0][0], &g[0][0] + N * K, -1);
    fill(suf, suf + N, -1);
}
int add(string &s) {
    int v = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!to[v][x]) {
            to[v][x] = sz++;
            par[to[v][x]] = v;
            pc[to[v][x]] = x;
        }
        v = to[v][x];
    }
    return v;
}
int go(int v, int c);
int sf(int v) {
    if (suf[v] == -1)
        suf[v] = par[v] ? go(sf(par[v]), pc[v]) : 0;
    return suf[v];
}
int go(int v, int c) {
    if (g[v][c] == -1)
        g[v][c] = to[v][c] ? to[v][c] : (v ? go(sf(v), c) : 0);
    return g[v][c];
}
vector <int> occ(vector <string> &s, string &t) {
    vector <int> end, res;
    for (string &x : s)
        end.pb(add(x));
    vector <int> q = {0};
    for (int i = 0; i < q.size(); ++i)
        for (int c = 0; c < K; ++c)
            if (to[q[i]][c])
                q.pb(to[q[i]][c]);
    int v = 0;
    for (char c : t) {
        v = go(v, c - 'a');
        ++cnt[v];
    }
    for (int i = q.size() - 1; i > 0; --i)
        cnt[sf(q[i])] += cnt[q[i]];
    for (int v : end)
        res.pb(cnt[v]);
    return res;
}
