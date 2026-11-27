vector <int> colorBip(int n, vector <pair <int, int>> &e) {
    int m = e.size(), D = 0;
    vector <int> deg(n);
    for (auto [x, y] : e) {
        ++deg[x];
        ++deg[y];
        if (deg[x] > D) D = deg[x];
        if (deg[y] > D) D = deg[y];
    }

    vector <int> ans(m, -1);
    if (!m)
        return ans;

    vector <vector <int>> to(n, vector <int>(D, -1));
    vector <vector <int>> edgeId(n, vector <int>(D, -1));
    for (int id = 0; id < m; ++id) {
        int x = e[id].first, y = e[id].second;
        int a = 0, b = 0;
        while (to[x][a] != -1) ++a;
        while (to[y][b] != -1) ++b;

        if (a != b) {
            vector <int> path;
            int v = y, c = a;
            while (to[v][c] != -1) {
                path.pb(edgeId[v][c]);
                v = to[v][c];
                c = c == a ? b : a;
            }

            for (int i : path) {
                int old = ans[i];
                int x0 = e[i].first, y0 = e[i].second;
                to[x0][old] = to[y0][old] = -1;
                edgeId[x0][old] = edgeId[y0][old] = -1;
            }
            for (int i : path) {
                int old = ans[i], c0 = old == a ? b : a;
                int x0 = e[i].first, y0 = e[i].second;
                ans[i] = c0;
                to[x0][c0] = y0;
                to[y0][c0] = x0;
                edgeId[x0][c0] = edgeId[y0][c0] = i;
            }
        }

        ans[id] = a;
        to[x][a] = y;
        to[y][a] = x;
        edgeId[x][a] = edgeId[y][a] = id;
    }
    return ans;
}
