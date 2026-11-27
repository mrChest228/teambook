// Точки a, b, c не на одной прямой
// Центр описанной. $R = a b c \/ (4 S)$
pair <ld, ld> circum(ld ax, ld ay, ld bx, ld by, ld cx, ld cy) {
    bx -= ax, by -= ay, cx -= ax, cy -= ay;
    ld b = bx * bx + by * by, c = cx * cx + cy * cy;
    ld d = 2 * (bx * cy - by * cx);
    return {ax + (cy * b - by * c) / d, ay + (bx * c - cx * b) / d};
}
// Центр вписанной: вершины с весами - длинами сторон напротив
// $r = 2 S \/ (a + b + c)$
pair <ld, ld> incenter(ld ax, ld ay, ld bx, ld by, ld cx, ld cy) {
    ld a = hypotl(bx - cx, by - cy);
    ld b = hypotl(ax - cx, ay - cy);
    ld c = hypotl(ax - bx, ay - by);
    ld x = a * ax + b * bx + c * cx, y = a * ay + b * by + c * cy;
    return {x / (a + b + c), y / (a + b + c)};
}
