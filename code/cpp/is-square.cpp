bool isSquare(int128 n) { // n >= 0
    if (!(0x213 >> int(n & 15) & 1)) // квадраты по модулю 16: 0, 1, 4, 9
        return false;
    ulong r = sqrtl(n); // у n = k^2 ошибка < 0.36, r = k
    return uint128(r) * r == n;
}
