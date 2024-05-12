import time

def factorial(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

def main():
    start_time = time.time()
    result = factorial(5)
    end_time = time.time()
    execution_time = end_time - start_time
    print("Factorial:", result)
    print("Execution Time:", execution_time, "seconds")

main()