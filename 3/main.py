import time
import math
import random
from tabulate import tabulate

# ===== Функции для проверки простоты числа =====
def isPrimeBasic(n):
    """Базовый перебор от 2 до N-1"""
    if n < 2:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

def isPrimeSqrt(n):
    """Перебор от 2 до sqrt(N)"""
    if n < 2:
        return False
    if n == 2:
        return True
    limit = int(math.sqrt(n)) + 1
    for i in range(2, limit):
        if n % i == 0:
            return False
    return True

def isPrimeOdd(n):
    """Перебор только нечетных чисел (кроме 2)"""
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, n, 2):
        if n % i == 0:
            return False
    return True

def isPrimeSqrtOdd(n):
    """Перебор от 2 до sqrt(N) только нечетных"""
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    limit = int(math.sqrt(n)) + 1
    for i in range(3, limit, 2):
        if n % i == 0:
            return False
    return True

# ===== Функции для вычисления НОД =====
def gcd_list(m, n):
    """Формирование массива общих делителей"""
    divisors = []
    min_val = min(m, n)
    for i in range(1, min_val + 1):
        if m % i == 0 and n % i == 0:
            divisors.append(i)
    return max(divisors) if divisors else 1

def gcd_brute_force_min(m, n):
    """Перебор от 1 до min(M, N)"""
    min_val = min(m, n)
    nod = 1
    for i in range(1, min_val + 1):
        if m % i == 0 and n % i == 0:
            nod = i
    return nod

def gcd_brute_force_max(m, n):
    """Перебор от min(M, N) до 1"""
    min_val = min(m, n)
    for i in range(min_val, 0, -1):
        if m % i == 0 and n % i == 0:
            return i
    return 1

def gcd_euclid(m, n):
    """Алгоритм Евклида"""
    while n != 0:
        m, n = n, m % n
    return m

# ===== Функции для вычисления НОК =====
def lcm_list(m, n):
    """Формирование массива общих кратных"""
    max_val = max(m, n)
    min_val = min(m, n)
    multiples = []
    for i in range(max_val, m * n + 1):
        if i % m == 0 and i % n == 0:
            multiples.append(i)
    return min(multiples) if multiples else m * n

def lcm_brute_force(m, n):
    """Перебор от max(M, N) до M*N"""
    max_val = max(m, n)
    for i in range(max_val, m * n + 1):
        if i % m == 0 and i % n == 0:
            return i
    return m * n

def lcm_euclid(m, n):
    """Через алгоритм Евклида"""
    return m * n // gcd_euclid(m, n)

# ===== Функции для экспериментов =====
def measure_time(func, *args, trials=10):
    """Измерение среднего времени выполнения функции"""
    total_time = 0
    for _ in range(trials):
        start_time = time.perf_counter()
        func(*args)
        end_time = time.perf_counter()
        total_time += (end_time - start_time)
    return total_time / trials

def generate_prime_candidate(digits):
    """Генерация кандидата в простые числа"""
    return random.randint(10**(digits-1), 10**digits - 1)

# ===== Проведение экспериментов =====
def run_prime_experiments():
    """Эксперименты с проверкой простоты"""
    print("=" * 60)
    print("ЭКСПЕРИМЕНТЫ С ПРОВЕРКОЙ ПРОСТОТЫ ЧИСЛА")
    print("=" * 60)
    
    algorithms = [
        ("Перебор от 2 до N", isPrimeBasic),
        ("Перебор от 2 до sqrt(N)", isPrimeSqrt),
        ("Перебор нечетных от 2 до N", isPrimeOdd),
        ("Перебор нечетных от 2 до sqrt(N)", isPrimeSqrtOdd)
    ]
    
    results = []
    digits_list = [3, 4, 5, 6]  # Количество цифр в числе
    
    for digits in digits_list:
        n = generate_prime_candidate(digits)
        row = [f"{digits} цифр ({n})"]
        
        for algo_name, algo_func in algorithms:
            time_taken = measure_time(algo_func, n, trials=5)
            row.append(f"{time_taken:.6f} с")
        
        results.append(row)
    
    headers = ["Число"] + [algo[0] for algo in algorithms]
    print(tabulate(results, headers=headers, tablefmt="grid"))
    print()

def run_gcd_experiments():
    """Эксперименты с вычислением НОД"""
    print("=" * 60)
    print("ЭКСПЕРИМЕНТЫ С ВЫЧИСЛЕНИЕМ НОД")
    print("=" * 60)
    
    algorithms = [
        ("Массив делителей", gcd_list),
        ("Перебор от 1 до min(M,N)", gcd_brute_force_min),
        ("Перебор от min(M,N) до 1", gcd_brute_force_max),
        ("Алгоритм Евклида", gcd_euclid)
    ]
    
    results = []
    test_cases = [
        (1000, 2500),
        (10000, 25000),
        (100000, 250000),
        (1000000, 2500000)
    ]
    
    for m, n in test_cases:
        row = [f"({m}, {n})"]
        
        for algo_name, algo_func in algorithms:
            time_taken = measure_time(algo_func, m, n, trials=10)
            row.append(f"{time_taken:.6f} с")
        
        results.append(row)
    
    headers = ["Числа (M, N)"] + [algo[0] for algo in algorithms]
    print(tabulate(results, headers=headers, tablefmt="grid"))
    print()

def run_lcm_experiments():
    """Эксперименты с вычислением НОК"""
    print("=" * 60)
    print("ЭКСПЕРИМЕНТЫ С ВЫЧИСЛЕНИЕМ НОК")
    print("=" * 60)
    
    algorithms = [
        ("Массив кратных", lcm_list),
        ("Перебор от max(M,N) до M*N", lcm_brute_force),
        ("Через алгоритм Евклида", lcm_euclid)
    ]
    
    results = []
    test_cases = [
        (100, 250),
        (1000, 2500),
        (10000, 25000),
        (100000, 250000)
    ]
    
    for m, n in test_cases:
        row = [f"({m}, {n})"]
        
        for algo_name, algo_func in algorithms:
            time_taken = measure_time(algo_func, m, n, trials=10)
            row.append(f"{time_taken:.6f} с")
        
        results.append(row)
    
    headers = ["Числа (M, N)"] + [algo[0] for algo in algorithms]
    print(tabulate(results, headers=headers, tablefmt="grid"))
    print()

def run_sorting_experiment():
    """Эксперимент со сложностью сортировки"""
    print("=" * 60)
    print("ЭКСПЕРИМЕНТ СО СЛОЖНОСТЬЮ СОРТИРОВКИ")
    print("=" * 60)
    
    results = []
    sizes = [1000, 5000, 10000, 50000, 100000]
    
    for size in sizes:
        arr = [random.randint(1, 1000000) for _ in range(size)]
        
        start_time = time.perf_counter()
        sorted_arr = sorted(arr)
        end_time = time.perf_counter()
        
        time_taken = end_time - start_time
        results.append([size, f"{time_taken:.6f} с"])
    
    headers = ["Размер массива", "Время сортировки"]
    print(tabulate(results, headers=headers, tablefmt="grid"))
    print()

# ===== Основная программа =====
if __name__ == "__main__":
    print("ПРАКТИЧЕСКОЕ ЗАДАНИЕ: ОПТИМИЗАЦИЯ ПОЛНОГО ПЕРЕБОРА")
    print()
    
    # Запуск всех экспериментов
    run_prime_experiments()
    run_gcd_experiments()
    run_lcm_experiments()
    run_sorting_experiment()
    
    print("ВЫВОДЫ:")
    print("1. Оптимизация перебора (сокращение до sqrt(N)) значительно ускоряет проверку простоты")
    print("2. Алгоритм Евклида намного эффективнее полного перебора для вычисления НОД")
    print("3. Вычисление НОК через НОД (алгоритм Евклида) - самый эффективный метод")
    print("4. Встроенная сортировка Python имеет сложность O(N log N), что подтверждается экспериментально")