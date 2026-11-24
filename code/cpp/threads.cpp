#include <thread>
#include <atomic>

const int threadsCnt = 15, N = 1e8;

int x;
atomic <int> ans(1e18);
thread *th[threadsCnt];

void fnd(int l) {
    int r = l + N;
    for (int i = l; i < r; ++i)
        if (check(i) && i < ans)
            ans = i;
}

main() {
    for (int i = 0, l = 0; ans == 1e18; i = (i + 1) % threadsCnt, l += N) {
        if (th[i]) {
            th[i] -> join(); // Ожидание завершения потока
            delete th[i];
            cout << "Checked up to " << l - N * threadsCnt << '\n';
            th[i] = NULL;
        }
        th[i] = new thread(fnd, l);
    }
    // Ждём пока не завершатся остальные потоки, вдруг они улучшат ответ
    for (int i = 0; i < threadsCnt; ++i)
        if (th[i]) {
            th[i] -> join();
            delete th[i];
            th[i] = NULL;
        }
    cout << "Ans: " << ans;
}
