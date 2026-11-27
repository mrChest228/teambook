// $sum_(i = 0)^(n - 1) floor((a i + b) / m)$, m > 0, a и b любого знака, n * m и ответ влезают в long. O(log(m))
int floorSum(int n, int m, int a, int b) {
    int ans = 0;
    while (true) {
        int qa = divFloor(a, m), qb = divFloor(b, m);
        ans += qa * (n * (n - 1) / 2) + qb * n;
        a -= qa * m;
        b -= qb * m;
        int y = a * n + b; // Кол-во точек - под прямой, считаем их по столбцам вместо строк
        if (y < m)
            return ans;
        n = y / m;
        b = y % m;
        swap(m, a);
    }
}
