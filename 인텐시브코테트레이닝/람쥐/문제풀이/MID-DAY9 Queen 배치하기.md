
### 개요 
Queen이 서로 잡아 먹지 않게 체스에서 어떻게 배치하는가라는 전통적인 문제로, 이 문제를 통해 `백트레킹`의 개념을 배웁니다. 

`백트레킹`은 순회를 할때에 해가 될 가능성이 없는 해들을 탐색에서 제외하고, 가능성이 있는 경우의 수로 스킵해서 탐색하는 것을 의미합니다. 이 백트레킹을 사용하게 되면, 탐색시간이 매우 많이 줄게 되어, 시간복잡도 면에서 이득을 많이 볼 수 있습니다. 

시간복잡도에서 걸렸거나, 명확하게 이 케이스는 안된다고 판단이 될때, 백트레킹을 이용해서 탐색의 시간을 상당히 줄이면 테스트 케이스를 통과할수 있습니다. 


### 풀이 

대표적인 예시 문제가 N-퀸 문제입니다. N-퀸문제는 채스판에 N개 배치했을때 서로 공격할수없는 위치에 넣는 방법을 찾는 문제입니다. 

만약 이 문제를 완전 탐색을 이용해 풀게되면 이렇습니다. 

- 퀸을 n 위치에 배치해놓고, 다음 퀸을 배치하는 경우의 수를 배치된 퀸이 움직일수 없는 곳에 무작위 배치 합니다. 
- 그리고 배치한 뒤에, 다른 퀸을 잡힐수 없는 곳에 배치 해봅니다 
- 안된다면 폐기하고 첫 퀸을 다음 배치 할수 있는 곳에 배치합니다. 
- 이 것을 최적의 해를 구할 때 까지 반복합니다. 

```cpp 
//C++ program to find all solution of N queen problem 
//using recursion

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if the current placement is safe
bool isSafe(vector<int>& board, int currRow, int currCol) {

    // Check all previously placed queens
    for(int i = 0; i < board.size(); ++i) {
        int placedRow = board[i];

        // Columns are 1-based
        int placedCol = i + 1;

        // Check if the queen is on the same diagonal
        if(abs(placedRow - currRow) == abs(placedCol - currCol)) {
            return false; // Not safe
        }
    }

    // Safe to place the queen
    return true; 
}

// Recursive function to generate all possible permutations
void nQueenUtil(int col, int n, vector<int>& board, 
  	vector<vector<int>>& res, vector<bool>& visited) {

    // If all queens are placed, add into res
    if(col > n) {
        res.push_back(board);
        return;
    }

    // Try placing a queen in each row
    // of the current column
    for(int row = 1; row <= n; ++row) {

        // Check if the row is already used
        if(!visited[row]) {
            
            // Check if it's safe to place the queen
            if(isSafe(board, row, col)) {

                // Mark the row as used
                visited[row] = true; 

                // Place the queen
                board.push_back(row); 

                // Recur to place the next queen
                nQueenUtil(col + 1, n, board,
                             res, visited);

                // Backtrack: remove the queen
                board.pop_back(); 
                
                // Unmark row
                visited[row] = false; 
            }
        }
    }
}

// Main function to find all distinct 
// res to the n-queens puzzle
vector<vector<int>> nQueen(int n) {
    vector<vector<int>> res; 

    // Current board configuration
    vector<int> board; 

    // Track used rows
    vector<bool> visited(n + 1, false); 

    // Start solving from the first column
    nQueenUtil(1, n, board, res, visited);
    return res; 
}

int main() {
    int n = 4; 
    vector<vector<int>> res = nQueen(n); 

    for(int i = 0;i < res.size(); i++) {
        cout << "[";
        for(int j = 0; j < n; ++j) {
            cout << res[i][j]; 
            if(j != n - 1)   cout << " "; 
        }
        cout << "]\n";
    }
    return 0;
}
```

이럴 경우 시간복잡도는 **O(N^2)** 가 됩니다. 그리고 이런 경우 대칭인 경우 굳이 검색할 필요가 없음에도 검색하게 되니, 시간을 많이 낭비하게됩니다. 코테의 N-퀸 문제와, 관련 문제를 풀때에는 시간 복잡도에 걸릴 가능성이 높기 때문에, 이 순회를 절약 할 수 있는 로직이 필요합니다. 

### 백트레킹을 이용한 풀이 

https://leetcode.com/problems/n-queens/

백트레킹을 이용한다면 몇가지 예외처리를 파악해야합니다. 

퀸은 상하좌우 양 대각선으로 모두 움직일 수 있으므로, 같은 column 혹은  row에 놓을수 없습니다. 
즉, column 혹은 row 에 한개 씩만 배치 될 것이므로, column 마다 Queen을 하나씩 배치합니다. 


```cpp

    vector<string> makeBoard(const vector<int>& board, int n)

    {

        vector<string>grid(n, string(n, '.'));

        for (int col = 0; col <n ; col ++)

        {

            grid[board[col]][col] = 'Q';

        }

        return grid;

    }



```

그리고 `Backtracking` 함수를 작성해야합니다. 

```cpp 

 for (int row = 0; row <n ; row++)

        {

            if (!rows[row] && !diag[row+col] && !rdiag[row-col+n])

            {

                rows[row] = diag[row+col] = rdiag[row-col +n] = true;

                board.push_back(row);

                backtrack(col + 1, n , board, rows,diag, rdiag, res);

                board.pop_back();

                rows[row] = diag[row+col] = rdiag[row - col +n] = false;

            }

        }


```


```cpp

class Solution {

public:

    vector<vector<string>> solveNQueens(int n) {
		
		// 해당 배열들은 queen이 배치 되었을때 갈 수있는 모든 방향을 검색합니다. 
		
        vector<vector<string>> res;

        vector<int> board;

        vector<bool> rows(n, false);

        vector<bool> diag(2*n, false);

        vector<bool> Rdiag(2*n, false); // O(1) verification.

        backtrack(0, n, board, rows, diag, Rdiag, res); // back

        return res;

    }

  

private:

    void backtrack(int col, int n, vector<int>& board,

    vector<bool>& rows, vector<bool>&diag, vector<bool>&rdiag,

    vector<vector<string>>& res)

    {

        if (col == n)

        {

            res.push_back(makeBoard(board,n));

            return;

        }

        for (int row = 0; row <n ; row++)

        {

            if (!rows[row] && !diag[row+col] && !rdiag[row-col+n])

            {

                rows[row] = diag[row+col] = rdiag[row-col +n] = true;

                board.push_back(row);
  
                backtrack(col + 1, n , board, rows,diag, rdiag, res);

                board.pop_back();

                rows[row] = diag[row+col] = rdiag[row - col + n] = false;

            }

        }

    }  

  

    vector<string> makeBoard(const vector<int>& board, int n)

    {

        vector<string>grid(n, string(n, '.'));

        for (int col = 0; col <n ; col ++)

        {

            grid[board[col]][col] = 'Q';

        }

        return grid;

    }


};
 
```




### 비트 마스킹을 이용한 풀이 

비트마스킹을 이용해 풀이를 하면 다음과 같습니다.

```cpp 
class Solution {
public:
    bool isSafe(int row, int col, int rows, int ld, int rd, int n) {
        return !((rows >> row) & 1) &&
               !((ld >> (row + col)) & 1) &&
               !((rd >> (row - col + n)) & 1);
    }

    void solve(int col, int n, vector<int>& board,
               vector<vector<string>>& res,
               int rows, int ld, int rd) {
        if (col == n) {
            // 변환: board -> vector<string>
            vector<string> sol(n, string(n, '.'));
            for (int c = 0; c < n; c++) {
                sol[board[c]][c] = 'Q';
            }
            res.push_back(sol);
            return;
        }

        for (int row = 0; row < n; ++row) {
            if (isSafe(row, col, rows, ld, rd, n)) {
                board.push_back(row);
                solve(col + 1, n, board, res,
                      rows | (1 << row),
                      ld | (1 << (row + col)),
                      rd | (1 << (row - col + n)));
                board.pop_back();
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> board;
        solve(0, n, board, res, 0, 0, 0);
        return res;
    }
};


```