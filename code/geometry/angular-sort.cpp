// По часовой стрелке, начиная с направления вверх
bool comp(const pair <long, long> &a, const pair <long, long> &b) {
    const pair <long, long> o{}; // -O2 и -O3 её убирают
    if ((a >= o) != (b >= o)) // Левая полуплоскость позже правой
        return a >= o;
    return a.s * b.f > b.s * a.f;
}
