#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#define X first
#define Y second

 
using namespace std;
int v,e;
/*vector<pair<int,int>> adj[10000]; // price, node number 
bool visited [10000]; */

int main(int argc, char* argv[])
{
    cin >> v >> e;
    vector<vector<pair<int,int>>> adj(v+1);
    vector<bool> visited(v+1,false); 
    for (int i = 0 ;i < e ; i ++ )
    {
        int a,b, price;
        cin >> a >> b >> price;
        adj[a].push_back(make_pair(price,b));
        adj[b].push_back(make_pair(price,a)); 
    }
    
    // Prim's algorithm
    int cnt = 0;
    int ans = 0;
    // Using a priority queue to select the minimum edge 
    priority_queue<tuple<int,int,int>,
                    vector<tuple<int,int,int>>,
                    greater<tuple<int,int,int>>
                    > pq;
    visited[1] = true; // start from node 1
    for (auto& edge : adj[1]) {
        pq.push({edge.X, 1, edge.Y}); // (price, from, to)
    }
    while (cnt < v-1) //
    {
        int price, from ,to;
        tie(price, from, to) = pq.top();
        pq.pop();
    
        if (visited[to]){continue; // this is very important, we should not visit the same node again
            }
        ans += price; // add the price of the edge to the answer 
        visited[to] = true; // mark the node as visited 
        cnt ++;
        for (auto&edge: adj[to])
        {
            if (!visited[edge.Y]) {
                pq.push({edge.X, from, edge.Y}); // (price, from, to)
            } 
        }
    }
    cout << ans << endl; 

}
