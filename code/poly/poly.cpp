const int N = 1 << 20;

void shrink(vector <int> &v) { // Убираем нули в конце
    while (v.size() > 1 && v.back() == 0)
        v.pop_back();
}

template <int MOD, int G> // G - первообразный корень (обычно 3)
struct Poly {
    vector <int> inv1;
    vector <int> rt; // rt[k + j] = w^j, где w^(2k) = 1: корни для блока длины 2k лежат подряд
    int inv(int x) {
        if (x < inv1.size())
            return inv1[x];
        return MOD - 1LL * MOD / x * inv(MOD % x) % MOD;
    }
    int powm(int x, long k /*0 <= k < MOD - 1*/) {
        int ans = 1;
        for (int y = x; k > 0; k >>= 1, y = 1LL * y * y % MOD)
            if (k & 1)
                ans = 1LL * ans * y % MOD;
        return ans;
    }
    Poly() {
        inv1.resize(N + 1);
        inv1[1] = 1;
        for (int i = 2; i <= N; ++i)
            inv1[i] = MOD - 1LL * MOD / i * inv1[MOD % i] % MOD;
        rt.resize(N);
        for (int k = 1; k < N; k <<= 1) {
            int w = powm(G, (MOD - 1) / (k * 2));
            rt[k] = 1;
            for (int j = 1; j < k; ++j)
                rt[k + j] = 1LL * rt[k + j - 1] * w % MOD;
        }
    }
    // Прямое (DIF) выдаёт значения в порядке перевёрнутых битов, обратное (DIT) принимает их в этом же порядке:
    // перестановка не нужна, пока между ними только поэлементные операции
    void NTT(vector <int> &a, bool inverse /*обратное ли преобразование*/) {
        int n = a.size(); // n - степень двойки
        if (!inverse) {
            for (int k = n / 2; k >= 1; k >>= 1) // от длинных блоков к коротким
                for (int i = 0; i < n; i += k * 2)
                    for (int j = 0; j < k; j++) {
                        int u = a[i + j], v = a[i + j + k];
                        a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                        a[i + j + k] = 1LL * (u - v + MOD) * rt[k + j] % MOD;
                    }
            return;
        }
        for (int k = 1; k < n; k <<= 1) // от коротких блоков к длинным
            for (int i = 0; i < n; i += k * 2)
                for (int j = 0; j < k; j++) {
                    int u = a[i + j], v = 1LL * a[i + j + k] * rt[k + j] % MOD;
                    a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                    a[i + j + k] = u < v ? u - v + MOD : u - v;
                }
        reverse(a.begin() + 1, a.end()); // w^(-j) = w^(n - j)
        int invN = inv1[n];
        for (int &u : a)
            u = 1LL * u * invN % MOD;
    }
    // A * B, a.size() + b.size() - 1 коэффициентов
    vector <int> mult(vector <int> a, vector <int> b) {
        int sz = a.size() + b.size() - 1, n = 1;
        while (n < sz)
            n <<= 1;
        a.resize(n); b.resize(n);
        NTT(a, false); NTT(b, false);
        for (int i = 0; i < n; i++)
            a[i] = (1LL * a[i] * b[i]) % MOD;
        NTT(a, true);
        a.resize(sz);
        return a;
    }

    vector <int> deriv(const vector <int> &a) { // A'(x)
        if (!a.size())
            return {};
        vector <int> res(a.size() - 1);
        for (int i = 0; i < a.size() - 1; ++i)
            res[i] = 1LL * a[i + 1] * (i + 1) % MOD;
        return res;
    }
    vector <int> integ(const vector <int> &a) {
        vector <int> res(a.size() + 1);
        for (int i = 1; i <= a.size(); ++i)
            res[i] = 1LL * a[i - 1] * inv(i) % MOD;
        return res;
    }
    // 1 / A. a[0] != 0
    vector <int> inv(const vector <int> &a) {
        vector <int> b = { inv(a[0]) };
        for (int m = 2;; m <<= 1) {
            vector <int> sub(a.begin(), a.begin() + min(int(a.size()), m));
            sub.resize(m * 2); b.resize(m * 2);
            NTT(sub, false); NTT(b, false);
            for (int i = 0; i < m * 2; ++i) // B * (2 - A * B)
                b[i] = 1LL * b[i] * (2 - 1LL * sub[i] * b[i] % MOD + MOD) % MOD;
            NTT(b, true);
            b.resize(m);
            if (m >= a.size())
                break;
        }
        b.resize(a.size());
        return b;
    }
    // ln(A). a[0] == 1
    vector <int> ln(const vector <int> &a) {
        assert(a[0] == 1);
        vector <int> res = mult(deriv(a), inv(a)); // A' * (1/A)
        res.resize(a.size() - 1);
        return integ(res);
    }
    // exp(A). A[0] == 0
    vector <int> exp(const vector <int> &a) {
        assert(a[0] == 0);
        vector <int> b = {1};
        for (int m = 2;; m <<= 1) {
            b.resize(m);
            vector <int> lnb = ln(b);
            for (int i = 0; i < m; i++)
                lnb[i] = ((i < a.size() ? a[i] : 0) - lnb[i] + MOD) % MOD;
            lnb[0] = (lnb[0] + 1) % MOD; // 1 + A - ln(B)
            b = mult(b, lnb);
            if (m >= a.size())
                break;
        }
        b.resize(a.size());
        return b;
    }
    // A^k, первые a.size() коэффициентов
    vector <int> pow(vector <int> a, long k) {
        int sz = a.size(), deg = sz - 1, n = 1, cnt0 = 0;
        while (deg > 0 && a[deg] == 0)
            --deg;
        if (k <= (sz - 1) / max(deg, 1)) { // A^k помещается целиком: возводим в степень каждое значение
            while (n < sz)
                n <<= 1;
            a.resize(n);
            NTT(a, false);
            for (int &u : a)
                u = powm(u, k);
            NTT(a, true);
            a.resize(sz);
            return a;
        }
        while (cnt0 < sz && a[cnt0] == 0)
            ++cnt0;
        if (cnt0 == sz || cnt0 > (sz - 1) / k)
            return vector <int> (sz);
        vector <int> sub(a.begin() + cnt0, a.end());
        int inv0 = inv(sub[0]),
            pow0 = powm(sub[0], k % (MOD - 1));
        for (int &u : sub)
            u = 1LL * u * inv0 % MOD;
        sub = ln(sub);
        for (int &u : sub)
            u = 1LL * u * (k % MOD) % MOD;
        sub = exp(sub);
        cnt0 *= k;
        for (int i = sz - 1; i >= 0; --i)
            a[i] = (cnt0 <= i ? 1LL * sub[i - cnt0] * pow0 % MOD : 0);
        return a;
    }
    // A^(1 / r), первые a.size() - t + t / r коэффициентов, t - нули в начале
    // {}, если корня нет. Нужен root(c, r) из 3.7 с mod = MOD, g = G
    vector <int> root(vector <int> a, int r) {
        assert(mod == MOD);
        int sz = a.size(), t = 0;
        while (t < sz && a[t] == 0)
            ++t;
        if (t == sz)
            return a;
        long c = ::root(a[t], r); // A = c x^t (1 + ...)
        if (t % r || c == -1)
            return {};
        vector <int> sub(a.begin() + t, a.end());
        int inv0 = inv(sub[0]), invr = inv(r);
        for (int &u : sub)
            u = 1LL * u * inv0 % MOD;
        sub = ln(sub);
        for (int &u : sub)
            u = 1LL * u * invr % MOD; // 1 / r - множитель
        sub = exp(sub);
        vector <int> res(t / r);
        for (int u : sub)
            res.pb(1LL * u * c % MOD);
        return res;
    }
    // A = Q * B + R. В Q a.size() - b.size() + 1 коэффициентов, в R - b.size() - 1. b.back() != 0
    pair <vector <int>, vector <int>> divMod(const vector <int> &a, const vector <int> &b) {
        assert(b.back() != 0);
        int n = a.size(), m = b.size();
        if (n < m)
            return {{0}, a};
        vector <int> ra = a, rb = b;
        reverse(ra.begin(), ra.end());
        reverse(rb.begin(), rb.end());
        int sz = n - m + 1;
        ra.resize(sz);
        rb.resize(sz);
        vector <int> q = mult(ra, inv(rb));
        q.resize(sz);
        reverse(q.begin(), q.end());
        vector <int> bq = mult(b, q), r(m - 1);
        for (int i = 0; i < m - 1; ++i)
            r[i] = (a[i] - bq[i] + MOD) % MOD;
        return {q, r};
    }
};

Poly <998'244'353, 3>   p998;  // n <= 2^23 <=  8'388'608
Poly <1'004'535'809, 3> p1004; // n <= 2^21 <=  2'097'152
Poly <469'762'049, 3>   p469;  // n <= 2^26 <= 67'108'864
// Main
vec <int> c = p998.mult(a, b);
