#import "../book/default.typ": *;#heading(depth: 1)[_`        `_*1. #underline[C++]*]
#code-file("code/cpp/template.cpp")#br
== *1.1. Data structures*#br
#code-file("code/cpp/data-structures.cpp")#br
== *1.2. Потоки*#br
#code-file("code/cpp/threads.cpp")#br
== *1.3. Вывод в файл*#br
#code-file("code/cpp/file-output.cpp")#br
=== *1.3.1. printf*#br
#code("printf(формат, ...)") - в консоль, #code("fprintf(f, формат, ...)") - в файл. Тип не проверяется: при несовпадении с форматом выводится мусор (предупреждение даёт #code("-Wall")).`
`#code-file("code/cpp/printf.cpp")#br
== *1.4. Builtins*#br
#code("__builtin_clzll(x)") - кол-во $0$ после старшей $1$ в битовом представлении. При $x = 0$ - UB.`
`#code("__builtin_ctzll(x)") - кол-во $0$ перед младшей $1$ в битовом представлении. При $x = 0$ - UB. Поиск делимости на $2^k$.`
`#code("__builtin_parityll(x)") - чётность кол-ва $1$ в битовом представлении. Аналогично #code("__builtin_popcount(x) & 1"), у bitset - #code("b.count() & 1").`
`#code("__builtin_mul_overflow(a, b, &res)") - умножает a на b, сохраняет результат в res. Возвращает true, если произошло переполнение, и false, если всё ок.`
`Целый $floor(log_2(x))$: #code("__lg(x)") - одна инструкция (1 нс, #code("log2l") - 28 нс). Есть для int, long, long long и их unsigned, ответ того же типа, что и $x$. При $x = 0$ - UB, для #code("__int128") нет.`
`$floor(sqrt(x))$ для long: #code("sqrtl(x)") (точно для всех long: 64-битная мантисса #code("long double")); #code("sqrt") в double (53 бита) на больших $x = k^2 - 1$ даёт $k$.`
`#code-file("code/cpp/is-square.cpp")#br
=== *1.4.1. Округление и деление*#br
#code("lround(x)") / #code("llround(x)") - ближайшее целое в long / long long, половины от нуля: $2.5 -> 3$, $-2.5 -> -3$.`
`#code("floor(x)") - вниз: $-2.5 -> -3$, #code("trunc(x)") и #code("long(x)") - к нулю: $-2.5 -> -2$ (клетка сетки для отрицательных - только floor). Целое #code("a / b") - это trunc: при одинаковых знаках равно floor, при разных - ceil. При $a = -7, b = 2$: #code("a / b") $= -3$, floor $= -4$, ceil $= -3$.`
`#code("(a + b - 1) / b") - ceil только при $a >= 0, b > 0$. Ошибки: $a = -2, b = 2$: $0$ вместо $-1$; $a = 7, b = -2$: $-2$ вместо $-3$; $a = -7, b = -2$: $5$ вместо $4$.`
`Кол-во кратных $b$ на $[l, r]$: #code("divFloor(r, b) - divFloor(l - 1, b)"). floor и ceil при любых знаках:`
`#code-file("code/cpp/div.cpp")#br
=== *1.4.2. Большие константы, powl*#br
#code("1e18") - это double (53 бита): #code("long x = 1e18 + 7") даёт $10^18$, #code("1e17 + 3") - $10^17$. Степени 10 до $10^22$ точны, double точен до $2^53 approx 9 dot 10^15$, поэтому #code("int(1e9 + 7)") - ок. Дальше #code("long(1e18) + 7") или #code("1'000'000'000'000'000'007") (разделители разрядов, C++14).`
`Кол-во цифр: #code("to_string(x).size()"), не #code("log10l(x) + 1"): #code("log10l(999999999999999999)") = 18.`
`#code("powl") от целых в 45 раз медленнее бинарного возведения. Без своего: #code("__builtin_powil(x, n)") (#code("n") - int) - $O(log(n))$ умножений, в 1.5 раза медленнее бинарного, ответы до $9 dot 10^18$ точны.#br
== *1.5. Runtime Errors*#br
*0xC0000005* - Access Violation. Причины: выход за границы массива, слишком большой массив в стеке, обращение к NULL-указателю.`
`*0xC00000FD* - Stack Overflow. Причины: бесконечная/очень глубокая рекурсия, слишком большой массив в стеке.`
`*0xC0000374* - Heap Corruption. Повреждение кучи (динамической памяти), программа часто падает не в момент ошибки, а позже (когда пытается удалить или выделить память). Причины: запись за границы массива, вызвал #code("delete") второй раз (или просто к мусору).`
`*0xC0000094* - Integer Divide by Zero.`
`*0xC000001D* - Illegal Instruction. Причины: выход из не-void функции без return. (_-Werror=return-type_ в Other compiler options)`
`*0xC0000417* - Invalid C Runtime Parameter. Причины: assert failed или непойманное исключение.#br
== *1.6. Замер времени*#br
#code-file("code/cpp/timing.cpp")#br
== *1.7. Move(v)*#br
В нагруженных рекурсивных функциях, возвращающих vector / set, писать #code("return move(v);"). Без него контейнер копируется за $O(n)$, если возвращается не просто локальная переменная: #code("return x ? a : b;"), #code("return res[v];"), #code("return p.f;").`
`Ссылка без const не принимает rvalue (временный объект): для #code("int f(string &s)") вызов #code("f(t)") - ок, #code("f(t + \"#\")") и #code("f(\"abc\")") не компилируются. #code("int f(const string &s)") принимает и то, и другое.#br
== *1.8. clamp*#br
#code("clamp(x, l, r)") (C++17, #code("<algorithm>")) - $x$, прижатый к $[l, r]$: #code("x < l ? l : r < x ? r : x"). Все 3 аргумента одного типа: при #code("#define int long") писать #code("clamp(x, int(0), n)"). При $l > r$ - UB (GCC вернёт $l$ при $x < l$, иначе $r$, с #code("-D_GLIBCXX_ASSERTIONS") - падение). NaN возвращается как есть. #code("clamp(x, l, r, comp)") - со своим сравнением.``