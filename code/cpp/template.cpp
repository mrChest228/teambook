// Pragmas (before libraries includes to get the highest speed up)
#ifndef DEBUG
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,avx512f,avx512bw,avx512dbgi, sse4.2,bmi,bmi2,fma,popcnt,lzcnt,prefer-vector-width=512")
#endif

#include <bits/stdc++.h>

// Defines & typedefes
#define f first
#define s second
#define pb push_back
#define pf push_front
#define in insert
#define elif else if
#define gcd __gcd
#define nl '\n'

typedef long double ld; // sqrt, pow, ... от long считать через sqrtl, powl, ...: они в long double и точны до 2^64
typedef __int128 int128; // Или __int128_t
#define  long  int64_t
#define ulong uint64_t

using namespace std;
#define int long
mt19937_64 rnd(chrono::steady_clock::now(). time_since_epoch().count());

// DEBUG or RELEASE input
#ifdef DEBUG
    cin.exceptions(cin.failbit); //Выкидывает исключение (RE) при ошибке ввода (например, если читаешь число 10^18 в int, получишь RE вместо WA), влияние на время неизвестно
#else
    cin.tie(0); ios::sync_with_stdio(0);
#endif
