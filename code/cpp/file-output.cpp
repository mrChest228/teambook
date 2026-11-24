fout.open("answers.txt", ios::app); // ios::app - дописывание в конец файла
fout << "Ans: " << ans; // Строку может разорвать, если другой поток запустится во время копирования

// Атомарная запись в файл (строку не разорвет)

#include <cstdio>

FILE* f = fopen("output.txt", "a"); // 'a' - дописывание в конец файла
if (f != NULL) {
    fprintf(f, "Ans: %ld", ans); // %ld - long
    fclose(f); // 3. Закрываем
}

// С С++20

#include <syncstream>

osyncstream(std::cout) << "ans: " << ans;
