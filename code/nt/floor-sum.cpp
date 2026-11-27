long floorSum(long n, long m, long a, long b) {
    long qa = a / m - (a % m < 0), qb = b / m - (b % m < 0);
    long ra = a % m, rb = b % m;
    if (ra < 0)
        ra += m;
    if (rb < 0)
        rb += m;

    int128 ans = int128(qa) * n * (n - 1) / 2 + int128(qb) * n;
    a = ra;
    b = rb;
    // Ответ должен помещаться в long; промежуточные суммы считаются в int128.
    while (true) {
        if (a >= m) {
            ans += int128(n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += int128(n) * (b / m);
            b %= m;
        }
        int128 y = int128(a) * n + b;
        if (y < m)
            break;
        n = y / m;
        b = y % m;
        swap(m, a);
    }
    return (long)ans;
}
