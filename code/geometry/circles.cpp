// Центр описанной окружности, точки не на одной прямой. $R = a b c \/ (4 S)$
pair <ld, ld> circum(ld ax, ld ay, ld bx, ld by, ld cx, ld cy) {
    bx -= ax, by -= ay, cx -= ax, cy -= ay;
    ld b = bx * bx + by * by, c = cx * cx + cy * cy, d = 2 * (bx * cy - by * cx);
    return {ax + (cy * b - by * c) / d, ay + (bx * c - cx * b) / d};
}
// Центр вписанной: вершины с весами - длинами противоположных сторон. $r = 2 S \/ (a + b + c)$
pair <ld, ld> incenter(ld ax, ld ay, ld bx, ld by, ld cx, ld cy) {
    ld a = hypotl(bx - cx, by - cy), b = hypotl(ax - cx, ay - cy), c = hypotl(ax - bx, ay - by);
    return {(a * ax + b * bx + c * cx) / (a + b + c), (a * ay + b * by + c * cy) / (a + b + c)};
}
