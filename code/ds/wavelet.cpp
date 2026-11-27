int h, mid[20];
vector <int> b[20]; // b[i][j] - единиц среди первых j на уровне i

void build(vector <int> a, int sigma) { // значения в [0, sigma)
    h = __lg(max(sigma - 1, int(1))) + 1;
    for (int i = 0; i < h; ++i) {
        int bit = h - 1 - i;
        b[i].assign(a.size() + 1, 0);
        for (int j = 0; j < a.size(); ++j)
            b[i][j + 1] = b[i][j] + (a[j] >> bit & 1);
        mid[i] = a.size() - b[i][a.size()];
        stable_partition(a.begin(), a.end(), [&](int x) { return !(x >> bit & 1); });
    }
}
int kth(int l, int r, int k) {
    int ans = 0;
    for (int i = 0; i < h; ++i) {
        int L = b[i][l], R = b[i][r];
        int zeros = r - l - R + L;
        if (k < zeros) {
            l -= L;
            r -= R;
        }
        else {
            k -= zeros;
            ans |= 1 << (h - 1 - i);
            l = mid[i] + L;
            r = mid[i] + R;
        }
    }
    return ans;
}
int cnt(int l, int r, int x) {
    if (x >> h)
        return r - l;
    int ans = 0;
    for (int i = 0; i < h; ++i) {
        int L = b[i][l], R = b[i][r];
        int zeros = r - l - R + L;
        if (x >> (h - 1 - i) & 1) {
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
