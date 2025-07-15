#include <iostream>

using namespace std;

// 구조체 정의
struct Node
{
	char left;
	char right;
};

// A~Z까지의 노드를 저장 할 배열
Node tree[26];

// 전위 순회 함수 (루트 -> 왼쪽 자식 -> 오른쪽 자식)
void preorder(char root)
{
	if (root == '.')
	{
		return;
	}
	cout << root;
	preorder(tree[root - 'A'].left);
	preorder(tree[root - 'A'].right); 
}

// 중위 순회 함수 (왼쪽자식 -> 루트 -> 오른쪽 자식)
void inorder(char root)
{
	if (root == '.')
	{
		return;
	}
	inorder(tree[root - 'A'].left); 
	cout << root;
	inorder(tree[root - 'A'].right); 
}


// 후위 순회 함수 (왼쪽 자식 -> 오른쪽 자식 -> 루트)
void postorder(char root)
{
	if (root == '.')
	{
		return;
	}
	postorder(tree[root - 'A'].left); 
	postorder(tree[root - 'A'].right); 
	cout << root;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		char p, l, r;
		cin >> p >> l >> r; 
		tree[p - 'A'].left = l;
		tree[p - 'A'].right = r;
	}

	// 결과 출력
	// A가 항상 트리의 시작점이므로 A를 인자로 넣어준다.

	preorder('A');
	cout << "\n";

	inorder('A');
	cout << "\n";

	postorder('A');
	cout << "\n";

	return 0;
}
