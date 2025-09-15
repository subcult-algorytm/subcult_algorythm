from collections import deque
from typing import List, Tuple, Deque

# ✅ 입력_받기
def 입력_받기() -> Tuple[int, int]:
    열_칸_수, 행_칸_수 = map(int, input().split())
    return 열_칸_수, 행_칸_수

# ✅ 상자_만들기
def 상자_만들기(행_칸_수: int) -> List[List[int]]:
    상자: List[List[int]] = []
    for _ in range(행_칸_수):
        행: List[int] = list(map(int, input().split()))
        상자.append(행)
    return 상자

# ✅ 탐색_준비하기
def 탐색_준비하기(
    열_칸_수: int, 
    행_칸_수: int, 
    상자: List[List[int]]
) -> Tuple[List[int], List[int], Deque[Tuple[int, int]]]:
    이동_행: List[int] = [-1, 1, 0, 0]
    이동_열: List[int] = [0, 0, -1, 1]
    큐: Deque[Tuple[int, int]] = deque()

    for 행_번호 in range(행_칸_수):
        for 열_번호 in range(열_칸_수):
            if 상자[행_번호][열_번호] == 1:
                큐.append((행_번호, 열_번호))

    return 이동_행, 이동_열, 큐

# ✅ 토마토_익히기
def 토마토_익히기(
    상자: List[List[int]],
    큐: Deque[Tuple[int, int]],
    이동_행: List[int],
    이동_열: List[int],
    열_칸_수: int,
    행_칸_수: int
) -> None:
    while 큐:
        현재_행, 현재_열 = 큐.popleft()
        for 방향 in range(4):
            다음_행 = 현재_행 + 이동_행[방향]
            다음_열 = 현재_열 + 이동_열[방향]
            if 0 <= 다음_행 < 행_칸_수 and 0 <= 다음_열 < 열_칸_수:
                if 상자[다음_행][다음_열] == 0:
                    상자[다음_행][다음_열] = 상자[현재_행][현재_열] + 1
                    큐.append((다음_행, 다음_열))


# ✅ 결과_확인하기
def 결과_확인하기(상자: List[List[int]]) -> None:
    최대_값: int = 0
    for 행 in 상자:
        for 칸 in 행:
            if 칸 == 0:
                print(-1)
                return
        최대_값 = max(최대_값, max(행))

    print(최대_값 - 1)

# ✅ 실행_시작
if __name__ == "__main__":
    열_칸_수, 행_칸_수 = 입력_받기()
    상자 = 상자_만들기(행_칸_수)
    이동_행, 이동_열, 큐 = 탐색_준비하기(열_칸_수, 행_칸_수, 상자)
    토마토_익히기(상자, 큐, 이동_행, 이동_열, 열_칸_수, 행_칸_수)
    결과_확인하기(상자)
