long divFloor(long a, long b) { // (-7, 2) -> -4, (7, 2) -> 3
    return a / b - (a % b && (a ^ b) < 0); // знаки разные
}
long divCeil(long a, long b) { // (-7, 2) -> -3, (7, 2) -> 4
    return a / b + (a % b && (a ^ b) >= 0);
}
