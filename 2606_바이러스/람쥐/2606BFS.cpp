#include <iostream> 
#include <queue> 

using namespace std; 
int n[101][101];
bool visited [101]; 
int c; 
int nn, pp; 

queue <int> q; 

void bfs(int inV){ 

    visited [inV] = true; 
    q.push(inV);

    while(!q.empty()){ 
        inV = q.front(); 
        q.pop(); 
        for (int i = 1 ; i < nn ; i++) // why this recusion index starts from 1? 
        { 
            if (visited[i] == 0 && n[inV][i] == 1)
            { 
                q.push(i);
                visited[i] = 1; 
                c++;
            }
    
        }
    }
}

int main (){ 

    cin >> nn >> pp; 
    for (int i = 1; i < pp ; i++)
    { 
        int x, y; 
        cin >> x >> y; 
        n[x][y] = 1;
        n[y][x] = 1;

    }
    bfs (1); 
    cout << c; 
}
