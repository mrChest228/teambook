const int MX = 2e5 + 9, H = __lg(MX - 1) + 1;
int mid[H]; // mid[i] - нулей на уровне i
vector <int> b[H]; // b[i][j] - единиц среди первых j на уровне i

void build(vector <int> a) {
    for (int i = 0; i < H; ++i) {
        int bit = H - 1 - i;
        b[i].assign(a.size() + 1, 0);
        for (int j = 0; j < a.size(); ++j)
            b[i][j + 1] = b[i][j] + (a[j] >> bit & 1);
        mid[i] = a.size() - b[i][a.size()];
        // stable_partition: нули влево, единицы вправо, порядок внутри сохраняется
        stable_partition(a.begin(), a.end(), [&](int x) { return !(x >> bit & 1); });
    }
}
int kth(int l, int r, int k) { // k-е по возрастанию на [l, r), с 0
    int ans = 0;
    for (int i = 0; i < H; ++i) {
        int L = b[i][l], R = b[i][r]; // единиц до l и до r
        int zeros = r - l - R + L;
        if (k < zeros) { // ответ среди нулей: [l - L, r - R)
            l -= L;
            r -= R;
        }
        else {
            k -= zeros;
            ans |= 1 << (H - 1 - i);
            l = mid[i] + L;
            r = mid[i] + R;
        }
    }
    return ans;
}
int cnt(int l, int r, int x) { // кол-во < x на [l, r), x >= 0
    if (x >> H)
        return r - l;
    int ans = 0;
    for (int i = 0; i < H; ++i) {
        int L = b[i][l], R = b[i][r];
        int zeros = r - l - R + L;
        if (x >> (H - 1 - i) & 1) { // все нули меньше x
            ans += zeros;
            l = mid[i] + L;
            r = mid[i] + R;
        }
        else {
            l -= L;
            r -= R;
        }
    }
    return ans;
}
