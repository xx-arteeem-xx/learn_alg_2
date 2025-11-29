#include <iostream>
#include <ctime>
using namespace std;


class two {
public:
    int a() {
        int k = 0, n;
        bool prime = true;
        cout << "Введите число для проверка на простоту: ";
        cin >> n;
        double start_time = clock(); // начальное время
        for (int i = 2; i < n; i++) {
            k++;
            if (n % i == 0) {
                cout << "Число не простое" << endl;
                prime = false;
                break;
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        if (prime) {
            cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
            return k;
        }
    }
    int b() {
        int k = 0, n;
        bool prime = true;
        cout << "Введите число для проверка на простоту: ";
        cin >> n;
        double start_time = clock(); // начальное время
        int i = 2;
        k++;
        if (n % i == 0) {
            cout << "Число не простое" << endl;
            prime = false;
        }
        i++;
        if (prime) {
            for (i; i < n; i += 2) {
                k++;
                if (n % i == 0) {
                    cout << "Число не простое" << endl;
                    prime = false;
                    break;
                }
            }
        }

        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        if (prime) {
            cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
            return k;
        }
    }
    int c() {
        int k = 0, n;
        bool prime = true;
        cout << "Введите число для проверка на простоту: ";
        cin >> n;
        double start_time = clock(); // начальное время
        for (int i = 2; i < (int)sqrt(n) + 1; i++) {
            k++;
            if (n % i == 0) {
                cout << "Число не простое" << endl;
                prime = false;
                break;
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        if (prime) {
            cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
            return k;
        }
    }
    int d() {
        int k = 0, n;
        bool prime = true;
        cout << "Введите число для проверка на простоту: ";
        cin >> n;
        double start_time = clock(); // начальное время
        int i = 2;
        k++;
        if (n % i == 0) {
            cout << "Число не простое" << endl;
            prime = false;
        }
        i++;
        if (prime) {
            for (i; i < (int)sqrt(n) + 1; i += 2) {
                k++;
                if (n % i == 0) {
                    cout << "Число не простое" << endl;
                    prime = false;
                    break;
                }
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        if (prime) {
            cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
            return k;
        }
    }
};

class three {
private:
    int c_recur(int n, int m,int &k) {
        if (m == 0)return n;
        k++;
        return c_recur(m, n % m, k);
    }
public:
    int a() {
        int x, y,nod,k=0;
        cout << "Введите x: "; cin >> x;
        cout << "Введите y: "; cin >> y;
        double start_time = clock(); // начальное время
        for (int i = 1; i < min(x, y); i++) {
            k+=2;
            if (x % i == 0 and y % i == 0)nod = i;
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
        return k;
    }
    int b() {
        int x, y, nod = 1, k=0;
        cout << "Введите x: "; cin >> x;
        cout << "Введите y: "; cin >> y;
        double start_time = clock(); // начальное время
        for (int i = min(x, y); i >=1; i--) {
            k += 2;
            if (x % i == 0 and y % i == 0) {
                nod = i;
                break;
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
        return nod;
    }
    int c() {
        int x, y,nod,k= 0;
        cout << "Введите x: "; cin >> x;
        cout << "Введите y: "; cin >> y;
        double start_time = clock(); // начальное время
        nod = c_recur(x, y,k);
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Сложность: " << k << "\t\tВремя: " << seconds << endl;
        return nod;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    three test;
    cout<< test.b();
}

