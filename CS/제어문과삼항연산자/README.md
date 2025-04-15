# 삼항연산자와 if-else문 속도 비교

## 테스트 코드

```cpp
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
    std::cout << "Ternary: " << duration1.count() << "μs\n";
    std::cout << "If-Else: " << duration2.count() << "μs\n";

    return 0;
}
```

위 코드는 1번 실행할때 마다 a 변수에 각각 다른 변수(b,c)를 대입하는 코드이고 최적화를 하지 못하게 하기 위하여
강제로 메모리에 쓰게 만들기 위해 `volatile` 키워드를 삽입한 변수를 사용한 코드를 삽입했습니다..

| 컴파일 옵션     | 삼항연산자 | if-else문 |
| --------------- | ---------- | --------- |
| 최적화없음(/Od) | 5,545,151μs  | 4,712,050μs |
| 많은최적화(/O2) | 5,527,017μs  | 4,716,471μs |

실험 결과 삼항 연산자가 제어문보다 속도가 더 느리게 나왔습니다.

## 어셈블리 코드

위 코드의 삼항연산자와 제어문의 디어셈블리 코드는 다음과 같습니다.

제어문 :

```asm
mov rax, qword ptr [rsp+58h]
cqo
and rax,1
xor rax,rdx
sub rax,rdx
test rax,rax

je main+0ADh
mov eax,dword ptr [b1]
mov dword ptr [a1], eax

jmp main+0B5h
mov eax,dword ptr [c2]
mov dword ptr [a1],eax

mov eax,dword ptr [a1]
mov dword ptr [x], eax
```

삼항 연산자 :

```asm
mov rax,qword ptr[rsp+98h]
cqo
and rax,1
xor rax,rdx
sub rax,rdx
test rax,rax

je main+134h
mov eax,dword ptr [b2]
mov dword ptr [rsp+108h],eax

jmp main+13Fh
mov eax,dword ptr [c2]
mov dword ptr [rsp+108h],eax

mov eax,dword ptr [rsp+108h]
mov dword ptr [a2], eax

mov eax,dword ptr [a2]
mov dword ptr [x],eax
```

## 이유 분석

일단 위의 코드는 조건이 0과 1을 규칙적으로 반복하는 매우 예측 가능한 패턴입니다.

따라서 CPU의 분기 예측은 100% 정확도로 예측합니다.

예측을 성공하면 파이프라인이 완전히 활용되며 분기 예측의 jmp 명령어가 실제로 실행되지 않고 추측 실행만으로 처리됩니다.

또 어셈블리 코드를 보았을때 제어문은 메모리에 있는 각각의 변수들을 레지스터 1번만 거치고 a변수에 저장하지만
삼항연산자는 메모리에서 레지스터를 거친후 다시 메모리에 저장하고 그걸 다시 레지스터로 불러들였다가 메모리에 저장하는
코드를 가지고 있어 속도가 훨씬 느려지게 됩니다.

추가적으로 이 어셈블리 코드에서는 나오지 않았지만 삼항연산자는 데이터 의존성이 생길 수 있습니다.

삼항연산자는 조건 평가, 값 선택(cmov 명령어), 결과 저장 단계로 이루어지는데 값 선택 단계는 조건 평가 단계 이후에만 진행될 수 있기에
삼항연산자의 결과를 사용하는 다음 명령어는 연산이 끝난뒤에만 진행될 수 있게 됩니다.

## O2옵션이 더 느린 이유

위 실험에서는 최적화를 하지 않는 /Od옵션이 /O2옵션보다 더 빠르게 실행되었습니다.

이 이유에는 여러 복합적인 것이 섞여있을것이기에 확신하기는 어렵지만 아마 최적화를 하며 분기 예측 패턴을 파괴같은 이유로 거나
컴퓨터의 다른 프로세스가 파이프라인에 섞여들어갔기 때문으로 추측됩니다.

## 결론

삼항 연산자는 분기 미스 예측을 제거하지만, 모든 실행에서 조건 평가 완료를 강제하여 오히려 성능 저하를 초래할 수 있습니다.

최적화 시에는 분기 패턴의 예측 가능성과 데이터 의존성 비용을 종합적으로 평가해야합니다.
