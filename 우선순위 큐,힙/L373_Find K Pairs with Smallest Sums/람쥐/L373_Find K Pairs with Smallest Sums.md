
https://leetcode.com/problems/find-k-pairs-with-smallest-sums/description/?envType=problem-list-v2&envId=heap-priority-queue


**우선순위 큐**를 이용해서 결과를 정렬하고, 인덱스를 담으면 되는 간단한 문제이지만, 생각외로 많은 사람들이 투 포인터 내지는 소트를 이용해서 해매게 되는 문제입니다.

#### 첫번째 생각 
- 첫번째와 두번째 배열을 소트를 한다 
- 그리고 소트한 것을 토대로 순회를 해서 합을 구한다 
- 합이 작은 순서대로 다시 해시 테이블에다가 넣는다 
- 작은 순서대로 K 만큼 뽑는다. 

하지만, 소트에서 가장 낮은 인덱스끼리 뽑은 페어는 최소 합을 보장하지 않는다는 문제.. 

예를 들어 

```
Nums1 = [ 1, 7 , 11]
Nums2 = [ 2 ,4 ,6]
```

인 경우, 

```
{1, 2} {1, 4} {1,6}
```

의 순이어야 하지만 
```
{1,2} {7,4} {11,6}
```

이 되어 최저 합부터 뽑는다는 가정이 성립되지 않음. 

그러면 루프를 고쳐서뽑으면 되지 않나 싶지만. 애초에 length 범위가 10^5 이기 때문에 시간  복잡도에서 상당한 손해를 보게 됨. 이렇게 되다 보니, 부르트 포스와 투포인터 모두가 봉인됨.
심지어 소트를 해서 시간복잡도를 줄여도 여전히 시간복잡도가 `O(m⋅n⋅log(m⋅n))` 으로 매우 높기 때문에, LTE, 즉 시간 초과 가능성이 높음. 

### 우선순위 큐를 이용한 풀이 

결국 힙정렬 접근이 필요한데, 힙 정렬은 반복되는 패턴이나, 작은 혹은 높은 순서대로 배치하는데에 유용한 편. `std::sort()`가 대표적으로 힙정렬을 사용하는 매서드. 

여기서는 우선순위 큐, 즉 `ordered_set` 을 사용하는 자료구조를 사용해야 하는데. 
C++ 에서는 우선순위 큐를 선언할때 
`priority_queue< typename T, container, compare>` 의 순으로 선언하게 됩니다. 

차례대로, 첫번째 `typename T ` 에는 해당 우선순위 큐에 담을 데이터의 타입을 정하며, 
`container` 에는 이를 담을 컨테이너의 타입을 지정해야하는데, 대부분의 경우`std::vector()`를 지정하는 경우가 많습니다. `compare` 는 해당 우선순위큐를 어떤 순서로 정렬할지를 지정하며 `bool` 타입을 리턴해야 합니다. 

참고 : https://en.cppreference.com/w/cpp/container/priority_queue.html

그러므로 
```cpp 
priority_queue <pair<int, pair<int, int>>, 
				vector<pair<int, pair<int,int>>>,
				greater<pair <int, pair<int,int>>>
				>pq;
 
```

이렇게 우선순위 큐를 정의합니다. 이를 풀어서 해석하면 해당 우선순위큐는 `<int (합), pair<int, int> (인덱스 페어)> `의 자료형을 받으며, 이 둘을 페어로 묶는 `std::vector`를 컨테이너를 사용하며, 작은 순서대로 나열하게 됩니다. 

