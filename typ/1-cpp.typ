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
`$floor(log_2(x))$: #code("31 - __builtin_clz(x)") / #code("63 - __builtin_clzll(x)")`
`#code("__builtin_ctzll(x)") - кол-во $0$ перед младшей $1$ в битовом представлении. При $x = 0$ - UB. Поиск делимости на $2^k$.`
`#code("__builtin_parityll(x)") - чётность кол-ва $1$ в битовом представлении. Аналогично #code("__builtin_popcount(x) & 1").`
`#code("__builtin_mul_overflow(a, b, &res)") - умножает a на b, сохраняет результат в res. Возвращает true, если произошло переполнение, и false, если всё ок.`
`Целые $floor(log_2(x))$: #code("__lg(x)") или #code("bit_width(x) - 1") (1 нс, #code("log2l") - 28 нс). #code("powl") от long в 10 раз медленнее бинарного возведения, #code("log10l(999999999999999999)") = 18.`
`$floor(sqrt(x))$ для long: #code("sqrtl(x)") (точно для всех long: 64-битная мантисса #code("long double")); #code("sqrt") в double (53 бита) на больших $x = k^2 - 1$ даёт $k$.`
`#code-file("code/cpp/is-square.cpp")#br
=== *1.4.1. Округление и деление*#br
#code("lround(x)") / #code("llround(x)") - ближайшее целое в long / long long, половины от нуля: $2.5 -> 3$, $-2.5 -> -3$.`
`#code("floor(x)") - вниз: $-2.5 -> -3$, #code("trunc(x)") и #code("long(x)") - к нулю: $-2.5 -> -2$ (клетка сетки для отрицательных - только floor). Целое #code("a / b") - это trunc: при одинаковых знаках равно floor, при разных - ceil. При $a = -7, b = 2$: #code("a / b") $= -3$, floor $= -4$, ceil $= -3$.`
`#code("(a + b - 1) / b") - ceil только при $a >= 0, b > 0$. Ошибки: $a = -2, b = 2$: $0$ вместо $-1$; $a = 7, b = -2$: $-2$ вместо $-3$; $a = -7, b = -2$: $5$ вместо $4$.`
`Кол-во кратных $b$ на $[l, r]$: #code("divFloor(r, b) - divFloor(l - 1, b)"). floor и ceil при любых знаках:`
`#code-file("code/cpp/div.cpp")#br
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
В нагруженных рекурсивных функциях, возвращающих vector / set, писать #code("return move(v);"). Без него контейнер копируется за $O(n)$, если возвращается не просто локальная переменная: #code("return x ? a : b;"), #code("return res[v];"), #code("return p.f;").``