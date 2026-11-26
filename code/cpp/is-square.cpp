bool isSquare(int128 n) { // n >= 0
    if (!(0x213 >> int(n & 15) & 1)) // квадраты по модулю 16: 0, 1, 4, 9
        return false;
    ulong r = sqrtl(n); // в long double 64 бита, ошибка на единицы
    while (uint128(r) * r > n)
        --r;
    while (uint128(r + 1) * (r + 1) <= n)
        ++r;
    return uint128(r) * r == n;
}
