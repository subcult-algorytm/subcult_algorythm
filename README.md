# 알고리즘 스터디 Repository

이 Repository는 알고리즘 문제 풀이 및 분석 내용을 공유하기 위한 공간입니다. 각 팀원은 자신의 풀이와 분석 내용을 독립적으로 작성하여, Git을 통한 협업과 Obsidian의 강력한 연결 기능을 최대한 활용할 수 있습니다.

---
## 1.  파일 Commit 규칙

- **커밋 메시지**
    - 간결하게, 변경 사항을 명확하게 기록합니다.
    - 예시: `시온: 문제001 정렬 알고리즘 분석 추가`
        
- **파일 구조 준수**
    - 각 문제는 `문제풀이` 폴더 아래에 문제 번호와 제목이 포함된 폴더에 작성합니다.
    - 예시 구조:
```
subcult_algorythm
  ├── 문제001_정렬_알고리즘
  │     ├── 람지
  │     │    ├── 람지_코드.py
  │     │    └── 람지_풀이.md
  │     ├── 시온
  │     │    ├── 시온_코드.cpp
  │     │    └── 시온_풀이.md
  ...
```
- **작업 시 주의 사항**
	- 한 파일에 두 명 이상의 팀원이 동시에 작업하는 경우는 피합니다.
	- 작업 전 최신 버전을 pull 받아 충돌이 없도록 주의합니다.

## 2.  Plugin 설치 요청

팀원들이 동일한 환경에서 작업할 수 있도록, 아래 필수 플러그인들을 설치해주시기 바랍니다.
- **Obsidian Git**
    - Git과의 동기화를 위해 반드시 설치해 주세요.
- **Excalidraw**
    - 다이어그램 및 시각적 설명 작성을 위해 필요합니다.
- 그 외, 스터디 진행에 유용한 플러그인 목록은 별도로 공지하겠습니다.
    

> **참고:**  
> 이 Repository는 `.obsidian` 디렉토리를 Git에 포함하지 않으므로, 각 팀원은 개별적으로 Obsidian 설정을 관리해야 합니다. 플러그인 설치 및 설정 방법은 팀 내 가이드 문서를 참고해 주세요.

--- 

# 알고리즘 스터디 로그

<table align="center">
<thead>
<tr>
<th style="text-align:center;">주차</th>
<th style="text-align:center;">기간</th>
<th>핵심 주제</th>
<th>주요 활동 / 문제</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align:center;"><strong>기초 자료구조 1주차</strong></td>
<td style="text-align:center;"><code>25.02.19 ~ 02.25</code></td>
<td>기초 자료구조: 배열</td>
<td>-</td>
</tr>
<tr>
<td style="text-align:center;"><strong>기초 자료구조 2주차</strong></td>
<td style="text-align:center;"><code>25.02.26 ~ 03.04</code></td>
<td>기초 자료구조: 리스트</td>
<td>-</td>
</tr>
<tr>
<td style="text-align:center;"><strong>기초 자료구조 3주차</strong></td>
<td style="text-align:center;"><code>25.03.05 ~ 03.11</code></td>
<td>기초 자료구조: 스택/큐/덱</td>
<td>-</td>
</tr>
<tr>
<td style="text-align:center;"><strong>기초 자료구조 4주차</strong></td>
<td style="text-align:center;"><code>25.03.12 ~ 03.18</code></td>
<td>-</td>
<td><strong>- 1주 휴강 -</strong></td>
</tr>
<tr>
<td style="text-align:center;"><strong>기초 자료구조 5주차</strong></td>
<td style="text-align:center;"><code>25.03.19 ~ 03.25</code></td>
<td>기초 자료구조: 트리/힙/그래프</td>
<td>-</td>
</tr>
<tr>
<td colspan="4" style="text-align:center; padding: 10px; background-color: #f6f8fa;"> <strong>--- 문제 풀이 ---</strong> </td>
</tr>
<tr>
<td style="text-align:center;"><strong>6주차</strong></td>
<td style="text-align:center;"><code>25.03.26 ~ 04.01</code></td>
<td>그리디 (Greedy)</td>
<td><code>[BOJ] 27961 - 고양이는 많을수록 좋다</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>7주차</strong></td>
<td style="text-align:center;"><code>25.04.02 ~ 04.08</code></td>
<td>그래프 탐색 (BFS, DFS)</td>
<td><code>[BOJ] 7576 - 토마토</code><br><code>[BOJ] 7562 - 나이트의 이동</code><br><code>[BOJ] 2606 - 바이러스</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>8주차</strong></td>
<td style="text-align:center;"><code>25.04.09 ~ 04.15</code></td>
<td>다이나믹 프로그래밍 (DP)</td>
<td><code>[BOJ] 1463 - 1로 만들기</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>9주차</strong></td>
<td style="text-align:center;"><code>25.04.16 ~ 04.22</code></td>
<td>-</td>
<td><strong>- 1주 휴강 -</strong></td>
</tr>
<tr>
<td style="text-align:center;"><strong>수학 특집</strong></td>
<td style="text-align:center;"><code>25.04.24</code></td>
<td>수학 특집</td>
<td>• CCW (Counter-Clockwise)<br>• 벡터의 외적</td>
</tr>
<tr>
<td style="text-align:center;"><strong>10주차</strong></td>
<td style="text-align:center;"><code>25.04.23 ~ 04.29</code></td>
<td>특별 문제</td>
<td>명조 퍼즐</td>
</tr>
<tr>
<td style="text-align:center;"><strong>11주차</strong></td>
<td style="text-align:center;"><code>25.04.30 ~ 05.06</code></td>
<td>-</td>
<td><strong>- 1주 휴강 -</strong></td>
</tr>
<tr>
<td style="text-align:center;"><strong>12주차</strong></td>
<td style="text-align:center;"><code>25.05.07 ~ 05.13</code></td>
<td>투 포인터 / 슬라이딩 윈도우 / 누적합</td>
<td><code>[BOJ] 21921 - 블로그</code><br><code>[BOJ] 1806 - 부분합</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>13주차</strong></td>
<td style="text-align:center;"><code>25.05.14 ~ 05.20</code></td>
<td>다익스트라 (Dijkstra)</td>
<td><code>[BOJ] 1753 - 최단경로</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>14주차</strong></td>
<td style="text-align:center;"><code>25.05.21 ~ 05.27</code></td>
<td>위상 정렬 (Topology sort)</td>
<td><code>[BOJ] 2252 - 줄 세우기</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>15주차</strong></td>
<td style="text-align:center;"><code>25.05.28 ~ 06.03</code></td>
<td>Union-Find (DSU)</td>
<td><code>[BOJ] 1043 - 거짓말</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>16주차</strong></td>
<td style="text-align:center;"><code>25.06.04 ~ 06.10</code></td>
<td>-</td>
<td><strong>- 1주 휴강 -</strong></td>
</tr>
<tr>
<td style="text-align:center;"><strong>17주차</strong></td>
<td style="text-align:center;"><code>25.06.11 ~ 06.17</code></td>
<td>최소 스패닝 트리 (MST)</td>
<td><code>[BOJ] 1197 - 최소 스패닝 트리</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>18-19주차</strong></td>
<td style="text-align:center;"><code>25.06.18 ~ 07.01</code></td>
<td>최소 공통 조상 (LCA)</td>
<td><code>[BOJ] 11437 - LCA</code></td>
</tr>
<tr>
<td style="text-align:center;"><strong>20-21주차</strong></td>
<td style="text-align:center;"><code>25.07.02 ~ 07.15</code></td>
<td>LCA / 트리 순회 (Tree traversal)</td>
<td><code>[BOJ] 11438 - LCA 2</code><br><code>[BOJ] 2263 - 트리의 순회</code></td>
</tr>
</tbody>
</table>