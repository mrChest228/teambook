vector <int> color(int n, vector <pair <int, int>> &e) {
    int m = e.size(), D = 0;
    vector <int> deg(n), ret(m), fan(n), fanColor(n), freeColor(n), loc;
    for (auto [x, y] : e) {
        ++deg[x];
        ++deg[y];
        if (deg[x] > D) D = deg[x];
        if (deg[y] > D) D = deg[y];
    }
    if (!m)
        return ret;

    int C = D + 1;
    vector <vector <int>> to(n, vector <int>(C, -1));
    for (auto [x, y] : e) {
        int u = x, v = y;
        fan[0] = v;
        loc.assign(C, 0);
        int at = u, end = u, d, c = freeColor[u], ind = 0, i = 0;

        while (true) {
            d = freeColor[v];
            if (loc[d] || to[u][d] == -1)
                break;
            v = to[u][d];
            loc[d] = ++ind;
            fanColor[ind] = d;
            fan[ind] = v;
        }
        fanColor[loc[d]] = c;

        // Переключаем цвета на чередующейся цепи.
        for (int cd = d; at != -1; cd = cd ^ c ^ d) {
            int next = to[at][cd], otherColor = cd ^ c ^ d;
            int other = to[at][otherColor];
            to[at][cd] = other;
            to[at][otherColor] = next;
            end = at;
            at = next;
        }

        // Сдвигаем раскраску вдоль веера до свободного цвета d.
        while (to[fan[i]][d] != -1) {
            int left = fan[i], right = fan[i + 1], c0 = fanColor[i + 1];
            ++i;
            to[u][c0] = left;
            to[left][c0] = u;
            to[right][c0] = -1;
            freeColor[right] = c0;
        }
        to[u][d] = fan[i];
        to[fan[i]][d] = u;

        for (int y : {fan[0], u, end}) {
            freeColor[y] = 0;
            while (to[y][freeColor[y]] != -1)
                ++freeColor[y];
        }
    }

    for (int id = 0; id < m; ++id) {
        int x = e[id].first, y = e[id].second;
        while (to[x][ret[id]] != y)
            ++ret[id];
    }
    return ret;
}
