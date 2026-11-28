const int N = 2e5 + 9, K = 450; // K ~ n / sqrt(q)
int ql[N], qr[N], ord[N], ans[N]; // Запросы - отрезки [ql[i], qr[i]]

void add(int i); // Добавить в ответ элемент i
void del(int i); // Убрать
int get();       // Текущий ответ

// O(n * sqrt(q) + q) вызовов add и del
void mo(int q) {
    iota(ord, ord + q, 0);
    sort(ord, ord + q, [](int a, int b) {
        if (ql[a] / K != ql[b] / K)
            return ql[a] < ql[b];
        return ql[a] / K % 2 ? qr[a] > qr[b] : qr[a] < qr[b]; // Через блок r идёт обратно
    });
    int l = 0, r = -1;
    for (int j = 0; j < q; ++j) {
        int i = ord[j];
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
