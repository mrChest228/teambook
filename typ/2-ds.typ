#import "../book/default.typ": *;#heading(depth: 1)[*2. #underline[Data structures]*]
== *2.0. Курево по неявному ключу*#br
#code-file("code/ds/treap.cpp")#br
== *2.1. Дерево-Фенвика*#br
#code-file("code/ds/fenwick.cpp")#br
== *2.2. ДО Снизу*#br
#code-file("code/ds/segment-tree-bottom-up.cpp")#br
== *2.3. Segment Tree Beats*#br
#code-file("code/ds/segment-tree-beats.cpp")#br
== *2.4. Дерево Ли Чао*#br
#code-file("code/ds/li-chao.cpp")#br
== *2.5. Euler Tour Tree*#br
#code-file("code/ds/euler-tour-tree.cpp")#br
== *2.6. Wavelet matrix*#br
Массив не меняется, запросы на $[l, r)$ онлайн за $O(log(italic("MX")))$: #code("kth(l, r, k)") - $k$-е по возрастанию (с $0$), #code("cnt(l, r, x)") - кол-во чисел $< x$. Значения заранее сжать в $[0, italic("MX"))$.`
`Через них: кол-во в $[x, y)$ - #code("cnt(l, r, y) - cnt(l, r, x)"), максимум $< x$ - #code("kth(l, r, c - 1)"), где $c = $ #code("cnt(l, r, x)") $> 0$; медиана - #code("kth(l, r, (r - l) / 2)").`
`Устройство: на уровне $i$ числа стабильно разложены по биту #code("H - 1 - i"): слева нули (#code("mid[i]") штук), справа единицы. Если $L, R$ - единиц до $l$ и до $r$, отрезок переходит в $[l - L, r - R)$ среди нулей или в $[italic("mid") + L, italic("mid") + R)$ среди единиц. Спуск как в боре по битам ответа.`
`Против персистентного ДО (те же запросы и асимптотика), $n = q = 2 dot 10^5$: память $29$ МБ против $93$, запросы $184$ мс против $219$, без указателей и пула вершин. При малом $italic("MX")$ ещё выгоднее: при $italic("MX") = 2$ память $1.6$ МБ. ДО с сортированными векторами ($O(log^2)$ / $O(log^3)$) - $2043$ мс.`
`Задачи: $k$-я порядковая на отрезке (SPOJ MKTHNUM), кол-во чисел из $[x, y]$ на отрезке (SPOJ KQUERY), ближайшее к $x$ на отрезке. С префиксными суммами значений на каждом уровне - сумма $k$ наименьших на отрезке (сумма расстояний до медианы).`
`#code-file("code/ds/wavelet.cpp")``