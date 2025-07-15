// 전위순회 복구 문제
// - post order는 LRV로 root가 가장 마지막에 온다
// - in order는 LVR로 root를 기준으로 왼쪽/오른쪽 서브 트리가 나뉜다

// 1. postorder[ed]가 root -> 출력
// 2. inorder에서 root의 위치를 찾기 -> 루트 기준으로 나뉘는 서브 트리가 나온다
// 3. 위에서 나온 root의 위치를 기준으로 서브트리에 접근 가능

// 왼쪽 서브트리부터 오른쪽으로 재귀를 돌리면 가장 앞 노드부터 순서데로 나오므로, 재귀로 풀이 가능

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> inorder;
vector<int> postorder;
vector<int> in_idx; // O(1) 접근을 위한 임시 벡터(배열)

// 재귀 풀이
void getPreorder(int in_st, int in_ed, int post_st, int post_ed) 
{
    if (in_st > in_ed || post_st > post_ed) return; // base case

    // 1. 전체 트리의 root 구하기
    int root = postorder[post_ed]; 
    cout << root << " ";

    // 2. 하위 서브트리의 root와 크기 구하기
    int root_idx = in_idx[root];
    int left_size = root_idx - in_st;

    getPreorder(in_st, root_idx - 1, post_st, post_st + left_size - 1); // 왼쪽 서브트리
    getPreorder(root_idx + 1, in_ed, post_st + left_size, post_ed - 1); // 오른쪽 서브트리

    
    // inorder { st : root-1 }
    // postorder { st : st + left_size-1 }
    // inorder { root+1 : ed }
    // postorder { left_size : ed-1 }
}

int main() 
{
    cin >> n;
    inorder.resize(n);
    postorder.resize(n);
    in_idx.resize(n + 1); // 1-index

    // inorder & in_idx
    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
        in_idx[inorder[i]] = i; // inorder의 노드번호마다 인덱스를 달아줍니다
    }

    // postorder
    for (int i = 0; i < n; i++) 
        cin >> postorder[i];
    
    getPreorder(0, n - 1, 0, n - 1);
    cout << '\n';

    return 0;
}