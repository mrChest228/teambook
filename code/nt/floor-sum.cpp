long floorSum(long n, long m, long a, long b) {
    int128 ans = 0;
    while (true) {
        long qa = divFloor(a, m), qb = divFloor(b, m);
        ans += int128(qa) * n * (n - 1) / 2 + int128(qb) * n;
        a = (long)(int128(a) - int128(qa) * m);
        b = (long)(int128(b) - int128(qb) * m);
        // Ответ должен помещаться в long; m * n может превысить long, произведения - int128.
        int128 y = int128(a) * n + b;
        if (y < m)
            return (long)ans;
        n = y / m;
        b = y % m;
        swap(m, a);
    }
}
