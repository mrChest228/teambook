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
== *2.6. Wavelet tree*#br
На $[l, r)$ за $O(log(sigma))$: $k$-я порядковая статистика, кол-во чисел $< x$. Память $O(n log(sigma))$, значения заранее сжать в $[0, sigma)$.`
`#code-file("code/ds/wavelet.cpp")``