#import "../book/default.typ": *;#heading(depth: 1)[*4. #underline[Strings]*]
== *4.0. Z-функция*#br
#code-file("code/strings/z-function.cpp")#br
== *4.1. Префикс-функция*#br
#code-file("code/strings/prefix-function.cpp")#br
== *4.2. Манакер*#br
#code-file("code/strings/manacher.cpp")#br
== *4.3. Ахо–Корасик*#br
#code("to") - рёбра бора, #code("suf") - суфф. ссылки, #code("go") - переход автомата, #code("K") - размер алфавита. #code("add") возвращает конечную вершину строки. #code("occ") - пример: на каждом шаге по #code("t") #code("++cnt[v]"), затем #code("cnt[suf[v]] += cnt[v]") от глубоких вершин к корню, $O(|t| + N)$.`
`а) #code("map"): память $O(N)$, #code("build") за $O(N log(K))$, проход по тексту #code("v = go(v, c)") - амортизированно $O(log(K))$ на символ.`
`#code-file("code/strings/aho-corasick.cpp")`
`б) Ленивые #code("go") и #code("suf"): память $O(N K)$, каждое значение считается один раз. #code("init()") перед #code("add"). Все #code("add") - до первого #code("getGo")/#code("getSuf"), иначе в кэше остаются старые значения.`
`#code-file("code/strings/aho-corasick-lazy.cpp")`
`Кол-во вхождений каждой строки: при проходе текста #code("++cnt[v]"), затем по вершинам в порядке убывания глубины (#code("q") с конца) #code("cnt[suf[v]] += cnt[v]"), ответ - #code("cnt") конечной вершины строки. Вместо #code("map") в каждой вершине можно завести одну #code("unordered_map") по ключу #code("v * K + c"): быстрее, но уязвима к анти-хеш тестам.#br
== *4.4. Суффиксный массив + LCP*#br
#code("sf") - суфф. массив, #code("num[i]") - позиция суффикса #code("i") в #code("sf"), #code("lcp[i]") - lcp суффиксов #code("sf[i]") и #code("sf[i + 1]"). $O(n log(n))$.`
`lcp суффиксов #code("i"), #code("j") за $O(1)$: разреженная таблица по #code("lcp"), ответ #code("min(lcp[L..R - 1])"), где #code("L = min(num[i], num[j])"), #code("R = max(num[i], num[j])").`
`#code-file("code/strings/suffix-array.cpp")``