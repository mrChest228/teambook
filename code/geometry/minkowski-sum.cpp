struct point {
    long x, y;
    point operator+(point &a) { return {x + a.x, y + a.y}; }
    point operator-(point &a) { return {x - a.x, y - a.y}; }
    long cross(point &a) { return x * a.y - y * a.x; }
    long dot(point &a) { return x * a.x + y * a.y; }
    long len2() { return x * x + y * y; }
};

void normalize(vector <point> &p) { // Убираем точки на сторонах
    int n = p.size();
    if (n < 3) // Точка или отрезок
        return;
    vector <point> res;
    for (int i = 0; i < n; i++) {
        point a = p[i] - p[(i + n - 1) % n], b = p[(i + 1) % n] - p[i];
        if (a.cross(b) != 0)
            res.pb(p[i]);
    }
    p = res;
}

void reorder(vector <point> &p) { // Переупорядочиваем, чтобы начиналось с нижнего-левого (лексикографически)
    int pos = 0;
    for (int i = 1; i < p.size(); i++)
        if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector <point> minkowski(vector <point> a, vector <point> b) {
    reorder(a);
    reorder(b);

    vector <point> res;
    res.pb(a[0] + b[0]);

    int i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        if (i == a.size()) {
            point edge = b[(j + 1) % b.size()] - b[j];
            res.pb(res.back() + edge);
            ++j;
            continue;
        }
        if (j == b.size()) {
            point edge = a[(i + 1) % a.size()] - a[i];
            res.pb(res.back() + edge);
            ++i;
            continue;
        }
        point edgeA = a[(i + 1) % a.size()] - a[i], edgeB = b[(j + 1) % b.size()] - b[j];
        long cp = edgeA.cross(edgeB);

        point edge = cp < 0 ? edgeA : (cp > 0 ? edgeB : edgeA + edgeB);
        res.pb(res.back() + edge);

        if (cp <= 0) ++i;
        if (cp >= 0) ++j;
    }
    res.pop_back(); // Последняя точка совпадает с первой
    return res;
}

ld distToSegment(point p, point a, point b) {
    point ab = b - a, ap = p - a;
    if (ab.dot(ap) <= 0) // Ближе к A
        return sqrtl(ap.len2());
    point ba = a - b, bp = p - b;
    if (ba.dot(bp) <= 0) // Ближе к B
        return sqrtl(bp.len2());
    return abs(ab.cross(ap)) / sqrtl(ab.len2()); // Перпендикуляр
}

// Расстояние между a и b; 0, если пересекаются
ld dist(vector <point> a, vector <point> b) {
    for (point &p : b)
        p = {-p.x, -p.y};
    vector <point> c = minkowski(a, b);
    ld res = 1e18;
    bool inside = 1; // (0, 0) строго внутри c
    for (int i = 0; i < c.size(); i++) {
        point p = c[i], q = c[(i + 1) % c.size()];
        // Граница не для a и b, а для вершин и сторон суммы c = a + (-b): иначе len2, dot и cross не влезут в long
        assert(max({abs(p.x), abs(p.y), abs(q.x - p.x), abs(q.y - p.y)}) <= 2e9);
        inside &= p.cross(q) < 0;
        res = min(res, distToSegment({0, 0}, p, q));
    }
    return inside ? 0 : res;
}
// Main
vector <point> a(n), b(m);
// Читаем a и b по часовой стрелке
normalize(a);
normalize(b);
cout << dist(a, b); // 0, если пересекаются или касаются
