#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

// Глобальный счетчик сравнений
int comps = 0;

// 1. Последовательный поиск с подсчетом сравнений
int sequentialSearch(const vector<int>& arr, int target) {
    comps = 0;
    for (int i = 0; i < arr.size(); i++) {
        comps++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 2. Двоичный поиск с подсчетом сравнений
int binarySearch(const vector<int>& arr, int target) {
    comps = 0;
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comps++;
        if (arr[mid] == target) {
            return mid;
        }
        comps++;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 3. Зависимость сложности от размера массива
void complexityExperiment() {
    cout << "| Размер массива | Последовательный поиск | Двоичный поиск |" << endl;
    cout << "|----------------|------------------------|----------------|" << endl;
    
    random_device rd;
    mt19937 gen(rd());
    
    for (int size = 20; size <= 500; size += 20) {
        vector<int> arr(size);
        iota(arr.begin(), arr.end(), 1); // Заполняем упорядоченными значениями
        
        uniform_int_distribution<> dis(1, size);
        int target = dis(gen);
        
        // Тестируем последовательный поиск
        sequentialSearch(arr, target);
        int seqComps = comps;
        
        // Тестируем двоичный поиск
        binarySearch(arr, target);
        int binComps = comps;
        
        cout << "| " << size << " | " << seqComps << " | " << binComps << " |" << endl;
    }
}

// 4. Квадратичная сортировка (пузырьковая) с подсчетом сравнений
void bubbleSort(vector<int>& arr) {
    comps = 0;
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            comps++;
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// 5. Быстрая сортировка с подсчетом сравнений
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comps++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void quickSortWrapper(vector<int>& arr) {
    comps = 0;
    quickSort(arr, 0, arr.size()-1);
}

// Дополнительное задание 1: Определение порога для квадратичной сортировки
void thresholdQuadratic() {
    int N = 1000;
    vector<int> arr(N);
    iota(arr.begin(), arr.end(), 1);
    shuffle(arr.begin(), arr.end(), mt19937{random_device{}()});
    
    vector<int> arrCopy = arr;
    bubbleSort(arrCopy);
    int sortComps = comps;
    
    int k = 1;
    while (true) {
        int sequentialTotal = 0;
        int binaryTotal = sortComps;
        
        // K последовательных поисков
        for (int i = 0; i < k; i++) {
            sequentialSearch(arr, i+1);
            sequentialTotal += comps;
        }
        
        // K двоичных поисков
        for (int i = 0; i < k; i++) {
            binarySearch(arrCopy, i+1);
            binaryTotal += comps;
        }
        
        if (binaryTotal < sequentialTotal) {
            cout << "Порог K для квадратичной сортировки: " << k << endl;
            break;
        }
        k++;
    }
}

// Дополнительное задание 2: Определение порога для быстрой сортировки
void thresholdQuick() {
    int N = 1000;
    vector<int> arr(N);
    iota(arr.begin(), arr.end(), 1);
    shuffle(arr.begin(), arr.end(), mt19937{random_device{}()});
    
    vector<int> arrCopy = arr;
    quickSortWrapper(arrCopy);
    int sortComps = comps;
    
    int k = 1;
    while (true) {
        int sequentialTotal = 0;
        int binaryTotal = sortComps;
        
        for (int i = 0; i < k; i++) {
            sequentialSearch(arr, i+1);
            sequentialTotal += comps;
        }
        
        for (int i = 0; i < k; i++) {
            binarySearch(arrCopy, i+1);
            binaryTotal += comps;
        }
        
        if (binaryTotal < sequentialTotal) {
            cout << "Порог K для быстрой сортировки: " << k << endl;
            break;
        }
        k++;
    }
}

int main() {
    // Основные задания
    complexityExperiment();
    
    // Дополнительные задания
    thresholdQuadratic();
    thresholdQuick();
    
    return 0;
}