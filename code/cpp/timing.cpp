// chrono: время как на часах. Единицы - второй параметр duration:
// duration <ld> - с, duration <ld, milli> - мс, duration <ld, nano> - нс
auto st = chrono::steady_clock::now();
// Замеряемый код
auto en = chrono::steady_clock::now();
ld ms = chrono::duration <ld, milli /*or nano*/>(en - st).count();
long ns = (en - st).count(); // Целые нс. duration <long, milli> не скомпилируется

// clock(): секунды с начала программы. На Windows время как на часах. На Linux время процессора: суммируется по всем потокам и не идёт при sleep и ожидании ввода, поэтому с потоками (1.2) нужен chrono
ld sec = ld(clock()) / CLOCKS_PER_SEC;
