const int N = 2e5 + 9;
int deg[N];

// Дерево на вершинах 0..n - 1 (n >= 2) -> код длины n - 2, O(n)
vector <int> prufer(int n, vector <int> *g) {
    for (int v = 0; v < n; ++v)
        deg[v] = g[v].size();
    vector <int> code;
    // ptr - все листья с номером < ptr уже удалены, leaf - мин. лист
    for (int i = 0, ptr = 0, leaf = -1; i < n - 2; ++i) {
        if (leaf == -1) {
            while (deg[ptr] != 1)
                ++ptr;
            leaf = ptr++;
        }
        int v = -1; // Единственный оставшийся сосед листа
        for (int u : g[leaf])
            if (deg[u])
                v = u;
        code.pb(v);
        deg[leaf] = 0;
        leaf = --deg[v] == 1 && v < ptr ? v : -1; // v стал листом меньше ptr - он и есть мин.
    }
    return code;
}
// Код длины n - 2 -> рёбра дерева, O(n)
vector <pair <int, int>> unprufer(vector <int> &code) {
    int n = code.size() + 2;
    fill(deg, deg + n, 1); // Степень = кол-во вхождений в код + 1
    for (int v : code)
        ++deg[v];
    vector <pair <int, int>> e;
    int ptr = 0, leaf = -1;
    for (int v : code) {
        if (leaf == -1) {
            while (deg[ptr] != 1)
                ++ptr;
            leaf = ptr++;
        }
        e.pb({leaf, v});
        deg[leaf] = 0;
        leaf = --deg[v] == 1 && v < ptr ? v : -1;
    }
    while (leaf == -1 || deg[leaf] != 1) // Осталось ребро между двумя вершинами степени 1
        leaf = ptr++;
    deg[leaf] = 0;
    while (deg[ptr] != 1)
        ++ptr;
    e.pb({leaf, ptr});
    return e;
}
