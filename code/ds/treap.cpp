struct Node {
    int sz, y, val;
    Node *L = 0,
         *R = 0;
    Node (int val): sz(1), y(rnd()), val(val) {}
};

Node *root;

int size(Node *node) { return node ? node -> sz : 0; }
void calc(Node *node) {
    node -> sz = 1 + size(node -> L) + size(node -> R);
    //...
}
Node* merge(Node *l, Node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l -> y > r -> y) {
        l -> R = merge(l -> R, r);
        calc(l);
        return l;
    }
    else {
        r -> L = merge(l, r -> L);
        calc(r);
        return r;
    }
}
pair <Node*, Node*> split(Node *p, int k) { //Вырезать первые 0 <= k <= n элементов
    if (!p) return {0, 0};
    if (size(p -> L) + 1 <= k) {
        auto q = split(p -> R, k - size(p -> L) - 1);
        p -> R = q.f;
        calc(p);
        return {p, q.s};
    }
    else {
        auto q = split(p -> L, k);
        p -> L = q.s;
        calc(p);
        return {q.f, p};
    }
}
Node* cut(int l, int r) { // 0 <= l <= r < n
    auto q1 = split(root, r + 1);
    auto q2 = split(q1.f, l);
    root = merge(q2.f, q1.s);
    return q2.s;
}
void insert(Node *v, int k) { // 0 <= k <= n
    auto q = split(root, k);
    root = merge(q.f, merge(v, q.s));
}
