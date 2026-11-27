const int MOD = 998'244'353;

void fwht(vector <int> &a, bool inverse) {
    int n = a.size();
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += k * 2)
            for (int j = 0; j < k; j++) {
                int u = a[i + j], v = a[i + j + k];
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + k] = u < v ? u - v + MOD : u - v;
            }
    if (inverse) {
        int invN = powm(n, MOD - 2);
        for (int &x : a)
            x = 1LL * x * invN % MOD;
    }
}
vector <int> xorMult(vector <int> a, vector <int> b) {
    fwht(a, false);
    fwht(b, false);
    for (int i = 0; i < a.size(); ++i)
        a[i] = 1LL * a[i] * b[i] % MOD;
    fwht(a, true);
    return a;
}
