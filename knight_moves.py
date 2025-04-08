from collections import deque
from typing import List, Tuple, Deque

# ✅ 입력_받기
def 입력_받기() -> Tuple[int, int, int, int, int, int]:
    테스트_케이스_수 = int(input())
    체스판_크기 = int(input())
    시작_x, 시작_y = map(int, input().split())
    목표_x, 목표_y = map(int, input().split())
    return 테스트_케이스_수, 체스판_크기, 시작_x, 시작_y, 목표_x, 목표_y

# ✅ 체스판_초기화
def 체스판_초기화(체스판_크기: int) -> Tuple[List[List[bool]], List[List[int]]]:
    # 방문 여부를 체크하는 배열
    방문_여부: List[List[bool]] = []
    for i in range(체스판_크기):
        행: List[bool] = []
        for j in range(체스판_크기):
            행.append(False)
        방문_여부.append(행)
    
    # 각 칸까지의 이동 횟수를 저장하는 배열
    이동_횟수: List[List[int]] = []
    for i in range(체스판_크기):
        행: List[int] = []
        for j in range(체스판_크기):
            행.append(0)
        이동_횟수.append(행)
    
    return 방문_여부, 이동_횟수

# ✅ 유효한_위치인가
def 유효한_위치인가(x: int, y: int, 체스판_크기: int) -> bool:
    return 0 <= x < 체스판_크기 and 0 <= y < 체스판_크기

# ✅ 나이트_이동_계산
def 나이트_이동_계산(시작_x: int, 시작_y: int, 체스판_크기: int) -> List[List[int]]:
    # 나이트가 이동할 수 있는 8가지 방향
    x_이동: List[int] = [-2, -1, 1, 2, 2, 1, -1, -2]
    y_이동: List[int] = [1, 2, 2, 1, -1, -2, -2, -1]
    
    # 체스판 초기화
    방문_여부, 이동_횟수 = 체스판_초기화(체스판_크기)
    
    # 시작 위치 방문 처리
    방문_여부[시작_x][시작_y] = True
    이동_횟수[시작_x][시작_y] = 0
    
    # BFS를 위한 큐 초기화
    큐: Deque[Tuple[int, int]] = deque([(시작_x, 시작_y)])
    
    while 큐:
        현재_x, 현재_y = 큐.popleft()
        
        # 8가지 방향으로 이동 시도
        for i in range(8):
            다음_x = 현재_x + x_이동[i]
            다음_y = 현재_y + y_이동[i]
            
            # 유효한 위치이고 아직 방문하지 않은 경우
            if 유효한_위치인가(다음_x, 다음_y, 체스판_크기) and not 방문_여부[다음_x][다음_y]:
                방문_여부[다음_x][다음_y] = True
                이동_횟수[다음_x][다음_y] = 이동_횟수[현재_x][현재_y] + 1
                큐.append((다음_x, 다음_y))
    
    return 이동_횟수

# ✅ 결과_출력하기
def 결과_출력하기(이동_횟수: List[List[int]], 목표_x: int, 목표_y: int) -> None:
    print(이동_횟수[목표_x][목표_y])

# ✅ 실행_시작
if __name__ == "__main__":
    테스트_케이스_수, 체스판_크기, 시작_x, 시작_y, 목표_x, 목표_y = 입력_받기()
    이동_횟수 = 나이트_이동_계산(시작_x, 시작_y, 체스판_크기)
    결과_출력하기(이동_횟수, 목표_x, 목표_y) 