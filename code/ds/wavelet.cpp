vector <vector <int>> pref;
vector <int> mid;
int sigma, h;

void build(vector <int> &a, int s) {
    sigma = s;
    h = 0;
    while ((1L << h) < sigma)
        ++h;
    pref.assign(h, vector <int>(a.size() + 1));
    mid.resize(h);
    vector <int> cur = a, nxt(a.size());
    for (int level = 0; level < h; ++level) {
        int bit = h - level - 1;
        for (int i = 0; i < a.size(); ++i)
            pref[level][i + 1] = pref[level][i] + (cur[i] >> bit & 1);
        mid[level] = a.size() - pref[level][a.size()];
        int zero = 0, one = mid[level];
        for (int x : cur)
            if (x >> bit & 1)
                nxt[one++] = x;
            else
                nxt[zero++] = x;
        swap(cur, nxt);
    }
}
int kth(int l, int r, int k) {
    int x = 0;
    for (int level = 0; level < h; ++level) {
        int onesL = pref[level][l], onesR = pref[level][r];
        int zeros = r - l - (onesR - onesL);
        if (k < zeros) {
            l -= onesL;
            r -= onesR;
        }
        else {
            k -= zeros;
            x |= 1L << (h - level - 1);
            l = mid[level] + onesL;
            r = mid[level] + onesR;
        }
    }
    return x;
}
int cnt(int l, int r, int x) {
    if (x <= 0)
        return 0;
    if (x >= sigma)
        return r - l;
    int ans = 0;
    for (int level = 0; level < h; ++level) {
        int onesL = pref[level][l], onesR = pref[level][r];
        int zeros = r - l - (onesR - onesL);
        if (x >> (h - level - 1) & 1) {
            ans += zeros;
            l = mid[level] + onesL;
            r = mid[level] + onesR;
        }
        else {
            l -= onesL;
            r -= onesR;
        }
    }
    return ans;
}
