#import "../default.typ": *;#br
#heading(depth: 1)[*4.` `#underline[Strings]*#br]
== *4.0.` `Z-функция*#br
#code-file("code/strings/z-function.cpp")#br
== *4.1.` `Префикс-функция*#br
#code-file("code/strings/prefix-function.cpp")#br
== *4.2.` `Суффиксный` `массив` `+` `LCP*#br
#code("sf")` `-` `суфф.` `массив,` `#code("num[i]")` `-` `позиция` `суффикса` `#code("i")` `в` `#code("sf"),` `#code("lcp[i]")` `-` `lcp` `суффиксов` `#code("sf[i]")` `и` `#code("sf[i + 1]").` `$O(n log(n))$.`
`lcp` `суффиксов` `#code("i"),` `#code("j")` `за` `$O(1)$:` `разреженная` `таблица` `по` `#code("lcp"),` `ответ` `#code("min(lcp[L..R - 1])"),` `где` `#code("L = min(num[i], num[j])"),` `#code("R = max(num[i], num[j])").`
`#code-file("code/strings/suffix-array.cpp")#br
== *4.3.` `Манакер*#br
#code-file("code/strings/manacher.cpp")``