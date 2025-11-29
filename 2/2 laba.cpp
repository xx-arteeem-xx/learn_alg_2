
#include <iostream>
#include <string>

using namespace std;

class search {
private:
    int* my_array;
    int n;
    const int max_size = 100;
public:
    search() {
        my_array = new int[max_size];
        my_array[0] = 1;
        for (int i = 1; i < max_size; i++) {
            int x = rand() % 5;
            my_array[i] = my_array[i - 1] + x+1;
        }
    }
    void find(int x) {
        int diffic = 0;
        for (int i = 0; i < max_size; i++) {
            diffic++;
            if (x == my_array[i]) {
                cout << "Сложность: " << diffic<<endl;
                return;
            }
        }
        cout << "Элемент не найден"<<endl;
    }

};

class search_double {
private:
    int* my_array;
    int n;
    const int max_size = 100;
public:
    search_double() {
        my_array = new int[max_size];
        my_array[0] = 1;
        for (int i = 1; i < max_size; i++) {
            int x = rand() % 5;
            my_array[i] = my_array[i-1]+x;
        }
    }
    void find(int x) {
        int diffic = 0;
        int left = 0;
        int right = max_size - 1;

        while (left<=right) {
            int pos = (left + right) / 2;
            diffic++;
            if (x == my_array[pos]) {
                cout << "Сложность: " << diffic << endl;
                return;
            }
            diffic++;
            if (x > my_array[pos]) {
                left = pos+1;
            }
            else {
                right = pos-1;
            }
        }
        cout << "Элемент не найден" << endl;
    }
};

class three {
private:
    int* my_array;
    int k,last_x;
    const int max_size = 520;
public:
    three() {
        my_array = new int[max_size];
        my_array[0] = 1;
        int x;
        for (int i = 1; i < 20; i++) {
            x = my_array[i - 1]+ rand() % 5+1;
            my_array[i] =  x;
        }
        last_x = x;
        k = 20;
    }
    void generate() {
        int x;
        if (k < max_size) {
            for (int i = 0; i < 20; i++) {
                x = last_x + rand() % 5 + 1;
                my_array[k] = x;
                k++;
                last_x = x;
            }
        }
        
    }
    void print() {
        for (int i = 0; i < k; i++) {
            cout << my_array[i] << " ";
        }
        cout << endl;
    }
    void twist_search() {
        while (k <= 500) {
            int diffic_one = 0,diffic_two = 0;
            int x = my_array[rand() % k];
            cout << "Искомое число: " << x << endl<<"Количество чисел всего: "<<k<<endl;
            for (int i = 0; i < k; i++) {
                diffic_one++;
                if (x == my_array[i]) {
                    cout << "Последовательный поиск - сложность: " << diffic_one << endl;
                    break;
                }
            }
            int left = 0;
            int right = k - 1;

            while (left <= right) {
                int pos = (left + right) / 2;
                diffic_two++;
                if (x == my_array[pos]) {
                    cout << "Двоичный поиск - сложность: " << diffic_two << endl;
                    break;
                }
                diffic_two++;
                if (x > my_array[pos]) {
                    left = pos + 1;
                }
                else {
                    right = pos - 1;
                }
            }
            generate();
            cout << "-------------------------" << endl;
        }
        cout << "xz";
        return;
    }
};

class four {
private:
    int* my_array;
    const int max_size = 1000;
    int* copy_array;
public:
    four() {
        my_array = new int[max_size];
        copy_array = new int[max_size];
        int x;
        for (int i = 0; i < max_size; i++) {
            x = rand() % (max_size * 10);
            my_array[i] = x;
            copy_array[i] = x;
        }
    }
    int BubbleSort() {
        int n_match = 0;
        for (int i = 0; i < max_size-1; i++) {
            for (int j = 0; j < max_size - i-1; j++) {
                n_match++;
                if (my_array[j + 1]< my_array[j])
                {
                    int c = my_array[j + 1];
                    my_array[j + 1] = my_array[j];
                    my_array[j] = c;
                }
            }
        }
        return n_match;
    }
    int bin_search(int x) {
        int diffic = 0;
        int left = 0;
        int right = max_size - 1;

        while (left <= right) {
            int pos = (left + right) / 2;
            diffic++;
            if (x == my_array[pos]) {
                return diffic;
            }
            diffic++;
            if (x > my_array[pos]) {
                left = pos + 1;
            }
            else {
                right = pos - 1;
            }
        }
        cout << "Элемент не найден" << endl;
    }
    int pos_search(int x) {
        int diffic = 0;
        for (int i = 0; i < max_size; i++) {
            diffic++;
            if (x == copy_array[i]) {
                return diffic;
            }
        }
    }
    void findK() {
        int n_match_bin = 0, n_match_pos = 0,K = 0;
        n_match_bin = BubbleSort();

        while (n_match_bin > n_match_pos) {
            K++;
            int x = my_array[rand() % max_size];
            n_match_bin += bin_search(x);
            n_match_pos += pos_search(x);
        }
        cout << n_match_bin << " " << n_match_pos << endl;
        cout << "При массиве с заданной длинной " << max_size << " двоичный поиск становится эффективней за " << K << " прогонов" << endl;
    }
};

class five {
private:
    int* my_array;
    const int max_size = 1000;
    int* copy_array;
public:
    five() {
        my_array = new int[max_size];
        copy_array = new int[max_size];
        int x;
        for (int i = 0; i < max_size; i++) {
            x = rand() % (max_size * 10);
            my_array[i] = x;
            copy_array[i] = x;
        }
    }
    void swap(int i, int j) {
        int copy = my_array[i];
        my_array[i] = my_array[j];
        my_array[j] = copy;
    }
    int BubbleSort() {
        int n_match = 0;
        for (int i = 0; i < max_size - 1; i++) {
            for (int j = 0; j < max_size - i - 1; j++) {
                n_match++;
                if (my_array[j + 1] < my_array[j])
                {
                    int c = my_array[j + 1];
                    my_array[j + 1] = my_array[j];
                    my_array[j] = c;
                }
            }
        }
        return n_match;
    }
    int QuickSortImpl(int l, int r) {
        int n_match = 0;
        if (l < r) {
            int x = my_array[r];
            int less = l;
            for (int i = l; i < r; ++i) {
                n_match++;
                if (my_array[i]<= x) {
                    swap(i, less);
                    less++;
                }
            }
            swap(less, r);
            int q = less;
            n_match+=QuickSortImpl(l, q - 1);
            n_match+=QuickSortImpl(q + 1, r);
        }
        return n_match;
    }

    int QuickSort() {
        return QuickSortImpl(0, max_size - 1);
    }
    int bin_search(int x) {
        int diffic = 0;
        int left = 0;
        int right = max_size - 1;

        while (left <= right) {
            int pos = (left + right) / 2;
            diffic++;
            if (x == my_array[pos]) {
                return diffic;
            }
            diffic++;
            if (x > my_array[pos]) {
                left = pos + 1;
            }
            else {
                right = pos - 1;
            }
        }
        cout << "Элемент не найден" << endl;
    }
    int pos_search(int x) {
        int diffic = 0;
        for (int i = 0; i < max_size; i++) {
            diffic++;
            if (x == copy_array[i]) {
                return diffic;
            }
        }
    }
    void findK() {
        int n_match_bin = 0, n_match_pos = 0, K = 0;
        n_match_bin = QuickSort();
        while (n_match_bin > n_match_pos) {
            K++;
            int x = my_array[rand() % max_size];
            n_match_bin += bin_search(x);
            n_match_pos += pos_search(x);
        }
        cout << n_match_bin << " " << n_match_pos << endl;
        cout << "При массиве с заданной длинной " << max_size << " двоичный поиск становится эффективней за " << K << " прогонов" << endl;
    }
};



int main()
{
    setlocale(LC_ALL, "ru");
    five* test = new five();
    test->findK();
    return 0;
}
