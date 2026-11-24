int x; long y; ulong u; ld d; char c; string s;
printf("%d %ld %lu %Lf %c %s\n", x, y, u, d, c, s.c_str());
// С прекодом (#define int long) для int тоже %ld
// double - %f, %x - 16-ричная, %% - знак процента
printf("%.9Lf %5ld %05ld", d, y, y); // 9 знаков после запятой; ширина 5 пробелами; нулями
// На Windows вместо %ld и %lu писать %lld и %llu
// C++23: print("{} {:.9f}\n", y, d); - проверяет типы
