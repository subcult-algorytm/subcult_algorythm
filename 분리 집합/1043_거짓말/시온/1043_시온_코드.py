"""
백준 1043번: 거짓말
문제 링크: https://www.acmicpc.net/problem/1043

[문제 설명]
지민이는 파티에 가서 이야기를 하는 것을 좋아한다. 파티에 갈 때마다, 지민이는 지민이가 가장 좋아하는 
이야기를 한다. 지민이는 그 이야기를 말할 때, 있는 그대로 진실로 말하거나 엄청나게 과장해서 말한다. 
당연히 과장해서 이야기하는 것이 훨씬 더 재미있기 때문에, 되도록이면 과장해서 이야기하려고 한다. 
하지만, 지민이는 거짓말쟁이로 알려지기는 싫어한다. 문제는 몇몇 사람들은 그 이야기의 진실을 안다는 것이다. 
따라서 이런 사람들이 파티에 왔을 때는, 지민이는 진실을 이야기할 수 밖에 없다. 
당연히, 어떤 사람이 어떤 파티에서는 진실을 듣고, 또다른 파티에서는 과장된 이야기를 들었을 때도 
지민이는 거짓말쟁이로 알려지게 된다. 지민이는 이런 일을 모두 피해야 한다.

사람의 수 N이 주어진다. 그리고 그 이야기의 진실을 아는 사람이 주어진다. 
그리고 각 파티에 오는 사람들의 번호가 주어진다. 지민이는 모든 파티에 참가해야 한다. 
이때, 지민이가 거짓말쟁이로 알려지지 않으면서, 과장된 이야기를 할 수 있는 파티 개수의 최댓값을 구하는 프로그램을 작성하시오.

[입력]
- 첫째 줄: 사람의 수 N과 파티의 수 M (1 ≤ N, M ≤ 50)
- 둘째 줄: 이야기의 진실을 아는 사람의 수와 번호
- 셋째 줄부터 M개의 줄: 각 파티마다 오는 사람의 수와 번호

[출력]
- 지민이가 거짓말쟁이로 알려지지 않으면서, 과장된 이야기를 할 수 있는 파티 개수의 최댓값

[알고리즘 접근법]
이 문제는 Union-Find(Disjoint Set) 자료구조를 활용하는 문제입니다.

핵심 아이디어:
1. 같은 파티에 참석한 사람들은 모두 같은 정보를 공유하게 됩니다.
2. 진실을 아는 사람과 같은 파티에 참석한 사람도 진실을 알게 됩니다.
3. 한 번 진실을 알게 된 사람은 다른 파티에서도 진실을 알고 있습니다.

해결 과정:
1. Union-Find 자료구조를 초기화합니다.
2. 각 파티에 참석한 사람들을 하나의 그룹으로 union 합니다.
3. 진실을 아는 사람들과 연결된 모든 사람들을 찾습니다.
4. 각 파티를 검사하여, 진실을 아는 사람이 한 명도 없는 파티의 개수를 셉니다.

시간 복잡도: O(M × P × α(N))
- M: 파티의 수
- P: 각 파티의 평균 참석자 수
- α(N): 애커만 함수의 역함수 (거의 상수)

공간 복잡도: O(N)
- Union-Find를 위한 parent 배열
"""

from typing import List, Set


class UnionFind:
    """Union-Find 자료구조 구현"""
    
    def __init__(self, size: int):
        """
        Union-Find 초기화
        Args:
            size: 전체 원소의 개수 (0부터 size-1까지)
        """
        # 각 원소의 부모를 저장 (처음엔 자기 자신이 부모)
        self.parent = list(range(size))
        # 트리의 높이를 저장 (Union by Rank 최적화용)
        self.rank = [0] * size
    
    def find(self, x: int) -> int:
        """
        x가 속한 그룹의 대표(루트) 찾기
        경로 압축 최적화 적용
        """
        if self.parent[x] != x:
            # 재귀적으로 루트를 찾고, 경로 압축
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x: int, y: int) -> None:
        """
        x와 y가 속한 그룹을 하나로 합치기
        Union by Rank 최적화 적용
        """
        root_x = self.find(x)
        root_y = self.find(y)
        
        # 이미 같은 그룹이면 아무것도 하지 않음
        if root_x == root_y:
            return
        
        # 높이가 낮은 트리를 높은 트리에 연결
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            # 높이가 같으면 한쪽을 다른 쪽에 연결하고 높이 증가
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
    
    def is_same_group(self, x: int, y: int) -> bool:
        """x와 y가 같은 그룹에 속하는지 확인"""
        return self.find(x) == self.find(y)


def solve() -> int:
    """백준 1043번 거짓말 문제 해결"""
    # 입력 받기
    n, m = map(int, input().split())
    
    # Union-Find 초기화 (사람 번호가 1부터 시작하므로 n+1 크기)
    uf = UnionFind(n + 1)
    
    # 진실을 아는 사람들 입력
    truth_info = list(map(int, input().split()))
    truth_count = truth_info[0]
    truth_people = truth_info[1:] if truth_count > 0 else []
    
    # 각 파티 정보 저장
    parties: List[List[int]] = []
    
    for _ in range(m):
        party_info = list(map(int, input().split()))
        party_size = party_info[0]
        party_people = party_info[1:]
        parties.append(party_people)
        
        # 같은 파티에 참석한 사람들을 하나의 그룹으로 연결
        for i in range(1, party_size):
            uf.union(party_people[0], party_people[i])
    
    # 진실을 아는 사람들과 같은 그룹에 속한 모든 사람 찾기
    truth_groups: Set[int] = set()
    for person in truth_people:
        truth_groups.add(uf.find(person))
    
    # 거짓말 가능한 파티 수 계산
    lie_count = 0
    
    for party in parties:
        can_lie = True
        
        # 파티에 진실을 아는 그룹의 사람이 있는지 확인
        for person in party:
            if uf.find(person) in truth_groups:
                can_lie = False
                break
        
        if can_lie:
            lie_count += 1
    
    return lie_count


# 메인 실행부
if __name__ == "__main__":
    print(solve())


"""
[예제 입력 1]
4 3
0
2 1 2
1 3
3 2 3 4

[예제 출력 1]
3

[예제 설명]
- 진실을 아는 사람이 없으므로 모든 파티에서 거짓말 가능

[예제 입력 2]
4 5
1 1
1 1
1 2
1 3
1 4
2 4 1

[예제 출력 2]
2

[예제 설명]
- 1번이 진실을 알고 있음
- 파티1: 1번 참석 → 진실
- 파티2: 2번만 참석 → 거짓말 가능
- 파티3: 3번만 참석 → 거짓말 가능
- 파티4: 4번만 참석 → 거짓말 가능
- 파티5: 4번, 1번 참석 → 진실 (1번이 진실을 앎)
- 하지만 파티5에서 4번도 진실을 듣게 되므로, 파티4도 진실을 말해야 함
- 최종적으로 파티2, 파티3에서만 거짓말 가능
"""
