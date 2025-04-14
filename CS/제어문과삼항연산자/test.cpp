#include <chrono>
#include <iostream>

volatile int x = 0; // 최적화 방지

int main()
{
    const long long N = 1e10;
    int a2 = 0, b2 = 1, c2 = 2;
    int a1 = 0, b1 = 1, c1 = 2;

    // if-else 테스트
    auto start2 = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; ++i)
    {
        if (i % 2)
        {
            a1 = b1;
        }
        else
        {
            a1 = c2;
        }
        x = a1;
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    // 삼항 연산자 테스트
    auto start1 = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < N; ++i)
    {
        a2 = (i % 2) ? b2 : c2;
        x = a2;
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // 결과 출력
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "Ternary: " << duration1.count() << "ms\n";
    std::cout << "If-Else: " << duration2.count() << "ms\n";

    return 0;
}