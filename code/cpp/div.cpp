long divFloor(long a, long b) {
    return a / b - (a % b && (a ^ b) < 0); // знаки разные
}
long divCeil(long a, long b) {
    return a / b + (a % b && (a ^ b) >= 0);
}
