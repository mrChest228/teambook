int match[N], p[N], base[N];
bool used[N], blossom[N];
vector <int> g[N];

int lca(int a, int b, int n) {
    vector <int> seen(n);
    while (true) {
        a = base[a];
        seen[a] = 1;
        if (match[a] == -1)
            break;
        a = p[match[a]];
    }
    while (true) {
        b = base[b];
        if (seen[b])
            return b;
        b = p[match[b]];
    }
}
void markPath(int v, int b, int child) {
    while (base[v] != b) {
        blossom[base[v]] = true;
        blossom[base[match[v]]] = true;
        p[v] = child;
        child = match[v];
        v = p[match[v]];
    }
}
int findPath(int root, int n) {
    fill(used, used + n, 0);
    fill(p, p + n, -1);
    iota(base, base + n, 0);
    queue <int> q;
    q.push(root);
    used[root] = true;
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
            if (base[v] == base[u] || match[v] == u)
                continue;
            if (u == root || (match[u] != -1 && p[match[u]] != -1)) {
                int cur = lca(v, u, n);
                fill(blossom, blossom + n, 0);
                markPath(v, cur, u);
                markPath(u, cur, v);
                for (int i = 0; i < n; ++i)
                    if (blossom[base[i]]) {
                        base[i] = cur;
                        if (!used[i]) {
                            used[i] = true;
                            q.push(i);
                        }
                    }
            }
            else if (p[u] == -1) {
                p[u] = v;
                if (match[u] == -1)
                    return u;
                u = match[u];
                used[u] = true;
                q.push(u);
            }
        }
    }
    return -1;
}
int edmonds(int n) {
    fill(match, match + n, -1);
    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (match[i] == -1) {
            int v = findPath(i, n);
            if (v == -1)
                continue;
            ++ans;
            while (v != -1) {
                int pv = p[v];
                int next = pv == -1 ? -1 : match[pv];
                if (pv != -1) {
                    match[v] = pv;
                    match[pv] = v;
                }
                v = next;
            }
        }
    return ans;
}
