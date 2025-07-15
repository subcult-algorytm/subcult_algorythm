#include <iostream>

using namespace std;

// ����ü ����
struct Node
{
	char left;
	char right;
};

// A~Z������ ��带 ���� �� �迭
Node tree[26];

// ���� ��ȸ �Լ� (��Ʈ -> ���� �ڽ� -> ������ �ڽ�)
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

// ���� ��ȸ �Լ� (�����ڽ� -> ��Ʈ -> ������ �ڽ�)
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


// ���� ��ȸ �Լ� (���� �ڽ� -> ������ �ڽ� -> ��Ʈ)
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

	// ��� ���
	// A�� �׻� Ʈ���� �������̹Ƿ� A�� ���ڷ� �־��ش�.

	preorder('A');
	cout << "\n";

	inorder('A');
	cout << "\n";

	postorder('A');
	cout << "\n";

	return 0;
}
