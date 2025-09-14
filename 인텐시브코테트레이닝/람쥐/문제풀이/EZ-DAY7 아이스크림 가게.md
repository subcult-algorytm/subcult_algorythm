https://www.hackerrank.com/challenges/icecream-parlor/problem?isFullScreen=true
### 개요 

이 문제는 모든 array의 원소를 투포인터로 풀거나, 아니면 해시를 이용해서 `unordered_map`을 사용해서 효과적으로 탐색도 가능합니다. 상황에 맞게 사용해야 합니다. 
본질적으로 Two Sum 문제로, 투포인터처럼 풀어도 됩니다.

### 풀이 

#### 단순 브루트 포스

그냥 무식하게 가격을 나타내는 array를 투포인터로 탐색해 봅시다. 

```cpp
vector<int> icecreamParlor(int m, vector<int> arr) {

    for ( int i = 0; i < arr.size() -1 ; i ++ )
    {
       for (int j = i+ 1 ; j < arr.size() ; j ++)
        {
            if (arr[i] + arr[j] == m)
            {
                return {i+1, j+1};  // arr의 인자가 1 인덱스라는걸 잊지 맙시다! 
            }
        }
    }
    return {};
}
```

다행히도 이 문제는 부르트 포스로 풀수있는 문제긴합니다만... **부르트 포스를 할 때 시간복잡도는 `O(n^2)`로 탐색크기가 커지게 된다면 매우 비효율적입니다.** 


####  해시 사용

해시를 사용해서 두 개 이상의 값을 한번에 쌍으로 저장하는 경우, 한 개의 값을 미리 저장해놓고, 그 값의 차액을 배열에서 찾는 방식으로 순회 횟수를 줄일 수 도 있습니다. 

이렇게 되면 매번 이중 순회를 할 필요가 없고, `unordered_map`을 순회하니 `O(logN)`으로 시간이 줄어듭니다. 

```cpp 

vector<int> icecreamParlor(int m, vector<int> arr) {

    unordered_map<int,int> seen; 
    for (int i = 0; i < arr.size() ; i++ )
    {
	   int cost = arr[i]; 
	   int need = m - cost; 
	   
	   if (seen.find(need)!=seen.end()){ 
		   return{seen[need] + 1, i + 1}; 
	   }
	   
	   if (seen.find(need) == seen.end())
	   { 
		   seen[cost] = i;
	   }
    }
    return {};
}
```


#### 유의 할점 
부르트 포스는 정말 간단하고 간편한 방식이지만, 시간초과가 있다면 한개의 값을 캐싱하는 방법으로 순회를 줄여 볼수 있습니다. 불필요한 순회를 한번만 줄여도 상당한 시간 절약 효과가 있으므로, 부르트 포스로 푼 모든 문제들을 한번 고민 해봅시다. 