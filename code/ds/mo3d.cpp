const int N = 1e5 + 9, K = 4500; // $K approx 2 n^(2 \/ 3)$
int a[N], pos[N], val[N]; // Изменение j: $a_("pos"_j) = "val"_j$
int ql[N], qr[N], qt[N], ord[N], ans[N]; // $"qt"_i$ - число изменений до запроса i

void add(int i); // Добавить в ответ элемент i
void del(int i); // Убрать
int get();       // Текущий ответ

// Применить или откатить изменение j при текущем отрезке [l, r]
void change(int j, int l, int r) {
    int p = pos[j];
    if (l <= p && p <= r)
        del(p);
    swap(a[p], val[j]);
    if (l <= p && p <= r)
        add(p);
}

void mo(int q) {
    iota(ord, ord + q, 0);
    sort(ord, ord + q, [](int x, int y) {
        if (ql[x] / K != ql[y] / K)
            return ql[x] < ql[y];
        if (qr[x] / K != qr[y] / K)
            return qr[x] < qr[y];
        return qt[x] < qt[y];
    });
    int l = 0, r = -1, t = 0;
    for (int j = 0; j < q; ++j) {
        int i = ord[j];
        while (t < qt[i])
            change(t++, l, r);
        while (t > qt[i])
            change(--t, l, r);
        while (l > ql[i])
            add(--l);
        while (r < qr[i])
            add(++r);
        while (l < ql[i])
            del(l++);
        while (r > qr[i])
            del(r--);
        ans[i] = get();
    }
}
