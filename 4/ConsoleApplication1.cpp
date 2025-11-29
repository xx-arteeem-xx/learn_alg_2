

#include <iostream>
#include <string>
using namespace std;

class one {
public:
    int fact(int x) {
        if (x == 1)return 1;
        else return x * (fact(x - 1));
    }
    int summ(int x) {
        if (x == 1)return 1;
        else return x + (summ(x - 1));
    }
    int sqrt_int(int x) {
        if (x < 10)return x;
        else {
            string temp_x = to_string(x);
            int summ = 0;
            for (int i = 0; i < temp_x.size(); i++) {
                int temp_int = temp_x[i] - '0';
                summ += temp_int;

            }
            //cout << summ<<endl;
            return sqrt_int(summ);
        }

    }
};
class two {
public:
    void OnetoN(int x) {
        if (x>1) {
            OnetoN(x - 1);
        }
        cout << x <<endl;
    }
    void NtoOne(int x) {
        cout << x << endl;
        if (x > 1) {
            NtoOne(x - 1);
        }
        
    }
    void minusNToN(int x) {
        cout << x*-1 << endl;
        if (x > -x) {
            minusNToN(x - 1);
            cout << x << endl;
        }
    }
    void NTominusN(int x) {
        cout << x << endl;
        if (x > -x) {
            NTominusN(x - 1);
            cout << x*-1 << endl;
        }
    }
};

class three {
public:
    int evklid(int n,int m) {
        if (m == 0)return n;
        else return evklid(m, n % m);
    }
};

class Four {
private:
    const int max_size = 1000000;
    int* cash;


    void reset_cash() {
        for (int i = 0; i < max_size; i++) {
            cash[i] = -1;
        }
    }
public:
    Four() {
        cash = new int[max_size];
        for (int i = 0; i < max_size; i++) {
            cash[i] = -1;
        }
    }
    int one(int x) {
        if (x == 0)return 0;
        if (x == 1)return 1;
        else return one(x - 1) + one(x - 2);
    }
    int two(int x) {
        if (cash[x] == -1) {
            cash[x] = two(x - 1) + two(x - 2);
        }
        return cash[x];
    }
    int three(int x) {
        int* fib = new int[max_size];
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i < x + 1; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib[x];
    }
    int four(int x) {
        int f0 = 0, f1 = 1,f2;
        for (int i = 2; i < x + 1; i++) {
            f2 = f0 + f1;
            f0 = f1;
            f1 = f2;
        }
        return f2;
    }
};

int main()
{
    Four* test = new Four();
    cout<<test->one(50);
}
