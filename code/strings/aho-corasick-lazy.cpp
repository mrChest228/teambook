int to[N][K], go[N][K], suf[N], par[N], pc[N], sz = 1;

void init() {
    fill(&go[0][0], &go[0][0] + N * K, -1);
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
int getGo(int v, int c);
int getSuf(int v) {
    if (suf[v] == -1)
        suf[v] = par[v] ? getGo(getSuf(par[v]), pc[v]) : 0;
    return suf[v];
}
int getGo(int v, int c) {
    if (go[v][c] == -1)
        go[v][c] = to[v][c] ? to[v][c] : (v ? getGo(getSuf(v), c) : 0);
    return go[v][c];
}
