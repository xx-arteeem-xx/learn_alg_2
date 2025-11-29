#include <iostream>
#include <vector>
#include <ctime>
#include <cstring>

using namespace std;

// ===== 1. Рекурсивные функции =====

// 1.1. Факториал
int factorial(int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

// 1.2. Сумма цифр числа
int sumOfDigits(int n) {
    if (n == 0) return 0;
    return n % 10 + sumOfDigits(n / 10);
}

// 1.3. Цифровой корень числа
int digitalRoot(int n) {
    if (n < 10) return n;
    return digitalRoot(sumOfDigits(n));
}

// 1.4. Сумма чисел от 1 до N
int sumUpToN(int n) {
    if (n == 1) return 1;
    return n + sumUpToN(n - 1);
}

// ===== 2. Рекурсивные процедуры =====

// 2.1. Вывод чисел от 1 до N
void print1ToN(int n) {
    if (n > 1) print1ToN(n - 1);
    cout << n << " ";
}

// 2.2. Вывод чисел от N до 1
void printNTo1(int n) {
    if (n == 0) return;
    cout << n << " ";
    printNTo1(n - 1);
}

// 2.3. Вывод чётных чисел от 2 до N
void printEven(int n) {
    if (n < 2) return;
    printEven(n - 1);
    if (n % 2 == 0) cout << n << " ";
}

// ===== 3. Рекурсивная функция с двумя аргументами =====

// 3.1. Алгоритм Евклида (НОД)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// ===== 4. Реализации чисел Фибоначчи =====

// 4.1. Рекурсивная без оптимизации
int fibBasic(int n) {
    return n < 2 ? n : fibBasic(n - 1) + fibBasic(n - 2);
}

// 4.2. Рекурсивная с кеш-памятью
vector<int> cache(1000, -1);
int fibCached(int n) {
    if (n < 2) return n;
    if (cache[n] != -1) return cache[n];
    cache[n] = fibCached(n - 1) + fibCached(n - 2);
    return cache[n];
}

// 4.3. Итеративная с временным массивом
int fibArray(int n) {
    if (n < 2) return n;
    vector<int> f(n + 1);
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];
    return f[n];
}

// 4.4. Итеративная с вычислением "на лету"
int fibOnTheFly(int n) {
    if (n < 2) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ===== 5. Эксперименты =====

void resetCache() {
    fill(cache.begin(), cache.end(), -1);
}

int main() {
    // Тестирование рекурсивных функций
    cout << "Факториал 5: " << factorial(5) << endl;
    cout << "Сумма цифр 12345: " << sumOfDigits(12345) << endl;
    cout << "Цифровой корень 12345: " << digitalRoot(12345) << endl;
    cout << "Сумма чисел от 1 до 10: " << sumUpToN(10) << endl;

    // Тестирование рекурсивных процедур
    cout << "Числа от 1 до 5: "; print1ToN(5); cout << endl;
    cout << "Числа от 5 до 1: "; printNTo1(5); cout << endl;
    cout << "Чётные числа до 10: "; printEven(10); cout << endl;

    // Тестирование функции с двумя аргументами
    cout << "НОД(48, 18): " << gcd(48, 18) << endl;

    // Эксперименты с Фибоначчи
    int n = 40;
    clock_t start;

    cout << "\nЭксперименты с Фибоначчи (n=" << n << "):" << endl;

    start = clock();
    cout << "Рекурсивная без оптимизации: " << fibBasic(n) << endl;
    cout << "Время: " << (clock() - start) * 1000 / CLOCKS_PER_SEC << " мс" << endl;

    resetCache();
    start = clock();
    cout << "Рекурсивная с кешем: " << fibCached(n) << endl;
    cout << "Время: " << (clock() - start) * 1000 / CLOCKS_PER_SEC << " мс" << endl;

    start = clock();
    cout << "Итеративная с массивом: " << fibArray(n) << endl;
    cout << "Время: " << (clock() - start) * 1000 / CLOCKS_PER_SEC << " мс" << endl;

    start = clock();
    cout << "Итеративная на лету: " << fibOnTheFly(n) << endl;
    cout << "Время: " << (clock() - start) * 1000 / CLOCKS_PER_SEC << " мс" << endl;

    return 0;
}